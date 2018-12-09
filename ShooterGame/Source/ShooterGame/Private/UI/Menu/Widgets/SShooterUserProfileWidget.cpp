// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Engine/Console.h"
#include "SShooterUserProfileWidget.h"
#include "ShooterMenuItem.h"
#include "SShooterMenuItem.h"
#include "ShooterStyle.h"
#include "ShooterMenuWidgetStyle.h"
#include "ShooterUIHelpers.h"
#include "ShooterGameInstance.h"
#include "Player/ShooterLocalPlayer.h"
#include "ShooterGameUserSettings.h"
#include "Slate/SceneViewport.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"

// accelbyte
#include "Api/AccelByteUserProfileApi.h"
#include "Core/AccelByteCredentials.h"
// accelbyte

#define LOCTEXT_NAMESPACE "SShooterUserProfileWidget"

#if PLATFORM_XBOXONE
#define PROFILE_SWAPPING	1
#else
#define PROFILE_SWAPPING	0
#endif

TSharedPtr<FSlateDynamicImageBrush> ThumbnailBrush;

void SShooterUserProfileWidget::Construct(const FArguments& InArgs)
{
	ThumbnailBrush.Reset();
	MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
	bProfileUpdated = false;
	bControlsLocked = false;
	bConsoleVisible = false;
	OutlineWidth = 20.0f;
	SelectedIndex = 0;
	PlayerOwner = InArgs._PlayerOwner;
	bGameMenu = InArgs._IsGameMenu;
	ControllerHideMenuKey = EKeys::Gamepad_Special_Right;
	Visibility.Bind(this, &SShooterUserProfileWidget::GetSlateVisibility);
	FLinearColor UserNameTextColor =  FLinearColor(FColor(142,246,255));
	FLinearColor UserIDTextColor = FLinearColor(FColor(24, 105, 112));
	MenuHeaderHeight = 62.0f;
	MenuHeaderWidth = 287.0f;


	ChildSlot
	[	
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		.Padding(TAttribute<FMargin>(this, &SShooterUserProfileWidget::GetMenuOffset))
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SBox) // box kiri, buat border image
				.WidthOverride(84.0f)
				.HeightOverride(84.0f)
				[
					SNew(SImage) // gambar avatar, klo bisa dari URL				
					.Image(FShooterStyle::Get().GetBrush("ShooterGame.ProfileBorder"))
				]
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SBox) // box kiri, buat gambar profile			
				.WidthOverride(56.0f)
				.HeightOverride(56.0f)
				[
					SNew(SImage) // gambar avatar, klo bisa dari URL				
					.Image(this, &SShooterUserProfileWidget::GetProfileAvatar)
				]
			]

		]
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		[
			SNew(SVerticalBox)					
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			.Padding(15.0f, 70.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(FShooterStyle::Get(), "ShooterGame.UsernameTextStyle")				
				.Text(this, &SShooterUserProfileWidget::GetProfileName)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)			
			.Padding(15.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(FShooterStyle::Get(), "ShooterGame.UserIDTextStyle")				
				.Text(this, &SShooterUserProfileWidget::GetProfileUserID)
			]

		]
	];
}

EVisibility SShooterUserProfileWidget::GetSlateVisibility() const
{
	return bConsoleVisible ? EVisibility::HitTestInvisible : EVisibility::Visible;
}

FText SShooterUserProfileWidget::GetMenuTitle() const 
{
	return CurrentMenuTitle;
}

FMargin SShooterUserProfileWidget::GetProfileSwapOffset() const
{
	return FMargin(0.0f, 50.0f, 50.0f, 0.0f);
}

bool SShooterUserProfileWidget::IsProfileSwapActive() const
{
#if PROFILE_SWAPPING
	// Dont' show if ingame or not on the main menu screen
	return !bGameMenu && MenuHistory.Num() == 0 ? true : false;
#else
	return false;
#endif
}

EVisibility SShooterUserProfileWidget::GetProfileSwapVisibility() const
{
	return IsProfileSwapActive() ? EVisibility::Visible : EVisibility::Collapsed;
}

const FSlateBrush* SShooterUserProfileWidget::GetProfileAvatar() const
{
	if(ThumbnailBrush.IsValid())
		return ThumbnailBrush.Get();

	return FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
}

FText SShooterUserProfileWidget::GetProfileName() const
{
	return UserName;
}

FText SShooterUserProfileWidget::GetProfileUserID() const
{
	return UserID;
}

bool SShooterUserProfileWidget::ProfileUISwap(const int ControllerIndex) const
{
	if(IsProfileSwapActive())
	{
		const FOnLoginUIClosedDelegate Delegate = FOnLoginUIClosedDelegate::CreateSP( this, &SShooterUserProfileWidget::HandleProfileUISwapClosed );
		if ( ShooterUIHelpers::Get().ProfileSwapUI(ControllerIndex, false, &Delegate) )
		{
			UShooterGameInstance* GameInstance = PlayerOwner.IsValid() ? Cast< UShooterGameInstance >( PlayerOwner->GetGameInstance() ) : nullptr;

			if ( GameInstance != nullptr )
			{
				GameInstance->SetIgnorePairingChangeForControllerId( ControllerIndex );
			}
			return true;
		}
	}
	return false;
}

void SShooterUserProfileWidget::HandleProfileUISwapClosed(TSharedPtr<const FUniqueNetId> UniqueId, const int ControllerIndex, const FOnlineError& Error)
{
	UShooterGameInstance * GameInstance = PlayerOwner.IsValid() ? Cast< UShooterGameInstance >( PlayerOwner->GetGameInstance() ) : nullptr;

	if ( GameInstance != nullptr )
	{
		GameInstance->SetIgnorePairingChangeForControllerId( -1 );
	}

	// If the id is null, the user backed out
	if( UniqueId.IsValid() && PlayerOwner.IsValid() )
	{
		// If the id is the same, the user picked the existing profile
		// (use the cached unique net id, since we want to compare to the user that was selected at "press start"
		FUniqueNetIdRepl OwnerId = PlayerOwner->GetCachedUniqueNetId();
		if( OwnerId.IsValid() && UniqueId.IsValid() && *OwnerId == *UniqueId)
		{
			return;
		}

		// Go back to the welcome screen.
		HideMenu();
	}

	UShooterLocalPlayer* LocalPlayer = Cast<UShooterLocalPlayer>(PlayerOwner.Get());
	LocalPlayer->LoadPersistentUser();
}

void SShooterUserProfileWidget::LockControls(bool bEnable)
{
	bControlsLocked = bEnable;
}

int32 SShooterUserProfileWidget::GetOwnerUserIndex()
{
	return PlayerOwner.IsValid() ? PlayerOwner->GetControllerId() : 0;
}

int32 SShooterUserProfileWidget::GetMenuLevel()
{
	return MenuHistory.Num();
}

void SShooterUserProfileWidget::BuildAndShowMenu()
{
	//grab the user settings
	UShooterGameUserSettings* UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
	ScreenRes = UserSettings->GetScreenResolution();

	//Build left menu panel
	bLeftMenuChanging = false;
	bGoingBack = false;
	BuildLeftPanel(bGoingBack);

	//sets up whole main menu animations and launches them
	SetupAnimations();

	// Set up right side and launch animation if there is any submenu
	if (CurrentMenu.Num() > 0 && CurrentMenu.IsValidIndex(SelectedIndex) && CurrentMenu[SelectedIndex]->bVisible)
	{
		NextMenu = CurrentMenu[SelectedIndex]->SubMenu;
		if (NextMenu.Num() > 0)
		{
			BuildRightPanel();
			bSubMenuChanging = true;
		}
	}

	bMenuHiding = false;
	FSlateApplication::Get().PlaySound(MenuStyle->MenuEnterSound, GetOwnerUserIndex());

	UserName = FText::FromString(TEXT("[Username]"));
	UserID = FText::FromString(TEXT("[+]"));
}

void SShooterUserProfileWidget::UpdateAvatar(FString Url)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Start Downloading avatar"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Url);
	}
	if (!bProfileUpdated)
	{
		// start download avatar
		TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
		ThumbRequest->SetVerb("GET");
		ThumbRequest->SetURL(Url);
		ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SShooterUserProfileWidget::OnThumbImageReceived);
		ThumbRequest->ProcessRequest();
	}

}

void SShooterUserProfileWidget::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TArray<uint8> ImageData = Response->GetContent();
		ThumbnailBrush = CreateBrush(Response->GetContentType(), FName(*Request->GetURL()), ImageData);
		bProfileUpdated = true;
	}
}

TSharedPtr<FSlateDynamicImageBrush> SShooterUserProfileWidget::CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData)
{
    UE_LOG(LogTemp, Log, TEXT("SShooterUserProfileWidget::CreateBrush : %s, Content Type: %s"), *ResourceName.ToString(), *ContentType);
    TSharedPtr<FSlateDynamicImageBrush> Brush;

    uint32 BytesPerPixel = 4;
    int32 Width = 0;
    int32 Height = 0;

    bool bSucceeded = false;
    TArray<uint8> DecodedImage;
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

    int BitDepth = 8;
    //jpg
    EImageFormat ImageFormat = EImageFormat::JPEG;
    ERGBFormat RgbFormat = ERGBFormat::BGRA;
    //png
    if (ContentType.Contains(TEXT("png")))
    {
        ImageFormat = EImageFormat::PNG;
        RgbFormat = ERGBFormat::BGRA;
    }
    //bmp
    else if (ContentType.Contains(TEXT("bmp")))
    {
        ImageFormat = EImageFormat::BMP;
        RgbFormat = ERGBFormat::BGRA;
    }

    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
    if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
    {
        Width = ImageWrapper->GetWidth();
        Height = ImageWrapper->GetHeight();

        const TArray<uint8>* RawData = NULL;

        if (ImageWrapper->GetRaw(RgbFormat, BitDepth, RawData))
        {
            DecodedImage = *RawData;
            bSucceeded = true;
        }
    }

    if (bSucceeded && FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), DecodedImage))
    {
        Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
    }

    return Brush;
}

void SShooterUserProfileWidget::HideMenu()
{
	if (!bMenuHiding)
	{
		if(MenuWidgetAnimation.IsAtEnd())
		{
			MenuWidgetAnimation.PlayReverse(this->AsShared());
		}
		else
		{
			MenuWidgetAnimation.Reverse();
		}
		bMenuHiding = true;
	}
}


void SShooterUserProfileWidget::SetupAnimations()
{
	//Setup a curve
	const float StartDelay = 0.0f;
	const float SecondDelay = bGameMenu ? 0.f : 0.3f;
	const float AnimDuration = 0.5f;
	const float MenuChangeDuration = 0.2f;

	//always animate the menu from the same side of the screen; it looks silly when it disappears to one place and reappears from another
	AnimNumber = 1;

	MenuWidgetAnimation = FCurveSequence();
	SubMenuWidgetAnimation = FCurveSequence();
	SubMenuScrollOutCurve = SubMenuWidgetAnimation.AddCurve(0,MenuChangeDuration,ECurveEaseFunction::QuadInOut);

	MenuWidgetAnimation = FCurveSequence();
	LeftMenuWidgetAnimation = FCurveSequence();
	LeftMenuScrollOutCurve = LeftMenuWidgetAnimation.AddCurve(0,MenuChangeDuration,ECurveEaseFunction::QuadInOut);
	LeftMenuWidgetAnimation.Play(this->AsShared());

	//Define the fade in animation
	TopColorCurve = MenuWidgetAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);

	//now, we want these to animate some time later

	//rolling out
	BottomScaleYCurve = MenuWidgetAnimation.AddCurve(StartDelay+SecondDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
	//fading in
	BottomColorCurve = MenuWidgetAnimation.AddCurve(StartDelay+SecondDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
	//moving from left side off screen
	ButtonsPosXCurve = MenuWidgetAnimation.AddCurve(StartDelay+SecondDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
}

void SShooterUserProfileWidget::BuildLeftPanel(bool bInGoingBack)
{
	if (CurrentMenu.Num() == 0)
	{
		//do not build anything if we do not have any active menu
		return;
	}
	//LeftBox->ClearChildren();
	int32 PreviousIndex = -1;
	if (bLeftMenuChanging)
	{
		if (bInGoingBack && MenuHistory.Num() > 0)
		{
			FShooterMenuInfo MenuInfo = MenuHistory.Pop();
			CurrentMenu = MenuInfo.Menu;
			CurrentMenuTitle = MenuInfo.MenuTitle;
			PreviousIndex = MenuInfo.SelectedIndex;
			if (CurrentMenu.Num() > 0 && CurrentMenu[PreviousIndex]->SubMenu.Num() > 0)
			{
				NextMenu = CurrentMenu[PreviousIndex]->SubMenu;
				bSubMenuChanging = true;
			}
		} 
		else if (PendingLeftMenu.Num() > 0)
		{
			MenuHistory.Push(FShooterMenuInfo(CurrentMenu, SelectedIndex, CurrentMenuTitle));
			CurrentMenuTitle = CurrentMenu[SelectedIndex]->GetText();
			CurrentMenu = PendingLeftMenu;
		}
	}
	SelectedIndex = PreviousIndex;
	//Setup the buttons
	for(int32 i = 0; i < CurrentMenu.Num(); ++i)
	{
		if (CurrentMenu[i]->bVisible)
		{
			TSharedPtr<SWidget> TmpWidget;
			if (CurrentMenu[i]->MenuItemType == EShooterMenuItemType::Standard)
			{
				TmpWidget = SAssignNew(CurrentMenu[i]->Widget, SShooterMenuItem)
					.PlayerOwner(PlayerOwner)
					.OnClicked(this, &SShooterUserProfileWidget::ButtonClicked, i)
					.Text(CurrentMenu[i]->GetText())
					.bIsMultichoice(false);
			} 
			else if (CurrentMenu[i]->MenuItemType == EShooterMenuItemType::MultiChoice)
			{
				TmpWidget = SAssignNew(CurrentMenu[i]->Widget, SShooterMenuItem)
					.PlayerOwner(PlayerOwner)
					.OnClicked(this, &SShooterUserProfileWidget::ButtonClicked, i)
					.Text(CurrentMenu[i]->GetText() )
					.bIsMultichoice(true)
					.OnArrowPressed(this, &SShooterUserProfileWidget::ChangeOption)
					.OptionText(this, &SShooterUserProfileWidget::GetOptionText, CurrentMenu[i]);
				UpdateArrows(CurrentMenu[i]);
			}
			else if (CurrentMenu[i]->MenuItemType == EShooterMenuItemType::CustomWidget)
			{
				TmpWidget = CurrentMenu[i]->CustomWidget;
			}
			if (TmpWidget.IsValid())
			{
				//set first selection to first valid widget
				if (SelectedIndex == -1)
				{
					SelectedIndex = i;
				}
				//LeftBox->AddSlot()	.HAlign(HAlign_Left)	.AutoHeight()
				//[
				//	TmpWidget.ToSharedRef()
				//];
			}
		}
	}
	
	
	TSharedPtr<FShooterMenuItem> FirstMenuItem = CurrentMenu.IsValidIndex(SelectedIndex) ? CurrentMenu[SelectedIndex] : NULL;
	if (FirstMenuItem.IsValid() && FirstMenuItem->MenuItemType != EShooterMenuItemType::CustomWidget)
	{
		FirstMenuItem->Widget->SetMenuItemActive(true);
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FText SShooterUserProfileWidget::GetOptionText(TSharedPtr<FShooterMenuItem> MenuItem) const
{
	FText Result = FText::GetEmpty();
	if (MenuItem->SelectedMultiChoice > -1 && MenuItem->SelectedMultiChoice < MenuItem->MultiChoice.Num())
	{
		Result = MenuItem->MultiChoice[MenuItem->SelectedMultiChoice];
	}
	return Result;
}

void SShooterUserProfileWidget::BuildRightPanel()
{
	//RightBox->ClearChildren();
	
	if (NextMenu.Num() == 0) return;

	for(int32 i = 0; i < NextMenu.Num(); ++i)
	{
		if (NextMenu[i]->bVisible)
		{
			TSharedPtr<SShooterMenuItem> TmpButton;
			//Custom menu items are not supported in the right panel
			if (NextMenu[i]->MenuItemType == EShooterMenuItemType::Standard)
			{
				TmpButton = SAssignNew(NextMenu[i]->Widget, SShooterMenuItem)
					.PlayerOwner(PlayerOwner)
					.Text(NextMenu[i]->GetText())
					.InactiveTextAlpha(0.3f)
					.bIsMultichoice(false);
			}
			else if (NextMenu[i]->MenuItemType == EShooterMenuItemType::MultiChoice)
			{
				TmpButton = SAssignNew(NextMenu[i]->Widget, SShooterMenuItem)
					.PlayerOwner(PlayerOwner)
					.Text(NextMenu[i]->GetText() )
					.InactiveTextAlpha(0.3f)
					.bIsMultichoice(true)
					.OptionText(this, &SShooterUserProfileWidget::GetOptionText, NextMenu[i]);
			}
			if(TmpButton.IsValid())
			{

			}
		}
	}
}

void SShooterUserProfileWidget::UpdateArrows(TSharedPtr<FShooterMenuItem> MenuItem)
{
	const int32 MinIndex = MenuItem->MinMultiChoiceIndex > -1 ? MenuItem->MinMultiChoiceIndex : 0;
	const int32 MaxIndex = MenuItem->MaxMultiChoiceIndex > -1 ? MenuItem->MaxMultiChoiceIndex : MenuItem->MultiChoice.Num()-1;
	const int32 CurIndex = MenuItem->SelectedMultiChoice;
	if (CurIndex > MinIndex)
	{
		MenuItem->Widget->LeftArrowVisible = EVisibility::Visible;
	} 
	else
	{
		MenuItem->Widget->LeftArrowVisible = EVisibility::Collapsed;
	}
	if (CurIndex < MaxIndex)
	{
		MenuItem->Widget->RightArrowVisible = EVisibility::Visible;
	}
	else
	{
		MenuItem->Widget->RightArrowVisible = EVisibility::Collapsed;
	}
}

void SShooterUserProfileWidget::EnterSubMenu()
{
	bLeftMenuChanging = true;
	bGoingBack = false;
	FSlateApplication::Get().PlaySound(MenuStyle->MenuEnterSound, GetOwnerUserIndex());
}

void SShooterUserProfileWidget::MenuGoBack(bool bSilent)
{
	if (MenuHistory.Num() > 0)
	{
		if (!bSilent)
		{
			FSlateApplication::Get().PlaySound(MenuStyle->MenuBackSound, GetOwnerUserIndex());
		}
		bLeftMenuChanging = true;
		bGoingBack = true;
		OnGoBack.ExecuteIfBound(CurrentMenu);
	}
	else if (bGameMenu) // only when it's in-game menu variant
	{
		if (!bSilent)
		{
			FSlateApplication::Get().PlaySound(MenuStyle->MenuBackSound, GetOwnerUserIndex());
		}
		OnToggleMenu.ExecuteIfBound();
	}
	else
	{
#if SHOOTER_CONSOLE_UI
		// Go back to the welcome screen.
		HideMenu();
#endif
	}
}

void SShooterUserProfileWidget::ConfirmMenuItem()
{
	if (CurrentMenu[SelectedIndex]->OnConfirmMenuItem.IsBound())
	{
		CurrentMenu[SelectedIndex]->OnConfirmMenuItem.Execute();
	} 
	else if (CurrentMenu[SelectedIndex]->SubMenu.Num() > 0)
	{
		EnterSubMenu();
	}
}

void SShooterUserProfileWidget::ControllerFacebuttonLeftPressed()
{
	if (CurrentMenu[SelectedIndex]->OnControllerFacebuttonLeftPressed.IsBound())
	{
		CurrentMenu[SelectedIndex]->OnControllerFacebuttonLeftPressed.Execute();
	} 
}

void SShooterUserProfileWidget::ControllerUpInputPressed()
{
	if (CurrentMenu[SelectedIndex]->OnControllerUpInputPressed.IsBound())
	{
		CurrentMenu[SelectedIndex]->OnControllerUpInputPressed.Execute();
	}
}

void SShooterUserProfileWidget::ControllerDownInputPressed()
{
	if (CurrentMenu[SelectedIndex]->OnControllerDownInputPressed.IsBound())
	{
		CurrentMenu[SelectedIndex]->OnControllerDownInputPressed.Execute();
	}
}

void SShooterUserProfileWidget::ControllerFacebuttonDownPressed()
{
	if (CurrentMenu[SelectedIndex]->OnControllerFacebuttonDownPressed.IsBound())
	{
		CurrentMenu[SelectedIndex]->OnControllerFacebuttonDownPressed.Execute();
	}
}

void SShooterUserProfileWidget::Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime )
{
	//Always tick the super
	SCompoundWidget::Tick( AllottedGeometry, InCurrentTime, InDeltaTime );

	//ugly code seeing if the console is open
	UConsole* ViewportConsole = (GEngine !=NULL && GEngine->GameViewport != NULL) ? GEngine->GameViewport->ViewportConsole : NULL;
	if (ViewportConsole != NULL && (ViewportConsole->ConsoleState == "Typing" || ViewportConsole->ConsoleState == "Open"))
	{
		if (!bConsoleVisible)
		{
			bConsoleVisible = true;
			FSlateApplication::Get().SetAllUserFocusToGameViewport();
		}
	}
	else
	{
		if (bConsoleVisible)
		{
			bConsoleVisible = false;
			FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
		}
	}

	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportFrame)
	{
		FViewport* Viewport = GEngine->GameViewport->ViewportFrame->GetViewport();
		if (Viewport)
		{
			const FVector2D Size = Viewport->GetSizeXY();
			ScreenRes = (Size / AllottedGeometry.Scale).IntPoint();
		}
	}

	if (MenuWidgetAnimation.IsAtStart() && !bMenuHiding)
	{
		//Start the menu widget animation, set keyboard focus
		FadeIn();
	}
	else if (MenuWidgetAnimation.IsAtStart() && bMenuHiding)
	{
		bMenuHiding = false;
		//Send event, so menu can be removed
		OnMenuHidden.ExecuteIfBound();
	}

	if (MenuWidgetAnimation.IsAtEnd())
	{
		if (bLeftMenuChanging)
		{
			if (LeftMenuWidgetAnimation.IsAtEnd())
			{
				PendingLeftMenu = NextMenu;
				if (NextMenu.Num() > 0
					&& NextMenu.Top()->SubMenu.Num() > 0)
				{
					NextMenu = NextMenu.Top()->SubMenu;
				} 
				else 
				{
					NextMenu.Reset();
				}
				bSubMenuChanging = true;

				LeftMenuWidgetAnimation.PlayReverse(this->AsShared());
			}
			if (!LeftMenuWidgetAnimation.IsPlaying())
			{
				if (CurrentMenu.Num() > 0)
				{
					BuildLeftPanel(bGoingBack);
					LeftMenuWidgetAnimation.Play(this->AsShared());
				}
				//Focus the custom widget
				if (CurrentMenu.Num() == 1 && CurrentMenu.Top()->MenuItemType == EShooterMenuItemType::CustomWidget)
				{
					FSlateApplication::Get().SetKeyboardFocus(CurrentMenu.Top()->CustomWidget);
				}
				bLeftMenuChanging = false;
				//RightBox->ClearChildren();
			}
		}
		if (bSubMenuChanging)
		{
			if (SubMenuWidgetAnimation.IsAtEnd())
			{
				SubMenuWidgetAnimation.PlayReverse(this->AsShared());
			}
			if (!SubMenuWidgetAnimation.IsPlaying())
			{
				if (NextMenu.Num() > 0)
				{
					BuildRightPanel();
					SubMenuWidgetAnimation.Play(this->AsShared());
				}
				bSubMenuChanging = false;
			}
		}
	}
}

FMargin SShooterUserProfileWidget::GetMenuOffset() const
{

	const TSharedRef< FSlateFontMeasure > FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	const FSlateFontInfo PlayerNameFontInfo = FShooterStyle::Get().GetWidgetStyle<FTextBlockStyle>("ShooterGame.UsernameTextStyle").Font;
	const FSlateFontInfo ProfileSwapFontInfo = FShooterStyle::Get().GetWidgetStyle<FTextBlockStyle>("ShooterGame.UserIDTextStyle").Font;
	const float MenuProfileWidth = FMath::Max(FontMeasure->Measure(UserName, PlayerNameFontInfo, 1.0f).X, FontMeasure->Measure(UserID.ToString(), ProfileSwapFontInfo, 1.0f).X) + 32.0f;

	const float OffsetX = (ScreenRes.X - MenuProfileWidth - 200); // 84 avatar width	
	FMargin Result = FMargin(OffsetX, 53.0f, 0, 0);
	return Result;
}

FMargin SShooterUserProfileWidget::GetLeftMenuOffset() const
{
	const float LeftBoxSizeX = 100; // LeftBox->GetDesiredSize().X + OutlineWidth * 2;
	return FMargin(0, 0,-LeftBoxSizeX + LeftMenuScrollOutCurve.GetLerp() * LeftBoxSizeX,0);
}

FMargin SShooterUserProfileWidget::GetSubMenuOffset() const
{
	return FMargin(0, 0, 0, 0);
}


FVector2D SShooterUserProfileWidget::GetBottomScale() const
{
	return FVector2D(BottomScaleYCurve.GetLerp(), BottomScaleYCurve.GetLerp());
}

FLinearColor SShooterUserProfileWidget::GetBottomColor() const
{
	return FMath::Lerp(FLinearColor(1,1,1,0), FLinearColor(1,1,1,1), BottomColorCurve.GetLerp());
}

FLinearColor SShooterUserProfileWidget::GetTopColor() const
{
	return FMath::Lerp(FLinearColor(1,1,1,0), FLinearColor(1,1,1,1), TopColorCurve.GetLerp());
}

FSlateColor SShooterUserProfileWidget::GetHeaderColor() const
{
	return CurrentMenuTitle.IsEmpty() ? FLinearColor::Transparent : FLinearColor::White;
}

FReply SShooterUserProfileWidget::ButtonClicked(int32 ButtonIndex)
{
	if (bControlsLocked)
	{
		return FReply::Handled();
	}

	if (SelectedIndex != ButtonIndex)
	{
		TSharedPtr<SShooterMenuItem> MenuItem = CurrentMenu[SelectedIndex]->Widget;
		MenuItem->SetMenuItemActive(false);
		SelectedIndex = ButtonIndex;
		MenuItem = CurrentMenu[SelectedIndex]->Widget;
		MenuItem->SetMenuItemActive(true);
		NextMenu = CurrentMenu[SelectedIndex]->SubMenu;
		bSubMenuChanging = true;
		FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound, GetOwnerUserIndex());
	}
	else if (SelectedIndex == ButtonIndex)
	{
		ConfirmMenuItem();
	}

	return FReply::Handled().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly);
}

void SShooterUserProfileWidget::FadeIn()
{
	//Start the menu widget playing
	MenuWidgetAnimation.Play(this->AsShared());

	//Go into UI mode
	FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
}

FReply SShooterUserProfileWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//If we clicked anywhere, jump to the end
	if(MenuWidgetAnimation.IsPlaying())
	{
		MenuWidgetAnimation.JumpToEnd();
	}

	//Set the keyboard focus 
	return FReply::Handled()
		.SetUserFocus(SharedThis(this), EFocusCause::SetDirectly);
}

void SShooterUserProfileWidget::ChangeOption(int32 MoveBy)
{
	TSharedPtr<FShooterMenuItem> MenuItem = CurrentMenu[SelectedIndex];

	const int32 MinIndex = MenuItem->MinMultiChoiceIndex > -1 ? MenuItem->MinMultiChoiceIndex : 0;
	const int32 MaxIndex = MenuItem->MaxMultiChoiceIndex > -1 ? MenuItem->MaxMultiChoiceIndex : MenuItem->MultiChoice.Num()-1;
	const int32 CurIndex = MenuItem->SelectedMultiChoice;

	if (MenuItem->MenuItemType == EShooterMenuItemType::MultiChoice)
	{
		if ( CurIndex + MoveBy >= MinIndex && CurIndex + MoveBy <= MaxIndex)
		{
			MenuItem->SelectedMultiChoice += MoveBy;
			MenuItem->OnOptionChanged.ExecuteIfBound(MenuItem, MenuItem->SelectedMultiChoice);
			FSlateApplication::Get().PlaySound(MenuStyle->OptionChangeSound, GetOwnerUserIndex());
		}
		UpdateArrows(MenuItem);
	}
}

int32 SShooterUserProfileWidget::GetNextValidIndex(int32 MoveBy)
{
	int32 Result = SelectedIndex;
	if (MoveBy != 0 && SelectedIndex + MoveBy > -1 && SelectedIndex+MoveBy < CurrentMenu.Num())
	{
		Result = SelectedIndex + MoveBy;
		//look for non-hidden menu item
		while (!CurrentMenu[Result]->Widget.IsValid())
		{
			MoveBy > 0 ? Result++ : Result--;
			//when moved outside of array, just return current selection
			if (!CurrentMenu.IsValidIndex(Result))
			{
				Result = SelectedIndex;
				break;
			}
		}
	}
	return Result;
}

FReply SShooterUserProfileWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	return Result;
}

FReply SShooterUserProfileWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	//Focus the custom widget
	if (CurrentMenu.Num() == 1 && CurrentMenu.Top()->MenuItemType == EShooterMenuItemType::CustomWidget)
	{
		return FReply::Handled().SetUserFocus(CurrentMenu.Top()->CustomWidget.ToSharedRef(), EFocusCause::SetDirectly);
	}

	return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
}

#undef LOCTEXT_NAMESPACE
