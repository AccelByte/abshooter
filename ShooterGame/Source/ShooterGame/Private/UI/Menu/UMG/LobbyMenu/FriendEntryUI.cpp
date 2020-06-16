// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "FriendEntryUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Utils/CacheUtils.h"

bool UFriendEntryUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(ChatButton != nullptr)) return false;
	ChatButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendChatRequest);

	if (!ensure(InviteButton != nullptr)) return false;
	InviteButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendInviteRequest);

	if (!ensure(UnfriendButton != nullptr)) return false;
	UnfriendButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendUnfriendRequest);

	if (!ensure(AcceptButton != nullptr)) return false;
	AcceptButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendAcceptRequest);

	if (!ensure(RejectButton != nullptr)) return false;
	RejectButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendRejectRequest);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UFriendEntryUI::SendCancelRequest);

	if (!ensure(DisplayNameField != nullptr)) return false;
	if (!ensure(PresenceField != nullptr)) return false;
	if (!ensure(FriendButtonSwitcher != nullptr)) return false;
	if (!ensure(RequestBox != nullptr)) return false; 
	if (!ensure(OnlineBox != nullptr)) return false;
	if (!ensure(AvatarImage != nullptr)) return false;

	// Default avatar
	FString DefaultAvatarDir = FPaths::ProjectContentDir() / TEXT("Slate\\Images");
	FString ImagePath = DefaultAvatarDir / TEXT("avatar.png");
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			DefaultAvatar = *FShooterImageUtils::CreateBrush(TEXT("png"), FName(*ImagePath), ImageData).Get();
		}
	}

	return true;
}

void UFriendEntryUI::SetInterface(IFriendEntryInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] Interface is null"));
		return;
	}
	EntryInterface = Interface;
}

void UFriendEntryUI::SetListItemObjectInternal(UObject* InObject)
{
	UFriendEntryUI* Entry = Cast<UFriendEntryUI>(InObject);

	Data = Entry->Data;
	
	DisplayNameField->SetText(FText::FromString(Entry->Data.DisplayName));

	FString PresenceText = TEXT("OFFLINE");


	OnlineBox->SetVisibility(ESlateVisibility::Collapsed);
	PresenceField->SetVisibility(ESlateVisibility::Collapsed);
	switch (Entry->Data.Type)
	{
	case EFriendType::FRIEND:
		FriendButtonSwitcher->SetActiveWidget(UnfriendButton);
		PresenceField->SetVisibility(ESlateVisibility::Visible);
		switch (Entry->Data.Presence)
		{
		case EFriendPresence::ONLINE:
			PresenceText = TEXT("ONLINE");
			OnlineBox->SetVisibility(ESlateVisibility::Visible);
			break;
		case EFriendPresence::INGAME:
			PresenceText = TEXT("INGAME");
			break;
		case EFriendPresence::IDLE:
			PresenceText = TEXT("IDLE");
			break;
		case EFriendPresence::OFFLINE:
			PresenceText = TEXT("OFFLINE");
			break;
		default:
			break;
		}
		break;
	case EFriendType::INCOMING:
		FriendButtonSwitcher->SetActiveWidget(RequestBox);
		break;
	case EFriendType::OUTGOING:
		FriendButtonSwitcher->SetActiveWidget(CancelButton);
		break;
	default:
		break;
	}
	PresenceField->SetText(FText::FromString(PresenceText));

	FString ResourceName = FShooterCacheUtils::CacheDir / Entry->Data.UserId + TEXT(".png");
	if(Entry->Data.Avatar.GetResourceName().ToString() == ResourceName)
	{
		AvatarImage->SetBrush(Entry->Data.Avatar);
	}
	else
	{
		AvatarImage->SetBrush(DefaultAvatar);
	}

	EntryInterface = Entry->EntryInterface;
}

void UFriendEntryUI::NativeOnItemSelectionChanged(bool bIsSelected)
{
	if (bIsSelected)
	{

	}
	else
	{

	}
}

#pragma region Button Callback
void UFriendEntryUI::SendChatRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	// TODO: Create send chat request interface.
}

void UFriendEntryUI::SendInviteRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	// TODO: Create send party invitation request interface.
}

void UFriendEntryUI::SendUnfriendRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->SendUnfriendRequest(Data.UserId);
}

void UFriendEntryUI::SendAcceptRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->SendAcceptFriendRequest(Data.UserId);
}

void UFriendEntryUI::SendRejectRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->SendRejectFriendRequest(Data.UserId);
}

void UFriendEntryUI::SendCancelRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->SendCancelFriendRequest(Data.UserId);
}
#pragma endregion Button Callback
