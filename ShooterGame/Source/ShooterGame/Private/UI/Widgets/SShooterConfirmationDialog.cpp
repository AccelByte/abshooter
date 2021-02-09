// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SShooterConfirmationDialog.h"
#include "ShooterGame.h"
#include "ShooterStyle.h"
#include "ShooterMenuItemWidgetStyle.h"
#include "ShooterGameInstance.h"
#include "PopupStyle.h"

void SShooterConfirmationDialog::Construct( const FArguments& InArgs )
{	
	PlayerOwner = InArgs._PlayerOwner;
	DialogType = InArgs._DialogType;

	OnConfirm = InArgs._OnConfirmClicked;
	OnCancel = InArgs._OnCancelClicked;

	const FShooterMenuItemStyle* ItemStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuItemStyle>("DefaultShooterMenuItemStyle");
	const FButtonStyle* ButtonStyle = &FShooterStyle::Get().GetWidgetStyle<FButtonStyle>("DefaultShooterButtonStyle");
	const FPopupStyle* PopupStyle = &FShooterStyle::Get().GetWidgetStyle<FPopupStyle>("DefaultPopupStyle");
	FLinearColor MenuTitleTextColor =  FLinearColor(FColor(155,164,182));


	ChildSlot
	.VAlign(VAlign_Center)
	.HAlign(HAlign_Center)
	[					
		SNew(SBorder)
		.BorderImage(&PopupStyle->OuterBorder)
		.Padding(FMargin(24, 32))
		[
			SNew(SBorder)
			.BorderImage(&PopupStyle->InnerBox)
			.Padding(FMargin(30, 51))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SNew(SBox)
					.MinDesiredWidth(570)
					.MinDesiredHeight(100)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Padding(32)
					[
						SNew(STextBlock)
						.Text(InArgs._MessageText)
						.TextStyle(&PopupStyle->MessageStyle)
						.WrapTextAt(500.0f)
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.MaxHeight(280)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.ContentPadding(16)
						.OnClicked(InArgs._OnCancelClicked)
						.Text(InArgs._CancelText)
						.TextStyle(&PopupStyle->ButtonText)
						.ButtonStyle(&PopupStyle->CancelButtonStyle)
						.Visibility(InArgs._CancelText.IsEmpty() == false ? EVisibility::Visible : EVisibility::Collapsed)
						.IsFocusable(false)
					]
					+ SHorizontalBox::Slot()
					[

						SNew(SButton)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.ContentPadding(16)
						.OnClicked(this, &SShooterConfirmationDialog::OnConfirmHandler)
						.Text(InArgs._ConfirmText)
						.TextStyle(&PopupStyle->ButtonText)
						.ButtonStyle(&PopupStyle->ConfirmButtonStyle)
						.IsFocusable(false)
					]
				]
			]
		]
	];
}

bool SShooterConfirmationDialog::SupportsKeyboardFocus() const
{
	return true;
}

FReply SShooterConfirmationDialog::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
}

FReply SShooterConfirmationDialog::OnConfirmHandler()
{
	return ExecuteConfirm(FSlateApplication::Get().GetUserIndexForKeyboard());
}

FReply SShooterConfirmationDialog::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	const FKey Key = KeyEvent.GetKey();
	const int32 UserIndex = KeyEvent.GetUserIndex();

	// Filter input based on the type of this dialog
	switch (DialogType)
	{
		case EShooterDialogType::Generic:
		{
			// Ignore input from users that don't own this dialog
			if (PlayerOwner != nullptr && PlayerOwner->GetControllerId() != UserIndex)
			{
				return FReply::Unhandled();
			}
			break;
		}

		case EShooterDialogType::ControllerDisconnected:
		{
			// Only ignore input from controllers that are bound to local users
			if(PlayerOwner != nullptr && PlayerOwner->GetGameInstance() != nullptr)
			{
				if (PlayerOwner->GetGameInstance()->FindLocalPlayerFromControllerId(UserIndex))
				{
					return FReply::Unhandled();
				}
			}
			break;
		}
	}

	// For testing on PC
	if ((Key == EKeys::Enter || Key == EKeys::Virtual_Accept) && !KeyEvent.IsRepeat())
	{
		return ExecuteConfirm(UserIndex);
	}
	else if (Key == EKeys::Escape || Key == EKeys::Virtual_Back)
	{
		if(OnCancel.IsBound())
		{
			return OnCancel.Execute();
		}
	}

	return FReply::Unhandled();
}

FReply SShooterConfirmationDialog::ExecuteConfirm(const int32 UserIndex)
{
	if (OnConfirm.IsBound())
	{
		//these two cases should be combined when we move to using PlatformUserIDs rather than ControllerIDs.
#if PLATFORM_PS4
		bool bExecute = false;
		// For controller reconnection, bind the confirming controller to the owner of this dialog
		if (DialogType == EShooterDialogType::ControllerDisconnected && PlayerOwner != nullptr)
		{
			const auto OnlineSub = IOnlineSubsystem::Get();
			if (OnlineSub)
			{
				const auto IdentityInterface = OnlineSub->GetIdentityInterface();
				if (IdentityInterface.IsValid())
				{
					TSharedPtr<const FUniqueNetId> IncomingUserId = IdentityInterface->GetUniquePlayerId(UserIndex);
					FUniqueNetIdRepl DisconnectedId = PlayerOwner->GetCachedUniqueNetId();

					if (*IncomingUserId == *DisconnectedId)
					{
						PlayerOwner->SetControllerId(UserIndex);
						bExecute = true;
					}
				}
			}
		}
		else
		{
			bExecute = true;
		}

		if (bExecute)
		{
			return OnConfirm.Execute();
		}
#else
		// For controller reconnection, bind the confirming controller to the owner of this dialog
		if (DialogType == EShooterDialogType::ControllerDisconnected && PlayerOwner != nullptr)
		{
			PlayerOwner->SetControllerId(UserIndex);
		}

		return OnConfirm.Execute();
#endif
	}

	return FReply::Unhandled();
}