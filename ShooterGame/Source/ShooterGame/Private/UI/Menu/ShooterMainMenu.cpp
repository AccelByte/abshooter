// Copyright 1998 - 2020 Epic Games, Inc. All Rights Reserved.

#include "ShooterMainMenu.h"
#include "ShooterGameInstance.h"
#include "ShooterGameProfile.h"
#include "ShooterLobby.h"
#include "ShooterGallery.h"
#include "UMG/MainMenu/MainMenuUI.h"
#include "UMG/GameProfileMenu/GameProfileMenuUI.h"
#include "UMG/LobbyMenu/LobbyMenuUI.h"
#include "UMG/GalleryMenu/GalleryMenuUI.h"
#include "Utils/FileUtils.h"
#include "Utils/CacheUtils.h"
// AccelByte
#include "Core/AccelByteRegistry.h"

// TODO: Refactor into UMG
#include "ShooterGame.h"
#include "ShooterGameLoadingScreen.h"
#include "ShooterStyle.h"
#include "ShooterMenuWidgetStyle.h"
#include "ShooterMenuSoundsWidgetStyle.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "GenericPlatform/GenericPlatformChunkInstall.h"
#include "Online/ShooterOnlineGameSettings.h"
#include "OnlineSubsystemSessionSettings.h"
#include "SShooterConfirmationDialog.h"
#include "ShooterMenuItemWidgetStyle.h"
#include "ShooterGameUserSettings.h"
#include "ShooterGameViewportClient.h"
#include "Player/ShooterPersistentUser.h"
#include "Player/ShooterLocalPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ShooterGameConfig.h"
#include "ShooterGameTelemetry.h"
// AccelByte
#include "Api/AccelByteOauth2Api.h"
#include "Api/AccelByteWalletApi.h"
#include "Api/AccelByteQos.h"
#include "Core/AccelByteCredentials.h"

#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"

#define MAX_BOT_COUNT 8

static const FString MapNames[] = { TEXT("Highrise") };
static const FString JoinMapNames[] = { TEXT("Any"), TEXT("Highrise") };
static const FName PackageNames[] = { TEXT("Highrise.umap") };
static const int DefaultTDMMap = 1;
static const int DefaultFFAMap = 0; 
static const float QuickmatchUIAnimationTimeDuration = 30.f;

//use an EMap index, get back the ChunkIndex that map should be part of.
//Instead of this mapping we should really use the AssetRegistry to query for chunk mappings, but maps aren't members of the AssetRegistry yet.
static const int ChunkMapping[] = { 1, 2 };

#if PLATFORM_SWITCH
#	define LOGIN_REQUIRED_FOR_ONLINE_PLAY 1
#else
#	define LOGIN_REQUIRED_FOR_ONLINE_PLAY 0
#endif

#if PLATFORM_SWITCH
#	define CONSOLE_LAN_SUPPORTED 1
#else
#	define CONSOLE_LAN_SUPPORTED 0
#endif

FShooterMainMenu::FShooterMainMenu(TWeakObjectPtr<UShooterGameInstance> _GameInstance)
	: GameInstance(_GameInstance)
{}

FShooterMainMenu::~FShooterMainMenu()
{
	auto Sessions = Online::GetSessionInterface();
	CleanupOnlinePrivilegeTask();
}

void FShooterMainMenu::Construct(TWeakObjectPtr<ULocalPlayer> _PlayerOwner)
{
	UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Construct"));

	if (!GameInstance.IsValid()) return;

	// Load main menu widget
	if (!ensure(GameInstance->MainMenuClass.IsValid())) return;

	PopulateRegionLatencies(ShooterGameConfig::Get().ServerLatencies_);
	auto ServerList = ShooterGameConfig::Get().ServerLatencies_;
	ShooterGameConfig::Get().SelectRegion(ServerList[0]);

	MainMenuUI = MakeWeakObjectPtr<UMainMenuUI>(CreateWidget<UMainMenuUI>(GameInstance.Get(), *GameInstance->MainMenuClass.Get()));
	if (!ensure(MainMenuUI != nullptr))
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] MainMenuUI is null"));
		return;
	}

	// Add the widget to viewport
	UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Setup MainMenuUI to viewport"));
	MainMenuUI->Setup();

	// Set up
	//LobbyWidget = SNew(SLobby);
	FShooterCacheUtils::LoadUserCaches();
	GameProfile = MakeShareable(new ShooterGameProfile(GameInstance, MakeWeakObjectPtr<UGameProfileMenuUI>(MainMenuUI->GetGameProfileMenu())));
	GameProfile->Initialize();
	Lobby = MakeShareable(new ShooterLobby(GameInstance, MakeWeakObjectPtr<ULobbyMenuUI>(MainMenuUI->GetLobbyMenu())));
	Lobby->Connect();
	Gallery = MakeShareable(new ShooterGallery(GameInstance, MakeWeakObjectPtr<UGalleryMenuUI>(MainMenuUI->GetGalleryMenu())));
	Gallery->Initialize();

	UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Get User Profile ..."));

	// Check cache first
	bool isUserCached = FShooterCacheUtils::IsUserCacheExist(GameInstance->UserProfileInfo.UserId);
	if (isUserCached)
	{
		UpdateUserProfileFromCache();
	}
	else
	{
		THandler<FAccelByteModelsUserProfileInfo> OnUserProfileObtained = THandler<FAccelByteModelsUserProfileInfo>::CreateLambda([this](const FAccelByteModelsUserProfileInfo& UserProfileInfo)
			{
				GameInstance->UserProfileInfo = UserProfileInfo; // save our own
				UpdateUserProfile(UserProfileInfo.AvatarUrl);
			}
		);
		FRegistry::UserProfile.GetUserProfile(
			AccelByte::THandler<FAccelByteModelsUserProfileInfo>::CreateLambda([this, OnUserProfileObtained = OnUserProfileObtained](const FAccelByteModelsUserProfileInfo& UserProfileInfo)
				{
					UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Get User ID: %s"), *UserProfileInfo.UserId);
					OnUserProfileObtained.ExecuteIfBound(UserProfileInfo);
				}
			),
			AccelByte::FErrorHandler::CreateLambda([this, OnUserProfileObtained = OnUserProfileObtained](int32 Code, FString Message)
				{
					UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Get User Profile Error: %s"), *Message);
					UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Attempt to create default user Profile..."));

					FAccelByteModelsUserProfileCreateRequest defaultCreateProfileRequest;
					defaultCreateProfileRequest.AvatarUrl = "https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg";
					defaultCreateProfileRequest.AvatarLargeUrl = "https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg";
					defaultCreateProfileRequest.AvatarSmallUrl = "https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg";
					defaultCreateProfileRequest.Language = "en";
					defaultCreateProfileRequest.Timezone = "Etc/UTC";
					defaultCreateProfileRequest.DateOfBirth = "1991-01-01";
					defaultCreateProfileRequest.FirstName = GameInstance->UserToken.Display_name;
					defaultCreateProfileRequest.LastName = GameInstance->UserToken.Display_name;

					FRegistry::UserProfile.CreateUserProfile(
						defaultCreateProfileRequest,
						AccelByte::THandler<FAccelByteModelsUserProfileInfo>::CreateLambda([&, OnUserProfileObtained = OnUserProfileObtained](const FAccelByteModelsUserProfileInfo& UserProfileInfo)
							{
								UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Attempt to create default user Profile...SUCCESS"));
								UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Get User ID: %s"), *UserProfileInfo.UserId);
								OnUserProfileObtained.ExecuteIfBound(UserProfileInfo);
							}
						),
						AccelByte::FErrorHandler::CreateLambda([&, defaultCreateProfileRequest = defaultCreateProfileRequest](int32 Code, FString Message)
							{
								UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Attempt to create default user Profile Failed! Code: %d, Message: %s."), Code, *Message);

								UpdateUserProfile(defaultCreateProfileRequest.AvatarUrl);
							}
						)
					);
				}
			)
		);
	}

	// TODO: Refactor into UMG
	/*
	bShowingDownloadPct = false;
	bAnimateQuickmatchSearchingUI = false;
	bUsedInputToCancelQuickmatchSearch = false;
	bQuickmatchSearchRequestCanceled = false;
	bIncQuickMAlpha = false;
	PlayerOwner = _PlayerOwner;
	MatchType = EMatchType::Custom;

	check(_GameInstance.IsValid());
	auto Sessions = Online::GetSessionInterface();

	GameInstance = _GameInstance;
	PlayerOwner = _PlayerOwner;

	OnCancelMatchmakingCompleteDelegate = FOnCancelMatchmakingCompleteDelegate::CreateSP(this, &FShooterMainMenu::OnCancelMatchmakingComplete);
	OnMatchmakingCompleteDelegate = FOnMatchmakingCompleteDelegate::CreateSP(this, &FShooterMainMenu::OnMatchmakingComplete);

	RefreshWallet();

	// read user settings
#if SHOOTER_CONSOLE_UI
	bIsLanMatch = FParse::Param(FCommandLine::Get(), TEXT("forcelan"));
#else
	UShooterGameUserSettings* const UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
	bIsLanMatch = UserSettings->IsLanMatch();
	bIsDedicatedServer = UserSettings->IsDedicatedServer();
#endif

	BotsCountOpt = 1;
	bIsRecordingDemo = false;

	if(GetPersistentUser())
	{
		BotsCountOpt = GetPersistentUser()->GetBotsCount();
		bIsRecordingDemo = GetPersistentUser()->IsRecordingDemos();
	}		

	// number entries 0 up to MAX_BOX_COUNT
	TArray<FText> BotsCountList;
	for (int32 i = 0; i <= MAX_BOT_COUNT; i++)
	{
		BotsCountList.Add(FText::AsNumber(i));
	}
	
	TArray<FText> MapList;
	for (int32 i = 0; i < ARRAY_COUNT(MapNames); ++i)
	{
		MapList.Add(FText::FromString(MapNames[i]));		
	}

	TArray<FText> JoinMapList;
	for (int32 i = 0; i < ARRAY_COUNT(JoinMapNames); ++i)
	{
		JoinMapList.Add(FText::FromString(JoinMapNames[i]));
	}

	TArray<FText> OnOffList;
	OnOffList.Add( LOCTEXT("Off","OFF") );
	OnOffList.Add( LOCTEXT("On","ON") );

	ShooterOptions = MakeShareable(new FShooterOptions()); 
	ShooterOptions->Construct(GetPlayerOwner());
	ShooterOptions->TellInputAboutKeybindings();
	ShooterOptions->OnApplyChanges.BindSP(this, &FShooterMainMenu::CloseSubMenu);

	//Now that we are here, build our menu 
	MenuWidget.Reset();
	MenuWidgetContainer.Reset();
	UserProfileWidgetContainer.Reset();

	TArray<FString> Keys;
	GConfig->GetSingleLineArray(TEXT("/Script/SwitchRuntimeSettings.SwitchRuntimeSettings"), TEXT("LeaderboardMap"), Keys, GEngineIni);

	if (GEngine && GEngine->GameViewport)
	{		

		// Justice user profile logged-in
		//SAssignNew(UserProfileWidget, SShooterUserProfileWidget)
		//	.Cursor(EMouseCursor::Default)
		//	.PlayerOwner(GetPlayerOwner())
		//	.IsGameMenu(false)
		//	.OnClicked(FOnClicked::CreateLambda([&]()->FReply
		//	{
		//		return FReply::Handled();
		//	}));

		//SAssignNew(MenuWidget, SShooterMenuWidget)
		//	.Cursor(EMouseCursor::Default)
		//	.PlayerOwner(GetPlayerOwner())
		//	.IsGameMenu(false)
		//	.UserProfileWidget(UserProfileWidget);

		SAssignNew(GameProfileWidget, SShooterGameProfile)
			.OwnerWidget(MenuWidget)
			.PlayerOwner(GetPlayerOwner());

		SAssignNew(CoinsWidgetContainer, SShooterCoinsWidget)
			.Cursor(EMouseCursor::Default);

		SAssignNew(MenuWidgetContainer, SWeakWidget)
			.PossiblyNullContent(MenuWidget);

		//SAssignNew(UserProfileWidgetContainer, SWeakWidget)
		//	.PossiblyNullContent(UserProfileWidget);

		TSharedPtr<FShooterMenuItem> RootMenuItem;
				
		SAssignNew(SplitScreenLobbyWidget, SShooterSplitScreenLobby)
			.PlayerOwner(GetPlayerOwner())
			.OnCancelClicked(FOnClicked::CreateSP(this, &FShooterMainMenu::OnSplitScreenBackedOut)) 
			.OnPlayClicked(FOnClicked::CreateSP(this, &FShooterMainMenu::OnSplitScreenPlay));

		FText Msg = LOCTEXT("No matches could be found", "No matches could be found");
		FText OKButtonString = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		QuickMatchFailureWidget = SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)			
			.MessageText(Msg)
			.ConfirmText(OKButtonString)
			.CancelText(FText())
			.OnConfirmClicked(FOnClicked::CreateRaw(this, &FShooterMainMenu::OnQuickMatchFailureUICancel))
			.OnCancelClicked(FOnClicked::CreateRaw(this, &FShooterMainMenu::OnQuickMatchFailureUICancel));

		Msg = LOCTEXT("Searching for Match...", "SEARCHING FOR MATCH...");
		OKButtonString = LOCTEXT("Stop", "STOP");
		QuickMatchSearchingWidget = SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)			
			.MessageText(Msg)
			.ConfirmText(OKButtonString)
			.CancelText(FText())
			.OnConfirmClicked(FOnClicked::CreateRaw(this, &FShooterMainMenu::OnQuickMatchSearchingUICancel))
			.OnCancelClicked(FOnClicked::CreateRaw(this, &FShooterMainMenu::OnQuickMatchSearchingUICancel));


		// message box test message
		Msg = LOCTEXT("Hello message box", "Hello message box");
		OKButtonString = NSLOCTEXT("DialogButtons", "YAY", "YAY");
		FText CancelButtonString = NSLOCTEXT("DialogButtons", "NOOO", "NOOO");
		TestMessageWidget = SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
			.MessageText(Msg)
			.ConfirmText(OKButtonString)
			.CancelText(CancelButtonString)
			.OnConfirmClicked(FOnClicked::CreateLambda([&]() -> FReply {
			UE_LOG(LogTemp, Log, TEXT("OK"));

			if (GEngine && GEngine->GameViewport)
			{
				GEngine->GameViewport->RemoveViewportWidgetContent(TestMessageWidgetContainer.ToSharedRef());
			}
			AddMenuToGameViewport();
			FSlateApplication::Get().SetKeyboardFocus(MenuWidget);

			return FReply::Handled();
		}))
			.OnCancelClicked(FOnClicked::CreateLambda([&]() -> FReply {
			UE_LOG(LogTemp, Log, TEXT("Cancel"));

			if (GEngine && GEngine->GameViewport)
			{
				GEngine->GameViewport->RemoveViewportWidgetContent(TestMessageWidgetContainer.ToSharedRef());
			}
			AddMenuToGameViewport();
			FSlateApplication::Get().SetKeyboardFocus(MenuWidget);


			return FReply::Handled();
		}));


		SAssignNew(SplitScreenLobbyWidgetContainer, SWeakWidget)
			.PossiblyNullContent(SplitScreenLobbyWidget);		

		SAssignNew(QuickMatchFailureWidgetContainer, SWeakWidget)
			.PossiblyNullContent(QuickMatchFailureWidget);	

		SAssignNew(QuickMatchSearchingWidgetContainer, SWeakWidget)
			.PossiblyNullContent(QuickMatchSearchingWidget);

		SAssignNew(TestMessageWidgetContainer, SWeakWidget)
			.PossiblyNullContent(TestMessageWidget);



		FText StoppingOKButtonString = LOCTEXT("Stopping", "STOPPING...");
		QuickMatchStoppingWidget = SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)			
			.MessageText(Msg)
			.ConfirmText(StoppingOKButtonString)
			.CancelText(FText())
			.OnConfirmClicked(FOnClicked())
			.OnCancelClicked(FOnClicked());

		SAssignNew(QuickMatchStoppingWidgetContainer, SWeakWidget)
			.PossiblyNullContent(QuickMatchStoppingWidget);

#if PLATFORM_XBOXONE
		TSharedPtr<FShooterMenuItem> MenuItem;

		// HOST ONLINE menu option
		{
			MenuItem = MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("HostCustom", "HOST CUSTOM"), this, &FShooterMainMenu::OnHostOnlineSelected);

			// submenu under "HOST ONLINE"
			MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnSplitScreenSelected);

			TSharedPtr<FShooterMenuItem> NumberOfBotsOption = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("NumberOfBots", "NUMBER OF BOTS"), BotsCountList, this, &FShooterMainMenu::BotCountOptionChanged);				
			NumberOfBotsOption->SelectedMultiChoice = BotsCountOpt;																

			HostOnlineMapOption = MenuHelper::AddMenuOption(MenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), MapList);
		}

		// JOIN menu option
		{
			// JOIN menu option
			MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("FindCustom", "FIND CUSTOM"), this, &FShooterMainMenu::OnJoinServer);

			// Server list widget that will be called up if appropriate
			MenuHelper::AddCustomMenuItem(JoinServerItem,SAssignNew(ServerListWidget,SShooterServerList).OwnerWidget(MenuWidget).PlayerOwner(GetPlayerOwner()));
		}

		// QUICK MATCH menu option
		{
			MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("QuickMatch", "QUICK MATCH"), this, &FShooterMainMenu::OnQuickMatchSelected);
		}

		// HOST OFFLINE menu option
		{
			MenuItem = MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("PlayOffline", "PLAY OFFLINE"),this, &FShooterMainMenu::OnHostOfflineSelected);

			// submenu under "HOST OFFLINE"
			MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnSplitScreenSelected);

			TSharedPtr<FShooterMenuItem> NumberOfBotsOption = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("NumberOfBots", "NUMBER OF BOTS"), BotsCountList, this, &FShooterMainMenu::BotCountOptionChanged);				
			NumberOfBotsOption->SelectedMultiChoice = BotsCountOpt;																

			HostOfflineMapOption = MenuHelper::AddMenuOption(MenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), MapList);
		}
#elif SHOOTER_CONSOLE_UI
		TSharedPtr<FShooterMenuItem> MenuItem;

		// HOST ONLINE menu option
		{
			HostOnlineMenuItem = MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("HostOnline", "HOST ONLINE"), this, &FShooterMainMenu::OnHostOnlineSelected);

			// submenu under "HOST ONLINE"
#if LOGIN_REQUIRED_FOR_ONLINE_PLAY
			MenuHelper::AddMenuItemSP(HostOnlineMenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnSplitScreenSelectedHostOnlineLoginRequired);
#else
			MenuHelper::AddMenuItemSP(HostOnlineMenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnSplitScreenSelectedHostOnline);
#endif

			TSharedPtr<FShooterMenuItem> NumberOfBotsOption = MenuHelper::AddMenuOptionSP(HostOnlineMenuItem, LOCTEXT("NumberOfBots", "NUMBER OF BOTS"), BotsCountList, this, &FShooterMainMenu::BotCountOptionChanged);
			NumberOfBotsOption->SelectedMultiChoice = BotsCountOpt;																

			HostOnlineMapOption = MenuHelper::AddMenuOption(HostOnlineMenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), MapList);
#if CONSOLE_LAN_SUPPORTED
			HostLANItem = MenuHelper::AddMenuOptionSP(HostOnlineMenuItem, LOCTEXT("LanMatch", "LAN"), OnOffList, this, &FShooterMainMenu::LanMatchChanged);
			HostLANItem->SelectedMultiChoice = bIsLanMatch;
#endif
		}

		// HOST OFFLINE menu option
		{
			MenuItem = MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("HostOffline", "HOST OFFLINE"),this, &FShooterMainMenu::OnHostOfflineSelected);

			// submenu under "HOST OFFLINE"
			MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnSplitScreenSelected);

			TSharedPtr<FShooterMenuItem> NumberOfBotsOption = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("NumberOfBots", "NUMBER OF BOTS"), BotsCountList, this, &FShooterMainMenu::BotCountOptionChanged);				
			NumberOfBotsOption->SelectedMultiChoice = BotsCountOpt;																

			HostOfflineMapOption = MenuHelper::AddMenuOption(MenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), MapList);
		}

		// QUICK MATCH menu option
		{
#if LOGIN_REQUIRED_FOR_ONLINE_PLAY
			MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("QuickMatch", "QUICK MATCH"), this, &FShooterMainMenu::OnQuickMatchSelectedLoginRequired);
#else
			MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("QuickMatch", "QUICK MATCH"), this, &FShooterMainMenu::OnQuickMatchSelected);
#endif
		}

		// JOIN menu option
		{
			// JOIN menu option
			MenuItem = MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Join", "JOIN"), this, &FShooterMainMenu::OnJoinSelected);

			// submenu under "join"
#if LOGIN_REQUIRED_FOR_ONLINE_PLAY
			MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("Server", "SERVER"), this, &FShooterMainMenu::OnJoinServerLoginRequired);
#else
			MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("Server", "SERVER"), this, &FShooterMainMenu::OnJoinServer);
#endif
			JoinMapOption = MenuHelper::AddMenuOption(MenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), JoinMapList);

			// Server list widget that will be called up if appropriate
			MenuHelper::AddCustomMenuItem(JoinServerItem,SAssignNew(ServerListWidget,SShooterServerList).OwnerWidget(MenuWidget).PlayerOwner(GetPlayerOwner()));

#if CONSOLE_LAN_SUPPORTED
			JoinLANItem = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("LanMatch", "LAN"), OnOffList, this, &FShooterMainMenu::LanMatchChanged);
			JoinLANItem->SelectedMultiChoice = bIsLanMatch;
#endif
		}

#else
		FMargin StylizedMargin = FMargin(0, 10, 0, 10);
		TSharedPtr<FShooterMenuItem> MenuItem;

		// HOST menu option
		MenuItem = MenuHelper::AddMenuItem(RootMenuItem, LOCTEXT("SinglePlayer", "SINGLE PLAYER"), StylizedMargin);

		//// submenu under "host"
		MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("FFALong", "VS. BOT"), this, &FShooterMainMenu::OnUIHostFreeForAll);
		MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("Back", "BACK"), this, &FShooterMainMenu::OnUIMenuGoBack);
		//MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("TDMLong", "TEAM DEATHMATCH"), this, &FShooterMainMenu::OnUIHostTeamDeathMatch);

		//TSharedPtr<FShooterMenuItem> NumberOfBotsOption = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("NumberOfBots", "NUMBER OF BOTS"), BotsCountList, this, &FShooterMainMenu::BotCountOptionChanged);
		//NumberOfBotsOption->SelectedMultiChoice = BotsCountOpt;

		//HostOnlineMapOption = MenuHelper::AddMenuOption(MenuItem, LOCTEXT("SELECTED_LEVEL", "Map"), MapList);

		//HostLANItem = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("LanMatch", "LAN"), OnOffList, this, &FShooterMainMenu::LanMatchChanged);
		//HostLANItem->SelectedMultiChoice = bIsLanMatch;

		//RecordDemoItem = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("RecordDemo", "Record Demo"), OnOffList, this, &FShooterMainMenu::RecordDemoChanged);
		//RecordDemoItem->SelectedMultiChoice = bIsRecordingDemo;

		//// JOIN menu option
		//MenuItem = MenuHelper::AddMenuItem(RootMenuItem, LOCTEXT("Join", "JOIN"));

		//// submenu under "join"
		//MenuHelper::AddMenuItemSP(MenuItem, LOCTEXT("Server", "SERVER"), this, &FShooterMainMenu::OnJoinServer);
		//JoinLANItem = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("LanMatch", "LAN"), OnOffList, this, &FShooterMainMenu::LanMatchChanged);
		//JoinLANItem->SelectedMultiChoice = bIsLanMatch;

		//DedicatedItem = MenuHelper::AddMenuOptionSP(MenuItem, LOCTEXT("Dedicated", "Dedicated"), OnOffList, this, &FShooterMainMenu::DedicatedServerChanged);
		//DedicatedItem->SelectedMultiChoice = bIsDedicatedServer;

		//// Server list widget that will be called up if appropriate
		//MenuHelper::AddCustomMenuItem(JoinServerItem,SAssignNew(ServerListWidget,SShooterServerList).OwnerWidget(MenuWidget).PlayerOwner(GetPlayerOwner()));
#endif
		// Lobby
		MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Lobby", "LOBBY"), this, &FShooterMainMenu::OnShowLobby, StylizedMargin);
		MenuHelper::AddCustomMenuItem(LobbyMenuItem, SAssignNew(LobbyWidget, SLobby)
			.OwnerWidget(MenuWidget)
			.PlayerOwner(GetPlayerOwner())
			.OnStartMatch_Lambda([&] {
				GameInstance->GotoState(ShooterGameInstanceState::Playing);
				MenuWidget->LockControls(true);
				MenuWidget->HideMenu();
			}));

		// Leaderboards
		//MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Leaderboards", "LEADERBOARDS"), this, &FShooterMainMenu::OnShowLeaderboard);
		//MenuHelper::AddCustomMenuItem(LeaderboardItem,SAssignNew(LeaderboardWidget,SShooterLeaderboard).OwnerWidget(MenuWidget).PlayerOwner(GetPlayerOwner()));

		// DS Region Selection
		PopulateRegionLatencies(ShooterGameConfig::Get().ServerLatencies_);
		MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("RefreshQoS", "REGION ↺"), this, &FShooterMainMenu::GetQoS, StylizedMargin);
		DsRegionOption = MenuHelper::AddMenuOptionSP(RootMenuItem, LOCTEXT("", ""), DsRegionLatenciesText, this, &FShooterMainMenu::DsRegionOptionChanged, StylizedMargin);
		// Initial selection
		DsRegionOptionChanged(DsRegionOption, DsRegionOption->SelectedMultiChoice);

#if !SHOOTER_CONSOLE_UI

		// Inventory
		{
			MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Inventory", "INVENTORY"), this, &FShooterMainMenu::OnShowInventory, StylizedMargin);
			MenuHelper::AddCustomMenuItem(InventoryItem, SAssignNew(InventoryWidget, SShooterInventory).OwnerWidget(MenuWidget).PlayerOwner(GetPlayerOwner()).OnBuyItemFinished(FSimpleDelegate::CreateSP(this, &FShooterMainMenu::RefreshWallet)));
		}
#endif

		// Store
		MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Store", "STORE"), this, &FShooterMainMenu::OnShowStore, StylizedMargin);
		MenuHelper::AddCustomMenuItem(StoreItem, SAssignNew(StoreWidget, SShooterStore)
			.OwnerWidget(MenuWidget)
			.PlayerOwner(GetPlayerOwner())
			.OnBuyItemFinished(FSimpleDelegate::CreateSP(this, &FShooterMainMenu::RefreshWallet))
			.CoinsWidget(CoinsWidgetContainer));

		// Options
		ShooterOptions->OptionsItem->ExternalPadding = StylizedMargin;
		MenuHelper::AddExistingMenuItem(RootMenuItem, ShooterOptions->OptionsItem.ToSharedRef());
		ShooterOptions->OptionsItem->OnConfirmMenuItem.BindSP(this, &FShooterMainMenu::OnShowOption);
		if(FSlateApplication::Get().SupportsSystemHelp())
		{
			TSharedPtr<FShooterMenuItem> HelpSubMenu = MenuHelper::AddMenuItem(RootMenuItem, LOCTEXT("Help", "HELP"));
			HelpSubMenu->OnConfirmMenuItem.BindStatic([](){ FSlateApplication::Get().ShowSystemHelp(); });
		}

		// QUIT option (for PC)
#if !SHOOTER_CONSOLE_UI
		MenuHelper::AddMenuItemSP(RootMenuItem, LOCTEXT("Quit", "QUIT"), this, &FShooterMainMenu::OnUIQuit, StylizedMargin);
#endif

		MenuWidget->CurrentMenuTitle = LOCTEXT("MainMenu","MAIN MENU");
		MenuWidget->OnGoBack.BindSP(this, &FShooterMainMenu::OnMenuGoBack);
		MenuWidget->MainMenu = MenuWidget->CurrentMenu = RootMenuItem->SubMenu;
		MenuWidget->OnMenuHidden.BindSP(this, &FShooterMainMenu::OnMenuHidden);

		ShooterOptions->UpdateOptions();
		MenuWidget->BuildAndShowMenu();


		CoinsWidgetContainer->BuildAndShowMenu();
		CoinsWidgetContainer->SetVisibility(EVisibility::Collapsed);
	}
	*/
}

void FShooterMainMenu::Teardown()
{
	if (MainMenuUI.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterMainMenu] Teardown MainMenuUI"));
		MainMenuUI->Teardown();
		MainMenuUI.Reset();
	}
}

void FShooterMainMenu::UpdateUserProfile(FString AvatarURL)
{
	MainMenuUI->SetDisplayName(GameInstance->UserToken.Display_name);
	if (!AvatarURL.IsEmpty())
	{
		FString Filename = FShooterCacheUtils::CacheDir / GameInstance->UserToken.User_id + TEXT(".png");
		FShooterImageUtils::GetImage(AvatarURL, FOnImageReceived::CreateSP(this, &FShooterMainMenu::OnThumbImageReceived), Filename);
	}
}

void FShooterMainMenu::OnThumbImageReceived(FCacheBrush Image)
{
	if (Image.IsValid())
	{
		MainMenuUI->SetAvatarImage(*Image.Get());
		FUserCache UserCache;
		UserCache.UserId = GameInstance->UserToken.User_id;
		UserCache.DisplayName = GameInstance->UserToken.Display_name;
		FShooterCacheUtils::SaveUserCache(UserCache);
		GameInstance->PlayerAvatar = Image;
	}
}

void FShooterMainMenu::UpdateUserProfileFromCache()
{
	MainMenuUI->SetDisplayName(GameInstance->UserToken.Display_name);
	FCacheBrush UserAvatar = FShooterCacheUtils::GetUserAvatarCache(GameInstance->UserToken.User_id);
	if(UserAvatar.IsValid())
	{
		MainMenuUI->SetAvatarImage(*UserAvatar.Get());
		GameInstance->PlayerAvatar = UserAvatar;
	}
}

// TODO: Migrate into UMG

void FShooterMainMenu::AddMenuToGameViewport()
{
	if (GEngine && GEngine->GameViewport)
	{
		UGameViewportClient* const GVC = GEngine->GameViewport;
		
		GVC->AddViewportWidgetContent(CoinsWidgetContainer.ToSharedRef());
		GVC->AddViewportWidgetContent(MenuWidgetContainer.ToSharedRef()); // yg di add terakhir, bisa dapat input
		GVC->SetCaptureMouseOnClick(EMouseCaptureMode::NoCapture);
	}
}

void FShooterMainMenu::RemoveMenuFromGameViewport()
{
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
		GEngine->GameViewport->RemoveViewportWidgetContent(CoinsWidgetContainer.ToSharedRef());
	}
}

void FShooterMainMenu::Tick(float DeltaSeconds)
{
	if (bAnimateQuickmatchSearchingUI && QuickMatchSearchingWidget.IsValid())
	{
		FLinearColor QuickMColor = QuickMatchSearchingWidget->GetColorAndOpacity();
		if (bIncQuickMAlpha)
		{
			if (QuickMColor.A >= 1.f)
			{
				bIncQuickMAlpha = false;
			}
			else
			{
				QuickMColor.A += DeltaSeconds;
			}
		}
		else
		{
			if (QuickMColor.A <= .1f)
			{
				bIncQuickMAlpha = true;
			}
			else
			{
				QuickMColor.A -= DeltaSeconds;
			}
		}
		QuickMatchSearchingWidget->SetColorAndOpacity(QuickMColor);
		QuickMatchStoppingWidget->SetColorAndOpacity(QuickMColor);
	}

	IPlatformChunkInstall* ChunkInstaller = FPlatformMisc::GetPlatformChunkInstall();
	if (ChunkInstaller)
	{
		EMap SelectedMap = GetSelectedMap();
		// use assetregistry when maps are added to it.
		int32 MapChunk = ChunkMapping[(int)SelectedMap];
        //ChunkInstaller->GetPakchunkLocation()
		EChunkLocation::Type ChunkLocation = ChunkInstaller->GetPakchunkLocation(MapChunk);

		FText UpdatedText;
		bool bUpdateText = false;
		if (ChunkLocation == EChunkLocation::NotAvailable)
		{			
			float PercentComplete = FMath::Min(ChunkInstaller->GetChunkProgress(MapChunk, EChunkProgressReportingType::PercentageComplete), 100.0f);									
			UpdatedText = FText::FromString(FString::Printf(TEXT("%s %4.0f%%"),*LOCTEXT("SELECTED_LEVEL", "Map").ToString(), PercentComplete));
			bUpdateText = true;
			bShowingDownloadPct = true;
		}
		else if (bShowingDownloadPct)
		{
			UpdatedText = LOCTEXT("SELECTED_LEVEL", "Map");			
			bUpdateText = true;
			bShowingDownloadPct = false;			
		}

		if (bUpdateText)
		{
			if (GameInstance.IsValid() && GameInstance->GetOnlineMode() != EOnlineMode::Offline && HostOnlineMapOption.IsValid())
			{
				HostOnlineMapOption->SetText(UpdatedText);
			}
			else if (HostOfflineMapOption.IsValid())
			{
				HostOfflineMapOption->SetText(UpdatedText);
			}
		}
	}
}

TStatId FShooterMainMenu::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FShooterMainMenu, STATGROUP_Tickables);
}

void FShooterMainMenu::OnMenuHidden()
{	
#if SHOOTER_CONSOLE_UI
	// Menu was hidden from the top-level main menu, on consoles show the welcome screen again.
	if ( ensure(GameInstance.IsValid()))
	{
		GameInstance->GotoState(ShooterGameInstanceState::WelcomeScreen);
	}
#else
	RemoveMenuFromGameViewport();
#endif
}

void FShooterMainMenu::OnQuickMatchSelectedLoginRequired()
{
	IOnlineIdentityPtr Identity = IOnlineSubsystem::Get()->GetIdentityInterface();

	int32 ControllerId = GetPlayerOwner()->GetControllerId();

	OnLoginCompleteDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(ControllerId, FOnLoginCompleteDelegate::CreateRaw(this, &FShooterMainMenu::OnLoginCompleteQuickmatch));
	Identity->Login(ControllerId, FOnlineAccountCredentials());
}

void FShooterMainMenu::OnLoginCompleteQuickmatch(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	IOnlineSubsystem::Get()->GetIdentityInterface()->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, OnLoginCompleteDelegateHandle);

	OnQuickMatchSelected();
}

void FShooterMainMenu::OnQuickMatchSelected()
{
	bQuickmatchSearchRequestCanceled = false;
#if SHOOTER_CONSOLE_UI
	if ( !ValidatePlayerForOnlinePlay(GetPlayerOwner()) )
	{
		return;
	}
#endif

	StartOnlinePrivilegeTask(IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate::CreateSP(this, &FShooterMainMenu::OnUserCanPlayOnlineQuickMatch));
}

void FShooterMainMenu::OnUserCanPlayOnlineQuickMatch(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{
	CleanupOnlinePrivilegeTask();
	MenuWidget->LockControls(false);
	if (PrivilegeResults == (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures)
	{
		if (GameInstance.IsValid())
		{
			GameInstance->SetOnlineMode(EOnlineMode::Online);
		}

		MatchType = EMatchType::Quick;

		//SplitScreenLobbyWidget->SetIsJoining(false);

		// Skip splitscreen for PS4
#if PLATFORM_PS4 || MAX_LOCAL_PLAYERS == 1
		BeginQuickMatchSearch();
#else
		UGameViewportClient* const GVC = GEngine->GameViewport;

		RemoveMenuFromGameViewport();
		//GVC->AddViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());

		//SplitScreenLobbyWidget->Clear();
		//FSlateApplication::Get().SetKeyboardFocus(SplitScreenLobbyWidget);
#endif
	}
	else if (GameInstance.IsValid())
	{

		GameInstance->DisplayOnlinePrivilegeFailureDialogs(UserId, Privilege, PrivilegeResults);
	}
}

FReply FShooterMainMenu::OnConfirmGeneric()
{
	UShooterGameViewportClient* ShooterViewport = Cast<UShooterGameViewportClient>(GameInstance->GetGameViewportClient());
	if (ShooterViewport)
	{
		ShooterViewport->HideDialog();
	}

	return FReply::Handled();
}

void FShooterMainMenu::BeginQuickMatchSearch()
{
	auto Sessions = Online::GetSessionInterface();
	if(!Sessions.IsValid())
	{
		UE_LOG(LogOnline, Warning, TEXT("Quick match is not supported: couldn't find online session interface."));
		return;
	}

	if (GetPlayerOwnerControllerId() == -1)
	{
		UE_LOG(LogOnline, Warning, TEXT("Quick match is not supported: Could not get controller id from player owner"));
		return;
	}

	QuickMatchSearchSettings = MakeShareable(new FShooterOnlineSearchSettings(false, true));
	QuickMatchSearchSettings->QuerySettings.Set(SEARCH_XBOX_LIVE_HOPPER_NAME, FString("TeamDeathmatch"), EOnlineComparisonOp::Equals);
	QuickMatchSearchSettings->QuerySettings.Set(SEARCH_XBOX_LIVE_SESSION_TEMPLATE_NAME, FString("MatchSession"), EOnlineComparisonOp::Equals);
	QuickMatchSearchSettings->TimeoutInSeconds = 120.0f;

	FShooterOnlineSessionSettings SessionSettings(false, true, 8);
	SessionSettings.Set(SETTING_GAMEMODE, FString("TDM"), EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_MATCHING_HOPPER, FString("TeamDeathmatch"), EOnlineDataAdvertisementType::DontAdvertise);
	SessionSettings.Set(SETTING_MATCHING_TIMEOUT, 120.0f, EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_SESSION_TEMPLATE_NAME, FString("GameSession"), EOnlineDataAdvertisementType::DontAdvertise);

	auto QuickMatchSearchSettingsRef = QuickMatchSearchSettings.ToSharedRef();
	
	DisplayQuickmatchSearchingUI();

	Sessions->ClearOnMatchmakingCompleteDelegate_Handle(OnMatchmakingCompleteDelegateHandle);
	OnMatchmakingCompleteDelegateHandle = Sessions->AddOnMatchmakingCompleteDelegate_Handle(OnMatchmakingCompleteDelegate);

	// Perform matchmaking with all local players
	TArray<TSharedRef<const FUniqueNetId>> LocalPlayerIds;
	for (int32 i = 0; i < GameInstance->GetNumLocalPlayers(); ++i)
	{
		FUniqueNetIdRepl PlayerId = GameInstance->GetLocalPlayerByIndex(i)->GetPreferredUniqueNetId();
		if (PlayerId.IsValid())
		{
			LocalPlayerIds.Add((*PlayerId).AsShared());
		}
	}

	if (!Sessions->StartMatchmaking(LocalPlayerIds, NAME_GameSession, SessionSettings, QuickMatchSearchSettingsRef))
	{
		OnMatchmakingComplete(NAME_GameSession, false);
	}
}

void FShooterMainMenu::OnSplitScreenSelectedHostOnlineLoginRequired()
{
	IOnlineIdentityPtr Identity = IOnlineSubsystem::Get()->GetIdentityInterface();
	int32 ControllerId = GetPlayerOwner()->GetControllerId();

	if (bIsLanMatch)
	{
		Identity->Logout(ControllerId);
		OnSplitScreenSelected();
	}
	else
	{
		OnLoginCompleteDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(ControllerId, FOnLoginCompleteDelegate::CreateRaw(this, &FShooterMainMenu::OnLoginCompleteHostOnline));
		Identity->Login(ControllerId, FOnlineAccountCredentials());
	}
}

void FShooterMainMenu::OnSplitScreenSelected()
{
	if (!IsMapReady())
	{
		return;
	}

	RemoveMenuFromGameViewport();

#if PLATFORM_PS4 || MAX_LOCAL_PLAYERS == 1
	if (GameInstance.IsValid() && GameInstance->GetOnlineMode() == EOnlineMode::Online)
	{
		OnUIHostTeamDeathMatch();
	}
	else
#endif
	{
		UGameViewportClient* const GVC = GEngine->GameViewport;
		//GVC->AddViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());

		//SplitScreenLobbyWidget->Clear();
		//FSlateApplication::Get().SetKeyboardFocus(SplitScreenLobbyWidget);
	}
}

void FShooterMainMenu::OnHostOnlineSelected()
{
#if SHOOTER_CONSOLE_UI
	if (!ValidatePlayerIsSignedIn(GetPlayerOwner()))
	{
		return;
	}
#endif

	MatchType = EMatchType::Custom;

	EOnlineMode NewOnlineMode = bIsLanMatch ? EOnlineMode::LAN : EOnlineMode::Online;
	if (GameInstance.IsValid())
	{
		GameInstance->SetOnlineMode(NewOnlineMode);
	}
	//SplitScreenLobbyWidget->SetIsJoining(false);
	MenuWidget->EnterSubMenu();
}

void FShooterMainMenu::OnUserCanPlayHostOnline(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{
	CleanupOnlinePrivilegeTask();
	MenuWidget->LockControls(false);
	if (PrivilegeResults == (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures)	
	{
		OnSplitScreenSelected();
	}
	else if (GameInstance.IsValid())
	{
		GameInstance->DisplayOnlinePrivilegeFailureDialogs(UserId, Privilege, PrivilegeResults);
	}
}

void FShooterMainMenu::OnLoginCompleteHostOnline(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	IOnlineSubsystem::Get()->GetIdentityInterface()->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, OnLoginCompleteDelegateHandle);

	OnSplitScreenSelectedHostOnline();
}

void FShooterMainMenu::OnSplitScreenSelectedHostOnline()
{
#if SHOOTER_CONSOLE_UI
	if (!ValidatePlayerForOnlinePlay(GetPlayerOwner()))
	{
		return;
	}
#endif

	StartOnlinePrivilegeTask(IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate::CreateSP(this, &FShooterMainMenu::OnUserCanPlayHostOnline));
}
void FShooterMainMenu::StartOnlinePrivilegeTask(const IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate& Delegate)
{
	if (GameInstance.IsValid())
	{
		// Lock controls for the duration of the async task
		MenuWidget->LockControls(true);
		FUniqueNetIdRepl UserId;
		if (PlayerOwner.IsValid())
		{
			UserId = PlayerOwner->GetPreferredUniqueNetId();
		}
		GameInstance->StartOnlinePrivilegeTask(Delegate, EUserPrivileges::CanPlayOnline, UserId.GetUniqueNetId());
	}	
}

void FShooterMainMenu::CleanupOnlinePrivilegeTask()
{
	if (GameInstance.IsValid())
	{
		GameInstance->CleanupOnlinePrivilegeTask();
	}
}

void FShooterMainMenu::OnHostOfflineSelected()
{
	MatchType = EMatchType::Custom;

#if LOGIN_REQUIRED_FOR_ONLINE_PLAY
	IOnlineSubsystem::Get()->GetIdentityInterface()->Logout(GetPlayerOwner()->GetControllerId());
#endif

	if (GameInstance.IsValid())
	{
		GameInstance->SetOnlineMode(EOnlineMode::Offline);
	}
	//SplitScreenLobbyWidget->SetIsJoining( false );

	MenuWidget->EnterSubMenu();
}

FReply FShooterMainMenu::OnSplitScreenBackedOut()
{	
	//SplitScreenLobbyWidget->Clear();
	SplitScreenBackedOut();
	return FReply::Handled();
}

FReply FShooterMainMenu::OnSplitScreenPlay()
{
	switch ( MatchType )
	{
		case EMatchType::Custom:
		{
#if SHOOTER_CONSOLE_UI
			//if ( SplitScreenLobbyWidget->GetIsJoining() )
			{
#if 1
				// Until we can make split-screen menu support sub-menus, we need to do it this way
				if (GEngine && GEngine->GameViewport)
				{
					//GEngine->GameViewport->RemoveViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());
				}
				AddMenuToGameViewport();

				FSlateApplication::Get().SetKeyboardFocus(MenuWidget);	

				// Grab the map filter if there is one
				FString SelectedMapFilterName = TEXT("ANY");
				if (JoinMapOption.IsValid())
				{
					int32 FilterChoice = JoinMapOption->SelectedMultiChoice;
					if (FilterChoice != INDEX_NONE)
					{
						SelectedMapFilterName = JoinMapOption->MultiChoice[FilterChoice].ToString();
					}
				}


				MenuWidget->NextMenu = JoinServerItem->SubMenu;
				ServerListWidget->BeginServerSearch(bIsLanMatch, bIsDedicatedServer, SelectedMapFilterName);
				ServerListWidget->UpdateServerList();
				MenuWidget->EnterSubMenu();
#else
				//SplitScreenLobbyWidget->NextMenu = JoinServerItem->SubMenu;
				ServerListWidget->BeginServerSearch(bIsLanMatch, bIsDedicatedServer, SelectedMapFilterName);
				ServerListWidget->UpdateServerList();
				//SplitScreenLobbyWidget->EnterSubMenu();
#endif
			}
			break; // I have no idea
#endif
			{
				if (GEngine && GEngine->GameViewport)
				{
					//GEngine->GameViewport->RemoveViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());
				}
				OnUIHostTeamDeathMatch();
			}
			break;
		}

		case EMatchType::Quick:
		{
			if (GEngine && GEngine->GameViewport)
			{
				//GEngine->GameViewport->RemoveViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());
			}
			BeginQuickMatchSearch();
			break;
		}
	}

	return FReply::Handled();
}

void FShooterMainMenu::SplitScreenBackedOut()
{
	if (GEngine && GEngine->GameViewport)
	{
		//GEngine->GameViewport->RemoveViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());	
	}
	AddMenuToGameViewport();

	FSlateApplication::Get().SetKeyboardFocus(MenuWidget);	
}

void FShooterMainMenu::HelperQuickMatchSearchingUICancel(bool bShouldRemoveSession)
{
	auto Sessions = Online::GetSessionInterface();
	if (bShouldRemoveSession && Sessions.IsValid())
	{
		if (PlayerOwner.IsValid() && PlayerOwner->GetPreferredUniqueNetId().IsValid())
		{
			UGameViewportClient* const GVC = GEngine->GameViewport;
			GVC->RemoveViewportWidgetContent(QuickMatchSearchingWidgetContainer.ToSharedRef());
			GVC->AddViewportWidgetContent(QuickMatchStoppingWidgetContainer.ToSharedRef());
			FSlateApplication::Get().SetKeyboardFocus(QuickMatchStoppingWidgetContainer);
			
			OnCancelMatchmakingCompleteDelegateHandle = Sessions->AddOnCancelMatchmakingCompleteDelegate_Handle(OnCancelMatchmakingCompleteDelegate);
			Sessions->CancelMatchmaking(*PlayerOwner->GetPreferredUniqueNetId(), NAME_GameSession);
		}
	}
	else
	{
		UGameViewportClient* const GVC = GEngine->GameViewport;
		GVC->RemoveViewportWidgetContent(QuickMatchSearchingWidgetContainer.ToSharedRef());
		AddMenuToGameViewport();
		FSlateApplication::Get().SetKeyboardFocus(MenuWidget);
	}
}

FReply FShooterMainMenu::OnQuickMatchSearchingUICancel()
{
	HelperQuickMatchSearchingUICancel(true);
	bUsedInputToCancelQuickmatchSearch = true;
	bQuickmatchSearchRequestCanceled = true;
	return FReply::Handled();
}

FReply FShooterMainMenu::OnQuickMatchFailureUICancel()
{
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(QuickMatchFailureWidgetContainer.ToSharedRef());
	}
	AddMenuToGameViewport();
	FSlateApplication::Get().SetKeyboardFocus(MenuWidget);
	return FReply::Handled();
}

void FShooterMainMenu::DisplayQuickmatchFailureUI()
{
	UGameViewportClient* const GVC = GEngine->GameViewport;
	RemoveMenuFromGameViewport();
	GVC->AddViewportWidgetContent(QuickMatchFailureWidgetContainer.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(QuickMatchFailureWidget);
}

void FShooterMainMenu::DisplayQuickmatchSearchingUI()
{
	UGameViewportClient* const GVC = GEngine->GameViewport;
	RemoveMenuFromGameViewport();
	GVC->AddViewportWidgetContent(QuickMatchSearchingWidgetContainer.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(QuickMatchSearchingWidget);
	bAnimateQuickmatchSearchingUI = true;
}

void FShooterMainMenu::DisplayTestMessage()
{
	UGameViewportClient* const GVC = GEngine->GameViewport;
	RemoveMenuFromGameViewport();
	GVC->AddViewportWidgetContent(TestMessageWidgetContainer.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(TestMessageWidget);
	bAnimateQuickmatchSearchingUI = true;
}

void FShooterMainMenu::OnMatchmakingComplete(FName SessionName, bool bWasSuccessful)
{
	auto SessionInterface = Online::GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogOnline, Warning, TEXT("OnMatchmakingComplete: Couldn't find session interface."));
		return;
	}

	SessionInterface->ClearOnMatchmakingCompleteDelegate_Handle(OnMatchmakingCompleteDelegateHandle);

	if (bQuickmatchSearchRequestCanceled && bUsedInputToCancelQuickmatchSearch)
	{
		bQuickmatchSearchRequestCanceled = false;
		// Clean up the session in case we get this event after canceling
		auto Sessions = Online::GetSessionInterface();
		if (bWasSuccessful && Sessions.IsValid())
		{
			if (PlayerOwner.IsValid() && PlayerOwner->GetPreferredUniqueNetId().IsValid())
			{
				Sessions->DestroySession(NAME_GameSession);
			}
		}
		return;
	}

	if (bAnimateQuickmatchSearchingUI)
	{
		bAnimateQuickmatchSearchingUI = false;
		HelperQuickMatchSearchingUICancel(false);
		bUsedInputToCancelQuickmatchSearch = false;
	}
	else
	{
		return;
	}

	if (!bWasSuccessful)
	{
		UE_LOG(LogOnline, Warning, TEXT("Matchmaking was unsuccessful."));
		DisplayQuickmatchFailureUI();
		return;
	}

	UE_LOG(LogOnline, Log, TEXT("Matchmaking successful! Session name is %s."), *SessionName.ToString());

	if (GetPlayerOwner() == NULL)
	{
		UE_LOG(LogOnline, Warning, TEXT("OnMatchmakingComplete: No owner."));
		return;
	}

	auto MatchmadeSession = SessionInterface->GetNamedSession(SessionName);

	if (!MatchmadeSession)
	{
		UE_LOG(LogOnline, Warning, TEXT("OnMatchmakingComplete: No session."));
		return;
	}

	if(!MatchmadeSession->OwningUserId.IsValid())
	{
		UE_LOG(LogOnline, Warning, TEXT("OnMatchmakingComplete: No session owner/host."));
		return;
	}

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(QuickMatchSearchingWidgetContainer.ToSharedRef());
	}
	bAnimateQuickmatchSearchingUI = false;

	UE_LOG(LogOnline, Log, TEXT("OnMatchmakingComplete: Session host is %d."), *MatchmadeSession->OwningUserId->ToString());

	if (ensure(GameInstance.IsValid()))
	{
		MenuWidget->LockControls(true);

		auto Subsystem = IOnlineSubsystem::Get();
		if (Subsystem != nullptr && Subsystem->IsLocalPlayer(*MatchmadeSession->OwningUserId))
		{
			// This console is the host, start the map.
			GameInstance->BeginHostingQuickMatch();
		}
		else
		{
			// We are the client, join the host.
			GameInstance->TravelToSession(SessionName);
		}
	}
}

FShooterMainMenu::EMap FShooterMainMenu::GetSelectedMap() const
{
	if (GameInstance.IsValid() && GameInstance->GetOnlineMode() != EOnlineMode::Offline && HostOnlineMapOption.IsValid())
	{
		return (EMap)HostOnlineMapOption->SelectedMultiChoice;
	}
	else if (HostOfflineMapOption.IsValid())
	{
		return (EMap)HostOfflineMapOption->SelectedMultiChoice;
	}

	return EMap::EHighRise;	// Need to return something (we can hit this path in cooking)
}

void FShooterMainMenu::CloseSubMenu()
{
	MenuWidget->MenuGoBack(true);
}

void FShooterMainMenu::OnMenuGoBack(MenuPtr Menu)
{
	// if we are going back from options menu
	if (ShooterOptions->OptionsItem->SubMenu == Menu)
	{
		ShooterOptions->RevertChanges();
	}

	// In case a Play Together event was received, don't act on it
	// if the player changes their mind.
	if (HostOnlineMenuItem.IsValid() && HostOnlineMenuItem->SubMenu == Menu)
	{
		GameInstance->ResetPlayTogetherInfo();
	}

	// if we've backed all the way out we need to make sure online is false.
	if (MenuWidget->GetMenuLevel() == 1)
	{
		GameInstance->SetOnlineMode(EOnlineMode::Offline);
	}

	if (StoreItem->SubMenu == Menu)
	{
		CoinsWidgetContainer->SetVisibility(EVisibility::Collapsed);
	}
}

void FShooterMainMenu::BotCountOptionChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex)
{
	BotsCountOpt = MultiOptionIndex;

	if(GetPersistentUser())
	{
		GetPersistentUser()->SetBotsCount(BotsCountOpt);
	}
}

void FShooterMainMenu::LanMatchChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex)
{
	if (HostLANItem.IsValid())
	{
		HostLANItem->SelectedMultiChoice = MultiOptionIndex;
	}

	check(JoinLANItem.IsValid());
	JoinLANItem->SelectedMultiChoice = MultiOptionIndex;
	bIsLanMatch = MultiOptionIndex > 0;
	UShooterGameUserSettings* UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
	UserSettings->SetLanMatch(bIsLanMatch);

	EOnlineMode NewOnlineMode = bIsLanMatch ? EOnlineMode::LAN : EOnlineMode::Online;
	if (GameInstance.IsValid())
	{
		GameInstance->SetOnlineMode(NewOnlineMode);
	}
}

void FShooterMainMenu::DedicatedServerChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex)
{
	check(DedicatedItem.IsValid());
	DedicatedItem->SelectedMultiChoice = MultiOptionIndex;
	bIsDedicatedServer = MultiOptionIndex > 0;
	UShooterGameUserSettings* UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
	UserSettings->SetDedicatedServer(bIsDedicatedServer);
}

void FShooterMainMenu::RecordDemoChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex)
{
	if (RecordDemoItem.IsValid())
	{
		RecordDemoItem->SelectedMultiChoice = MultiOptionIndex;
	}

	bIsRecordingDemo = MultiOptionIndex > 0;

	if(GetPersistentUser())
	{
		GetPersistentUser()->SetIsRecordingDemos(bIsRecordingDemo);
		GetPersistentUser()->SaveIfDirty();
	}
}

void FShooterMainMenu::OnUIMenuGoBack()
{
	MenuWidget->MenuGoBack();
}

void FShooterMainMenu::OnUIHostFreeForAll()
{
#if WITH_EDITOR
	if (GIsEditor == true)
	{
		return;
	}
#endif
	if (!IsMapReady())
	{
		return;
	}

#if !SHOOTER_CONSOLE_UI
	if (GameInstance.IsValid())
	{
		GameInstance->SetOnlineMode(bIsLanMatch ? EOnlineMode::LAN : EOnlineMode::Online);
	}
#endif

	MenuWidget->LockControls(true);
	MenuWidget->HideMenu();

	UWorld* const World = GameInstance.IsValid() ? GameInstance->GetWorld() : nullptr;
	if (World && GetPlayerOwnerControllerId() != -1)
	{
	const FShooterMenuSoundsStyle& MenuSounds = FShooterStyle::Get().GetWidgetStyle<FShooterMenuSoundsStyle>("DefaultShooterMenuSoundsStyle");
		MenuHelper::PlaySoundAndCall(World, MenuSounds.StartGameSound, GetPlayerOwnerControllerId(), this, &FShooterMainMenu::HostFreeForAll);
	}
}

void FShooterMainMenu::OnUIHostTeamDeathMatch()
{
#if WITH_EDITOR
	if (GIsEditor == true)
	{
		return;
	}
#endif
	if (!IsMapReady())
	{
		return;
	}

#if !SHOOTER_CONSOLE_UI
	if (GameInstance.IsValid())
	{
		GameInstance->SetOnlineMode(bIsLanMatch ? EOnlineMode::LAN : EOnlineMode::Online);
	}
#endif

	MenuWidget->LockControls(true);
	MenuWidget->HideMenu();

	UWorld* const World = GameInstance.IsValid() ? GameInstance->GetWorld() : nullptr;
	if (World && GetPlayerOwnerControllerId() != -1)
	{
	const FShooterMenuSoundsStyle& MenuSounds = FShooterStyle::Get().GetWidgetStyle<FShooterMenuSoundsStyle>("DefaultShooterMenuSoundsStyle");
		MenuHelper::PlaySoundAndCall(World, MenuSounds.StartGameSound, GetPlayerOwnerControllerId(), this, &FShooterMainMenu::HostTeamDeathMatch);
	}
}

void FShooterMainMenu::HostGame(const FString& GameType)
{	
	if (ensure(GameInstance.IsValid()) && GetPlayerOwner() != NULL)
	{
		FString const StartURL = FString::Printf(TEXT("/Game/Maps/%s?game=%s%s%s?%s=%d%s"), *GetMapName(), *GameType, GameInstance->GetOnlineMode() != EOnlineMode::Offline ? TEXT("?listen") : TEXT(""), GameInstance->GetOnlineMode() == EOnlineMode::LAN ? TEXT("?bIsLanMatch") : TEXT(""), *AShooterGameMode::GetBotsCountOptionName(), BotsCountOpt, bIsRecordingDemo ? TEXT("?DemoRec") : TEXT("") );

		// Game instance will handle success, failure and dialogs
		GameInstance->HostGame(GetPlayerOwner(), GameType, StartURL);
	}
}

void FShooterMainMenu::HostFreeForAll()
{
	HostGame(TEXT("FFA"));
}

void FShooterMainMenu::HostTeamDeathMatch()
{
	HostGame(TEXT("TDM"));
}

FReply FShooterMainMenu::OnConfirm()
{
	if (GEngine && GEngine->GameViewport)
	{
		UShooterGameViewportClient * ShooterViewport = Cast<UShooterGameViewportClient>(GEngine->GameViewport);

		if (ShooterViewport)
		{
			// Hide the previous dialog
			ShooterViewport->HideDialog();
		}
	}

	return FReply::Handled();
}

bool FShooterMainMenu::ValidatePlayerForOnlinePlay(ULocalPlayer* LocalPlayer)
{
	if (!ensure(GameInstance.IsValid()))
	{
		return false;
	}

	return GameInstance->ValidatePlayerForOnlinePlay(LocalPlayer);
}

bool FShooterMainMenu::ValidatePlayerIsSignedIn(ULocalPlayer* LocalPlayer)
{
	if (!ensure(GameInstance.IsValid()))
	{
		return false;
	}

	return GameInstance->ValidatePlayerIsSignedIn(LocalPlayer);
}

void FShooterMainMenu::OnJoinServerLoginRequired()
{
	IOnlineIdentityPtr Identity = IOnlineSubsystem::Get()->GetIdentityInterface();
	int32 ControllerId = GetPlayerOwner()->GetControllerId();

	if (bIsLanMatch)
	{
		Identity->Logout(ControllerId);
		OnUserCanPlayOnlineJoin(*GetPlayerOwner()->GetCachedUniqueNetId(), EUserPrivileges::CanPlayOnline, (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures);
	}
	else
	{
		OnLoginCompleteDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(ControllerId, FOnLoginCompleteDelegate::CreateRaw(this, &FShooterMainMenu::OnLoginCompleteJoin));
		Identity->Login(ControllerId, FOnlineAccountCredentials());
	}
}

void FShooterMainMenu::OnLoginCompleteJoin(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	IOnlineSubsystem::Get()->GetIdentityInterface()->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, OnLoginCompleteDelegateHandle);

	OnJoinServer();
}

void FShooterMainMenu::OnJoinSelected()
{
#if SHOOTER_CONSOLE_UI
	if (!ValidatePlayerIsSignedIn(GetPlayerOwner()))
	{
		return;
	}
#endif

	MenuWidget->EnterSubMenu();
}

void FShooterMainMenu::OnJoinServer()
{
#if SHOOTER_CONSOLE_UI
	if ( !ValidatePlayerForOnlinePlay(GetPlayerOwner()) )
	{
		return;
	}
#endif

	StartOnlinePrivilegeTask(IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate::CreateSP(this, &FShooterMainMenu::OnUserCanPlayOnlineJoin));
}

void FShooterMainMenu::OnUserCanPlayOnlineJoin(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{
	CleanupOnlinePrivilegeTask();
	MenuWidget->LockControls(false);

	if (PrivilegeResults == (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures)
	{

		//make sure to switch to custom match type so we don't instead use Quick type
		MatchType = EMatchType::Custom;

		if (GameInstance.IsValid())
		{
			GameInstance->SetOnlineMode(bIsLanMatch ? EOnlineMode::LAN : EOnlineMode::Online);
		}

		MatchType = EMatchType::Custom;
		// Grab the map filter if there is one
		FString SelectedMapFilterName("Any");
		if( JoinMapOption.IsValid())
		{
			int32 FilterChoice = JoinMapOption->SelectedMultiChoice;
			if( FilterChoice != INDEX_NONE )
			{
				SelectedMapFilterName = JoinMapOption->MultiChoice[FilterChoice].ToString();
			}
		}

#if SHOOTER_CONSOLE_UI
		UGameViewportClient* const GVC = GEngine->GameViewport;
#if PLATFORM_PS4 || MAX_LOCAL_PLAYERS == 1
		// Show server menu (skip splitscreen)
		AddMenuToGameViewport();
		FSlateApplication::Get().SetKeyboardFocus(MenuWidget);

		MenuWidget->NextMenu = JoinServerItem->SubMenu;
		ServerListWidget->BeginServerSearch(bIsLanMatch, bIsDedicatedServer, SelectedMapFilterName);
		ServerListWidget->UpdateServerList();
		MenuWidget->EnterSubMenu();
#else
		// Show splitscreen menu
		RemoveMenuFromGameViewport();	
		//GVC->AddViewportWidgetContent(SplitScreenLobbyWidgetContainer.ToSharedRef());

		//SplitScreenLobbyWidget->Clear();
		//FSlateApplication::Get().SetKeyboardFocus(SplitScreenLobbyWidget);

		//SplitScreenLobbyWidget->SetIsJoining( true );
#endif
#else
		MenuWidget->NextMenu = JoinServerItem->SubMenu;
		//FString SelectedMapFilterName = JoinMapOption->MultiChoice[JoinMapOption->SelectedMultiChoice].ToString();

		ServerListWidget->BeginServerSearch(bIsLanMatch, bIsDedicatedServer, SelectedMapFilterName);
		ServerListWidget->UpdateServerList();
		MenuWidget->EnterSubMenu();
#endif
	}
	else if (GameInstance.IsValid())
	{
		GameInstance->DisplayOnlinePrivilegeFailureDialogs(UserId, Privilege, PrivilegeResults);
	}
}

void FShooterMainMenu::OnShowLeaderboard()
{
	MenuWidget->NextMenu = LeaderboardItem->SubMenu;
#if LOGIN_REQUIRED_FOR_ONLINE_PLAY
	LeaderboardWidget->ReadStatsLoginRequired();
#else
	LeaderboardWidget->ReadStats();
#endif
	MenuWidget->EnterSubMenu();
}

//void FShooterMainMenu::OnShowLobby()
//{
//	if (!AccelByte::FRegistry::Lobby.IsConnected())
//	{
//		AccelByte::FRegistry::Lobby.Connect();
//		return;
//	}
//
//	const FShooterMenuStyle *MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
//	ChangeBackground(MenuStyle->LobbyBackground);
//
//	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
//	MenuWidget->NextMenu = LobbyMenuItem->SubMenu;
//	MenuWidget->EnterSubMenu();
//}

void FShooterMainMenu::OnShowOption()
{
	MenuWidget->NextMenu = ShooterOptions->OptionsItem->SubMenu;
	MenuWidget->EnterSubMenu();

	const FShooterMenuStyle *MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
	ChangeBackground(MenuStyle->OptionBackground);
}

void FShooterMainMenu::ChangeBackground(UMaterialInterface* Material)
{
	UWorld* const World = GameInstance.IsValid() ? GameInstance->GetWorld() : nullptr;
	for (TActorIterator<AStaticMeshActor> Iterator(World); Iterator; ++Iterator)
	{
		AStaticMeshActor *Current = *Iterator;
		if (Current->GetName().Contains(TEXT("EditorPlane")))
		{
			if (Material)
			{
				UMaterialInterface* Mat = Iterator->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0, Material);
				if (Mat)
				{
					Current->GetStaticMeshComponent()->CreateAndSetMaterialInstanceDynamicFromMaterial(0, Mat);
				}
			}
		}
	}

}

void FShooterMainMenu::RefreshWallet()
{
	FRegistry::Wallet.GetWalletInfoByCurrencyCode(TEXT("SGC"),
		AccelByte::THandler<FAccelByteModelsWalletInfo>::CreateSP(this, &FShooterMainMenu::OnGetWalletSuccess),
		FErrorHandler::CreateSP(this, &FShooterMainMenu::OnGetWalletError));
}

void FShooterMainMenu::OnGetWalletSuccess(const FAccelByteModelsWalletInfo& Response)
{
	CoinsWidgetContainer->Balance = Response.Balance;
}

void FShooterMainMenu::OnGetWalletError(int32 Code, const FString& Message)
{
	CoinsWidgetContainer->Balance = -1;
}

void FShooterMainMenu::OnShowInventory()
{
	const FShooterMenuStyle *MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
	ChangeBackground(MenuStyle->InventoryBackground);
	MenuWidget->NextMenu = InventoryItem->SubMenu;
	InventoryWidget->BuildInventoryItem();
	MenuWidget->EnterSubMenu();
}

void FShooterMainMenu::OnShowStore()
{
	const FShooterMenuStyle *MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
	ChangeBackground(MenuStyle->StoreBackground);
	MenuWidget->NextMenu = StoreItem->SubMenu;
	StoreWidget->BuildInventoryItem();
	MenuWidget->EnterSubMenu();
	CoinsWidgetContainer->SetVisibility(EVisibility::Visible);
}

void FShooterMainMenu::OnUIQuit()
{
	LockAndHideMenu();

	const FShooterMenuSoundsStyle& MenuSounds = FShooterStyle::Get().GetWidgetStyle<FShooterMenuSoundsStyle>("DefaultShooterMenuSoundsStyle");
	UWorld* const World = GameInstance.IsValid() ? GameInstance->GetWorld() : nullptr;
	if (World != NULL && GetPlayerOwnerControllerId() != -1)
	{
		FSlateApplication::Get().PlaySound(MenuSounds.ExitGameSound, GetPlayerOwnerControllerId());
		MenuHelper::PlaySoundAndCall(World, MenuSounds.ExitGameSound, GetPlayerOwnerControllerId(), this, &FShooterMainMenu::Quit);
	}
}

void FShooterMainMenu::Quit()
{
	if (ensure(GameInstance.IsValid()))
	{
		UGameViewportClient* const Viewport = GameInstance->GetGameViewportClient();
		if (ensure(Viewport)) 
		{
			Viewport->ConsoleCommand("quit");
		}
	}
}

void FShooterMainMenu::LockAndHideMenu()
{
	MenuWidget->LockControls(true);
	MenuWidget->HideMenu();
}

void FShooterMainMenu::DisplayLoadingScreen()
{
	IShooterGameLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<IShooterGameLoadingScreenModule>("ShooterGameLoadingScreen");
	if( LoadingScreenModule != NULL )
	{
		LoadingScreenModule->StartInGameLoadingScreen();
	}
}

bool FShooterMainMenu::IsMapReady() const
{
	bool bReady = true;
	IPlatformChunkInstall* ChunkInstaller = FPlatformMisc::GetPlatformChunkInstall();
	if (ChunkInstaller)
	{
		EMap SelectedMap = GetSelectedMap();
		// should use the AssetRegistry as soon as maps are added to the AssetRegistry
		int32 MapChunk = ChunkMapping[(int)SelectedMap];
		EChunkLocation::Type ChunkLocation = ChunkInstaller->GetPakchunkLocation(MapChunk);
		if (ChunkLocation == EChunkLocation::NotAvailable)
		{			
			bReady = false;
		}
	}
	return bReady;
}

UShooterPersistentUser* FShooterMainMenu::GetPersistentUser() const
{
	UShooterLocalPlayer* const ShooterLocalPlayer = Cast<UShooterLocalPlayer>(GetPlayerOwner());
	return ShooterLocalPlayer ? ShooterLocalPlayer->GetPersistentUser() : nullptr;
}

UWorld* FShooterMainMenu::GetTickableGameObjectWorld() const
{
	ULocalPlayer* LocalPlayerOwner = GetPlayerOwner();
	return (LocalPlayerOwner ? LocalPlayerOwner->GetWorld() : nullptr);
}

ULocalPlayer* FShooterMainMenu::GetPlayerOwner() const
{
	return PlayerOwner.Get();
}

int32 FShooterMainMenu::GetPlayerOwnerControllerId() const
{
	return ( PlayerOwner.IsValid() ) ? PlayerOwner->GetControllerId() : -1;
}

FString FShooterMainMenu::GetMapName() const
{
	 return MapNames[(int)GetSelectedMap()];
}

void FShooterMainMenu::OnCancelMatchmakingComplete(FName SessionName, bool bWasSuccessful)
{
	auto Sessions = Online::GetSessionInterface();
	if(Sessions.IsValid())
	{
		Sessions->ClearOnCancelMatchmakingCompleteDelegate_Handle(OnCancelMatchmakingCompleteDelegateHandle);
	}

	bAnimateQuickmatchSearchingUI = false;
	UGameViewportClient* const GVC = GEngine->GameViewport;
	GVC->RemoveViewportWidgetContent(QuickMatchStoppingWidgetContainer.ToSharedRef());
	AddMenuToGameViewport();
	FSlateApplication::Get().SetKeyboardFocus(MenuWidget);
}

void FShooterMainMenu::OnPlayTogetherEventReceived()
{
	HostOnlineMenuItem->Widget->SetMenuItemActive(true);
	MenuWidget->ConfirmMenuItem();
}

void FShooterMainMenu::DsRegionOptionChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex)
{
	if (DsRegionLatencies.Num() > 0 && DsRegionLatencies.Num() > MultiOptionIndex && MultiOptionIndex >= 0)
	{
		auto selection = DsRegionLatencies[MultiOptionIndex];
		ShooterGameConfig::Get().SelectRegion(selection);
	}
}

void FShooterMainMenu::GetQoS()
{
	const FShooterMenuSoundsStyle& MenuSounds = FShooterStyle::Get().GetWidgetStyle<FShooterMenuSoundsStyle>("DefaultShooterMenuSoundsStyle");
	FSlateApplication::Get().PlaySound(MenuSounds.ExitGameSound, GetPlayerOwnerControllerId());

	FRegistry::Qos.GetServerLatencies(
		THandler<TArray<TPair<FString, float>>>::CreateLambda([&](TArray<TPair<FString, float>> Result) {
			ShooterGameConfig::Get().SetServerLatencies(Result);
			PopulateRegionLatencies(Result);

			// Then back to main menu
			MenuWidget->NextMenu = MenuWidget->MainMenu;
			MenuWidget->EnterSubMenu();
			//const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");
			//ChangeBackground(LobbyStyle->MainMenuMaterial);
			FSlateApplication::Get().PlaySound(MenuSounds.StartGameSound, GetPlayerOwnerControllerId());

			}),
		AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
				UE_LOG(LogTemp, Log, TEXT("Could not obtain server latencies from QoS endpoint. ErrorCode: %d\nMessage:%s"), ErrorCode, *ErrorString);
			}));
}

void FShooterMainMenu::PopulateRegionLatencies(TArray<TPair<FString, float>> value)
{
	DsRegionLatencies = value;
	DsRegionLatenciesText.Empty();
	for (auto& server : ShooterGameConfig::Get().ServerLatencies_)
	{
		FString serverAsString = FString::Printf(TEXT("%s - %.0fms"), *server.Key, server.Value);
		DsRegionLatenciesText.Add(FText::FromString(serverAsString));
	}

	// IF there's no available region
	if (DsRegionLatencies.Num() == 0)
	{
		ShooterGameConfig::Get().SetServerLatencies({ TPair<FString, float>{ "UNAVAILABLE", -1.f } });
	}

	// If valid, select the left-most region
	if (DsRegionOption.IsValid())
	{
		// Update Value
		DsRegionOption->SelectedMultiChoice = 0;
		ShooterGameConfig::Get().SelectRegion(DsRegionLatencies[0]);

		// Update visible UI & the values
		DsRegionOption->Widget->LeftArrowVisible = EVisibility::Collapsed;
		DsRegionOption->Widget->RightArrowVisible = EVisibility::Visible;
		DsRegionOption->MultiChoice.Reset();
		DsRegionOption->MultiChoice = DsRegionLatenciesText;
	}
}
#undef LOCTEXT_NAMESPACE
