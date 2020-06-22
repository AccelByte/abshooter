// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "PartyMemberEntryUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Utils/CacheUtils.h"

bool UPartyMemberEntryUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(LeaveButton != nullptr)) return false;
	LeaveButton->OnClicked.AddDynamic(this, &UPartyMemberEntryUI::LeaveParty);

	if (!ensure(KickButton != nullptr)) return false;
	KickButton->OnClicked.AddDynamic(this, &UPartyMemberEntryUI::KickPartyMember);

	if (!ensure(PartyLeaderIcon != nullptr)) return false;
	if (!ensure(AvatarImage != nullptr)) return false;
	if (!ensure(DisplayNameField != nullptr)) return false;
	if (!ensure(WaitingResponseText != nullptr)) return false;
	if (!ensure(PartyButtonSwitcher != nullptr)) return false;
	if (!ensure(EntryDataBox != nullptr)) return false;

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

void UPartyMemberEntryUI::SetInterface(IPartyMemberEntryInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UPartyMemberEntryUI] Interface is null"));
		return;
	}
	EntryInterface = Interface;
}

void UPartyMemberEntryUI::SetListItemObjectInternal(UObject* InObject)
{
	UPartyMemberEntryUI* Entry = Cast<UPartyMemberEntryUI>(InObject);

	Data = Entry->Data;

	if (Entry->Data.UserId.IsEmpty()) EntryDataBox->SetVisibility(ESlateVisibility::Collapsed);
	else
	{
		EntryDataBox->SetVisibility(ESlateVisibility::Visible);

		FString ResourceName = FShooterCacheUtils::CacheDir / Entry->Data.UserId + TEXT(".png");
		if (Entry->Data.Avatar.GetResourceName().ToString() == ResourceName)
		{
			AvatarImage->SetBrush(Entry->Data.Avatar);
		}
		else
		{
			AvatarImage->SetBrush(DefaultAvatar);
		}

		DisplayNameField->SetText(FText::FromString(Entry->Data.DisplayName));

		if (Entry->Data.isLeader)
		{
			PartyLeaderIcon->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			PartyLeaderIcon->SetVisibility(ESlateVisibility::Hidden);
		}

		WaitingResponseText->SetVisibility(ESlateVisibility::Collapsed);
		if (!Entry->Data.isMySelf && Entry->Data.onInvitation) WaitingResponseText->SetVisibility(ESlateVisibility::Visible);

		if (Entry->Data.isMySelf) PartyButtonSwitcher->SetActiveWidget(LeaveButton);
		else PartyButtonSwitcher->SetActiveWidget(KickButton);

		if (!Entry->Data.isMySelf && !Entry->Data.isKickable) PartyButtonSwitcher->SetVisibility(ESlateVisibility::Collapsed);
		else PartyButtonSwitcher->SetVisibility(ESlateVisibility::Visible);
	}

	EntryInterface = Entry->EntryInterface;

	PartyInvitationCounter = Entry->PartyInvitationCounter;
}

void UPartyMemberEntryUI::Tick(float DeltaTime)
{
	PartyInvitationCounter -= DeltaTime;
	if (PartyInvitationCounter <= 0)
	{
		PartyInvitationCounter = 0;
		KickPartyMember();
	}
	WaitingResponseText->SetText(FText::FromString(FString::Printf(TEXT("Waiting For Response (%.0f)"), PartyInvitationCounter)));
}

bool UPartyMemberEntryUI::IsTickable() const
{
	return Data.onInvitation;
}

bool UPartyMemberEntryUI::IsTickableInEditor() const
{
	return false;
}

bool UPartyMemberEntryUI::IsTickableWhenPaused() const
{
	return false;
}

TStatId UPartyMemberEntryUI::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UPartyMemberEntryUI, STATGROUP_Tickables);
}

#pragma region Button Callback
void UPartyMemberEntryUI::LeaveParty()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UPartyMemberEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->LeaveParty();
}

void UPartyMemberEntryUI::KickPartyMember()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UPartyMemberEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->KickPartyMember(Data.UserId);
}
#pragma endregion Button Callback
