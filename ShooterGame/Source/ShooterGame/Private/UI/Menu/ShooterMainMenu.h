// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Utils/ImageUtils.h"

// TODO: Refactor into UMG
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Widgets/ShooterMenuItem.h"
#include "Widgets/SShooterMenuWidget.h"
#include "Widgets/SShooterCoinsWidget.h"
#include "Widgets/SShooterServerList.h"
#include "Widgets/SShooterDemoList.h"
#include "Widgets/SShooterInventory.h"
#include "Widgets/SShooterStore.h"
#include "Widgets/SShooterLeaderboard.h"
//#include "Widgets/SLobby.h"
//#include "Widgets/SShooterSplitScreenLobbyWidget.h"
#include "ShooterOptions.h"

#include "Api/AccelByteWalletApi.h"

class FShooterMainMenu : public TSharedFromThis<FShooterMainMenu>, public FTickableGameObject
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	*/
	FShooterMainMenu(TWeakObjectPtr<class UShooterGameInstance> _GameInstance);

	virtual ~FShooterMainMenu();

	/** Construct menu.	*/
	void Construct(TWeakObjectPtr<ULocalPlayer> _PlayerOwner);

	/** Teardown menu. */
	void Teardown();

	// TODO: Refactor into UMG

	/** Add the menu to the gameviewport so it becomes visible */
	void AddMenuToGameViewport();

	/** Remove from the gameviewport. */
	void RemoveMenuFromGameViewport();	

	/** TickableObject Functions */
	virtual void Tick(float DeltaTime) override;	
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableWhenPaused() const override { return true; }	
	virtual UWorld* GetTickableGameObjectWorld() const override;

	/** Returns the player that owns the main menu. */
	ULocalPlayer* GetPlayerOwner() const;

	/** Returns the controller id of player that owns the main menu. */
	int32 GetPlayerOwnerControllerId() const;

	/** Returns the string name of the currently selected map */
	FString GetMapName() const;

	/** Called if a play together invite is sent from the PS4 system */
	void OnPlayTogetherEventReceived();

protected:

	enum class EMap
	{
		/*ESancturary,*/
		EHighRise,
		EMax,
	};	

	enum class EMatchType
	{
		Custom,
		Quick
	};
	
	/** Owning player */
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;

	/** shooter options */
	TSharedPtr<class FShooterOptions> ShooterOptions;

	/** menu widget */
	TSharedPtr<class SShooterMenuWidget> MenuWidget;

	/** menu widget */
	TSharedPtr<class SShooterCoinsWidget> CoinsWidgetContainer;

	/* used for removing the MenuWidget */
	TSharedPtr<class SWeakWidget> MenuWidgetContainer;
	TSharedPtr<class SWeakWidget> UserProfileWidgetContainer;

	/** SplitScreen Lobby Widget */
	//TSharedPtr<class SShooterSplitScreenLobby> SplitScreenLobbyWidget;

	/* used for removing the SplitScreenLobby */
	//TSharedPtr<class SWeakWidget> SplitScreenLobbyWidgetContainer;

	/** server list widget */
	TSharedPtr<class SShooterServerList> ServerListWidget;

	/** lobby friend list widget */
	//TSharedPtr<class SLobby> LobbyWidget;
	/** yet another custom menu */
	//TSharedPtr<class FShooterMenuItem> LobbyMenuItem;

	/** dedicated server region selection */
	TSharedPtr<FShooterMenuItem> DsRegionOption;
	TArray<TPair<FString, float>> DsRegionLatencies;
	TArray<FText> DsRegionLatenciesText;
	void DsRegionOptionChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex);
	void GetQoS();
	void PopulateRegionLatencies(TArray<TPair<FString, float>> value);

	/** demo list widget */
	TSharedPtr<class SShooterDemoList> DemoListWidget;

	/** inventory widget */
	TSharedPtr<class SShooterInventory> InventoryWidget;

	/** store widget */
	TSharedPtr<class SShooterStore> StoreWidget;

	/** yet another custom menu */
	TSharedPtr<class FShooterMenuItem> ScreenshotItem;

	/** leaderboard widget */
	TSharedPtr<class SShooterLeaderboard> LeaderboardWidget;

	/** custom menu */
	TSharedPtr<class FShooterMenuItem> JoinServerItem;

	/** yet another custom menu */
	TSharedPtr<class FShooterMenuItem> LeaderboardItem;

	/** Custom demo browser menu */
	TSharedPtr<class FShooterMenuItem> DemoBrowserItem;

	/** Custom inventory menu */
	TSharedPtr<class FShooterMenuItem> InventoryItem;

	/** Store menu */
	TSharedPtr<class FShooterMenuItem> StoreItem;

	TSharedPtr<class FShooterMenuItem> GameProfileItem;

	/** LAN Options */
	TSharedPtr<class FShooterMenuItem> HostLANItem;
	TSharedPtr<class FShooterMenuItem> JoinLANItem;	

	/** Dedicated Server Option */
	TSharedPtr<class FShooterMenuItem> DedicatedItem;

	/** Record demo option */
	TSharedPtr<class FShooterMenuItem> RecordDemoItem;

	/** Settings and storage for quickmatch searching */
	TSharedPtr<FOnlineSessionSearch> QuickMatchSearchSettings;

	/** Map selection widget */
	TSharedPtr<FShooterMenuItem> HostOfflineMapOption;
	TSharedPtr<FShooterMenuItem> HostOnlineMapOption;
	TSharedPtr<FShooterMenuItem> JoinMapOption;

	/** Host an onine session menu */
	TSharedPtr<FShooterMenuItem> HostOnlineMenuItem;

	/** Track if we are showing a map download pct or not. */
	bool bShowingDownloadPct;

	/** Custom match or quick match */
	EMatchType MatchType;

	EMap GetSelectedMap() const;

	/** goes back in menu structure */
	void CloseSubMenu();

	/** called when going back to previous menu */
	void OnMenuGoBack(MenuPtr Menu);

	/** called when menu hide animation is finished */
	void OnMenuHidden();

	/** called when user chooses to start matchmaking. */
	void OnQuickMatchSelected();

	/** called when user chooses to start matchmaking, but a login is required first. */
	void OnQuickMatchSelectedLoginRequired();

	/** Called when user chooses split screen for the "host online" mode. Does some validation before moving on the split screen menu widget. */
	void OnSplitScreenSelectedHostOnlineLoginRequired();

	/** Called when user chooses split screen for the "host online" mode.*/
	void OnSplitScreenSelectedHostOnline();

	/** called when user chooses split screen.  Goes to the split screen setup screen.  Hides menu widget*/
	void OnSplitScreenSelected();

	/** Called whne user selects "HOST ONLINE" */
	void OnHostOnlineSelected();

	/** Called whne user selects "HOST OFFLINE" */
	void OnHostOfflineSelected();

	/** called when users back out of split screen lobby screen.  Shows main menu again. */
	void SplitScreenBackedOut();

	FReply OnSplitScreenBackedOut();

	FReply OnSplitScreenPlay();

	void OnMatchmakingComplete(FName SessionName, bool bWasSuccessful);

	/** bot count option changed callback */
	void BotCountOptionChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex);			

	/** lan match option changed callback */
	void LanMatchChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex);

	/** dedicated server option changed callback */
	void DedicatedServerChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex);

	/** record demo option changed callback */
	void RecordDemoChanged(TSharedPtr<FShooterMenuItem> MenuItem, int32 MultiOptionIndex);

	/** Back to main menu*/
	void OnUIMenuGoBack();

	/** Plays StartGameSound sound and calls HostFreeForAll after sound is played */
	void OnUIHostFreeForAll();

	/** Plays StartGameSound sound and calls HostTeamDeathMatch after sound is played */
	void OnUIHostTeamDeathMatch();

	/** Hosts a game, using the passed in game type */
	void HostGame(const FString& GameType);

	/** Hosts free for all game */
	void HostFreeForAll();

	/** Hosts team deathmatch game */
	void HostTeamDeathMatch();

	/** General ok/cancel handler, that simply closes the dialog */
	FReply OnConfirm();

	/** Returns true if owning player is online. Displays proper messaging if the user can't play */
	bool ValidatePlayerForOnlinePlay(ULocalPlayer* LocalPlayer);

	/** Returns true if owning player is signed in to an account. Displays proper messaging if the user can't play */
	bool ValidatePlayerIsSignedIn(ULocalPlayer* LocalPlayer);

	/** Called when the join menu option is chosen */
	void OnJoinSelected();

	/** Join server, but login necessary first. */
	void OnJoinServerLoginRequired();

	/** Join server */
	void OnJoinServer();

	//void OnShowLobby();

	void OnShowOption();

	/** Show leaderboard */
	void OnShowLeaderboard();

	/** Show inventory */
	void OnShowInventory();

	/** Show store */
	void OnShowStore();

	void ChangeBackground(UMaterialInterface* Material);

	/** Plays sound and calls Quit */
	void OnUIQuit();

	/** Quits the game */
	void Quit();

	/** Lock the controls and hide the main menu */
	void LockAndHideMenu();

	/** Display the loading screen. */
	void DisplayLoadingScreen();

	/** Begins searching for a quick match (matchmaking) */
	void BeginQuickMatchSearch();

	/** Checks the ChunkInstaller to see if the selected map is ready for play */
	bool IsMapReady() const;

	/** Callback for when game is created */
	void OnGameCreated(bool bWasSuccessful);

	/** Displays the UI for when a quickmatch can not be found */
	void DisplayQuickmatchFailureUI();

	/** Displays the UI for when a quickmatch is being searched for */
	void DisplayQuickmatchSearchingUI();

	/** Display the loading screen. */
	void DisplayTestMessage();

	/** Get the persistence user associated with PCOwner*/
	UShooterPersistentUser* GetPersistentUser() const;

	/** Start the check for whether the owner of the menu has online privileges */
	void StartOnlinePrivilegeTask(const IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate& Delegate);

	/** Common cleanup code for any Privilege task delegate */
	void CleanupOnlinePrivilegeTask();

	/** Delegate function executed after checking privileges for hosting an online game */
	void OnUserCanPlayHostOnline(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults);

	/** Delegate function executed after checking privileges for joining an online game */
	void OnUserCanPlayOnlineJoin(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults);

	/** Delegate function executed after checking privileges for starting quick match */
	void OnUserCanPlayOnlineQuickMatch(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults);

	// Generic confirmation handling (just hide the dialog)
	FReply OnConfirmGeneric();	

	/** Delegate function executed when the quick match async cancel operation is complete */
	void OnCancelMatchmakingComplete(FName SessionName, bool bWasSuccessful);

	/** Delegate function executed when login completes before an online match is created */
	void OnLoginCompleteHostOnline(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	/** Delegate function executed when login completes before an online match is joined */
	void OnLoginCompleteJoin(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	/** Delegate function executed when login completes before quickmatch is started */
	void OnLoginCompleteQuickmatch(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	/** Delegate for canceling matchmaking */
	FOnCancelMatchmakingCompleteDelegate OnCancelMatchmakingCompleteDelegate;

	/** Delegate executed when matchmaking completes */
	FOnMatchmakingCompleteDelegate OnMatchmakingCompleteDelegate;

	// ACCELBYTE
	void RefreshWallet();
	void OnGetWalletSuccess(const FAccelByteModelsWalletInfo& Response);
	void OnGetWalletError(int32 Code, const FString& Message);

	/** number of bots in game */
	int32 BotsCountOpt;

	/** Length that the UI for searching for a quickmatch should animate */
	float QuickMAnimTimer;

	/** This is kind of hacky, but it's the simplest solution since we're out of time.
		JoinSession was moved to an async event in the PS4 OSS and isn't called immediately
		so we need to wait till it's triggered and then remove it */
	bool bRemoveSessionThatWeJustJoined;

	/** Custom animation var that is used to determine whether or not to inc or dec the alpha value of the quickmatch UI*/
	bool bIncQuickMAlpha;

	/** lan game? */
	bool bIsLanMatch;	

	/** Recording demos? */
	bool bIsRecordingDemo;

	/** Are we currently animating the Searching for a QuickMatch UI? */
	bool bAnimateQuickmatchSearchingUI;

	/** Was the search request for quickmatch canceled while searching? */
	bool bQuickmatchSearchRequestCanceled;

	/** Was input used to cancel the search request for quickmatch? */
	bool bUsedInputToCancelQuickmatchSearch;

	/** Dedicated server? */
	bool bIsDedicatedServer;

	/** used for displaying the quickmatch confirmation dialog when a quickmatch to join is not found */
	TSharedPtr<class SShooterConfirmationDialog> QuickMatchFailureWidget;

	/** used for displaying the quickmatch confirmation dialog when a quickmatch to join is not found */
	// buat message box
	TSharedPtr<class SShooterConfirmationDialog> TestMessageWidget;

	/** used for managing the QuickMatchFailureWidget */
	TSharedPtr<class SWeakWidget> QuickMatchFailureWidgetContainer;

	/** used for displaying UI for when we are actively searching for a quickmatch */
	TSharedPtr<class SShooterConfirmationDialog> QuickMatchSearchingWidget;

	/* used for managing the QuickMatchSearchingWidget */
	TSharedPtr<class SWeakWidget> QuickMatchSearchingWidgetContainer;	

	/* used for managing the QuickMatchStoppingWidget */
	TSharedPtr<class SShooterConfirmationDialog> QuickMatchStoppingWidget;

	/* used for displaying a message while we wait for quick match to stop searching */
	TSharedPtr<SWeakWidget> QuickMatchStoppingWidgetContainer;

	// buat message box
	TSharedPtr<SWeakWidget> TestMessageWidgetContainer;

	/** Handler for cancel confirmation confirmations on the quickmatch widgets */
	FReply OnQuickMatchFailureUICancel();
	void HelperQuickMatchSearchingUICancel(bool bShouldRemoveSession); //helper for removing QuickMatch Searching UI
	FReply OnQuickMatchSearchingUICancel();

	FDelegateHandle OnMatchmakingCompleteDelegateHandle;
	FDelegateHandle OnCancelMatchmakingCompleteDelegateHandle;
	FDelegateHandle OnLoginCompleteDelegateHandle;

private:
	/**
	* @brief Update user profile.
	*
	* @param AvatarURL Player's avatar url.
	*/
	void UpdateUserProfile(FString AvatarURL);

	/** Handle when getting player's avatar image. */
	void OnThumbImageReceived(FCacheBrush Image);

	/** Update user profile from cache. */
	void UpdateUserProfileFromCache();

	/** Owning game instance. */
	TWeakObjectPtr<UShooterGameInstance> GameInstance;

	/** Main Menu UI widget. */
	TWeakObjectPtr<class UMainMenuUI> MainMenuUI;

	/** Game profile sub-menu widget. */
	TSharedPtr<class ShooterGameProfile> GameProfile;

	/** Lobby sub-menu widget. */
	TSharedPtr<class ShooterLobby> Lobby;

	/** Gallery sub-menu widget */
	TSharedPtr<class ShooterGallery> Gallery;
};
