// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SLobby.h"
#include "SLobbyChat.h"
#include "Api/AccelByteLobbyApi.h"
#include "Api/AccelByteOauth2Api.h"
#include "Core/AccelByteRegistry.h"

void SLobbyChat::Construct(const FArguments& InArgs)
{
	LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");
	LobbyParent = InArgs._LobbyParent;
	CurrentPartyId = &(LobbyParent->CurrentPartyID);

	AccelByte::FRegistry::Lobby.SetPrivateMessageNotifDelegate(AccelByte::Api::Lobby::FPersonalChatNotif::CreateSP(this, &SLobbyChat::OnReceivePrivateChat));
	AccelByte::FRegistry::Lobby.SetPartyChatNotifDelegate(AccelByte::Api::Lobby::FPartyChatNotif::CreateSP(this, &SLobbyChat::OnReceivePartyChat));


ChildSlot
.VAlign(VAlign_Fill)
.HAlign(HAlign_Fill)
	[
	SNew(SBox)
	.HeightOverride(250.0f)
	.WidthOverride(600.0f)
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()	//CHAT_TABs Area
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()	//CHAT_TAB Button Scroll LEFT <
			.AutoWidth()
			.Padding(FMargin(0, 4))
			[
				SAssignNew(ButtonChatTabScrollLeft, SButton)
				.OnClicked(this, &SLobbyChat::OnScrollLeftClicked)
				.ButtonStyle(&LobbyStyle->ChatTabLeftButtonStyle)
			]

			+ SHorizontalBox::Slot()	//CHAT_TAB ScrollBar<Button>
			.FillWidth(1.0f)
			.HAlign(HAlign_Fill)
			[
				SAssignNew(ScrollBoxChatTabs, SScrollBox)
				.IsEnabled(true)
				.AllowOverscroll(EAllowOverscroll::No)
				.ConsumeMouseWheel(EConsumeMouseWheel::Always)
				.ScrollBarAlwaysVisible(false)
				.ScrollBarVisibility(EVisibility::Collapsed)
				.Orientation(EOrientation::Orient_Horizontal)
			]

			+ SHorizontalBox::Slot()	//CHAT_TAB Button Scroll RIGHT >
			.AutoWidth()
			.Padding(FMargin(0, 4))
			[
				SAssignNew(ButtonChatTabScrollRight, SButton)
				.OnClicked(this, &SLobbyChat::OnScrollRightClicked)
				.ButtonStyle(&LobbyStyle->ChatTabRightButtonStyle)
			]
		]

		+ SVerticalBox::Slot()	//CHAT CONV Area
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(1.0f)
		[
			SAssignNew(ChatPageSwitcher, SWidgetSwitcher)
		]
	]
];
}

FReply SLobbyChat::OnScrollLeftClicked()
{
	if (ActiveTabIndex > 0)
	{
		SelectTab(ActiveTabIndex - 1);
		ScrollBoxChatTabs->ScrollDescendantIntoView(LobbyChatTabButtons[ActiveTabIndex], true);
	}
	return FReply::Handled();
}

FReply SLobbyChat::OnScrollRightClicked()
{
	if (ActiveTabIndex < LobbyChatTabButtons.Num() - 1)
	{
		SelectTab(ActiveTabIndex + 1);
		ScrollBoxChatTabs->ScrollDescendantIntoView(LobbyChatTabButtons[ActiveTabIndex], true);
	}
	return FReply::Handled();
}

void SLobbyChat::SelectTab(int32 TabIndex)
{
	ActiveTabIndex = TabIndex;

	for (auto a : LobbyChatTabButtons)
	{
		if (a->TabIndex == TabIndex)
		{
			a->Selected();
		}
		else
		{
			a->NotSelected();
		}
	}

	ChatPageSwitcher->SetActiveWidgetIndex(TabIndex);

	if (TabIndex == 0)
	{
		ButtonChatTabScrollLeft->SetEnabled(false);
	}
	else
	{
		ButtonChatTabScrollLeft->SetEnabled(true);
	}
	if (TabIndex == LobbyChatTabButtons.Num() - 1)
	{
		ButtonChatTabScrollRight->SetEnabled(false);
	}
	else
	{
		ButtonChatTabScrollRight->SetEnabled(true);
	}
	if (LobbyChatTabButtons.Num() == 1)
	{
		ButtonChatTabScrollLeft->SetEnabled(false);
		ButtonChatTabScrollRight->SetEnabled(false);
	}
	UE_LOG(LogTemp, Log, TEXT("Selected Tab: %d"), TabIndex);
}

void SLobbyChat::Remove(FString UserId)
{
	// remove chat box UI
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->Id.Equals(UserId))
		{
			ChatPageSwitcher->RemoveSlot(LobbyChatPages[i].ToSharedRef());
			LobbyChatPages.RemoveAt(i);
			break;
		}
	}

	// remove chat button
	for (int32 i = 0; i < LobbyChatTabButtons.Num(); i++)
	{
		if (LobbyChatTabButtons[i]->UserId.Equals(UserId))
		{
			ScrollBoxChatTabs->RemoveSlot(LobbyChatTabButtons[i].ToSharedRef());
			LobbyChatTabButtons.RemoveAt(i);
			break;
		}
	}
}

void SLobbyChat::RemovePartyChatTab(FString PartyId)
{
	// remove chat box UI
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->Id.Equals(PartyId))
		{
			ChatPageSwitcher->RemoveSlot(LobbyChatPages[i].ToSharedRef());
			LobbyChatPages.RemoveAt(i);
			break;
		}
	}

	// remove chat button
	for (int32 i = 0; i < LobbyChatTabButtons.Num(); i++)
	{
		if (LobbyChatTabButtons[i]->PartyId.Equals(PartyId))
		{
			ScrollBoxChatTabs->RemoveSlot(LobbyChatTabButtons[i].ToSharedRef());
			LobbyChatTabButtons.RemoveAt(i);
			break;
		}
	}
}

void SLobbyChat::AddPrivate(FString UserId, FString DisplayName)
{
	Add(UserId, DisplayName, false);
}

void SLobbyChat::AddParty(FString PartyId)
{
	Add(PartyId, "PARTY", true);
}

void SLobbyChat::Add(FString Identifier, FString TabName, bool bIsPartyMode)
{
	// if this identifier already added
	for (int i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->Id == Identifier) { return; }
	}
	LobbyChatPages.Add
	(
		SNew(SLobbyChatPage)
		.ChatPageIndex(LobbyChatPages.Num())
		.Id(Identifier)
		.OnTextComitted(this, &SLobbyChat::SendPartyChat)
		.OnSendButtonPressed(this, &SLobbyChat::SendPartyChat)
		.OnTextComitted(this, (bIsPartyMode) ? &SLobbyChat::SendPartyChat: &SLobbyChat::SendPrivateChat)
	);
	LobbyChatTabButtons.Add
	(
		SNew(SLobbyChatTabButton)
		.TabIndex(LobbyChatTabButtons.Num())
		.OnClicked(this, &SLobbyChat::SelectTab)
		.UserId(bIsPartyMode?"":Identifier)
		.PartyId(bIsPartyMode?Identifier:"")
		.DisplayName(TabName)
	);
	ChatPageSwitcher->AddSlot().AttachWidget(LobbyChatPages[LobbyChatPages.Num() - 1].ToSharedRef());
	ScrollBoxChatTabs->AddSlot().AttachWidget(LobbyChatTabButtons[LobbyChatTabButtons.Num() - 1].ToSharedRef());
	SelectTab(LobbyChatTabButtons.Num() - 1);
}

void SLobbyChat::SendPrivateChat(FString UserId, FString Message)
{
	AccelByte::FRegistry::Lobby.SendPrivateMessage(UserId, Message);
	AppendMessage(UserId, "ME", Message, false);
}

void SLobbyChat::SendPartyChat(FString PartyId, FString Message)
{
	AccelByte::FRegistry::Lobby.SendPartyMessage(Message);
	AppendMessage(PartyId, "ME", Message, true);
}

void SLobbyChat::OnReceivePrivateChat(const FAccelByteModelsPersonalMessageNotice& Response)
{
	FString DisplayName = LobbyParent->CheckDisplayName(Response.From) ? LobbyParent->GetDisplayName(Response.From) : Response.From;
	AppendMessage(Response.From, DisplayName, Response.Payload, false);
}

void SLobbyChat::OnReceivePartyChat(const FAccelByteModelsPartyMessageNotice& Response)
{
	// append to chat box UI
	FString DisplayName = LobbyParent->CheckDisplayName(Response.From) ? LobbyParent->GetDisplayName(Response.From) : Response.From;
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->Id.Equals(*CurrentPartyId))
		{
			//Get user's name and append it with this function

			// partner display name
			LobbyChatPages[i]->AppendConversation(DisplayName, Response.Payload);
			return;
		}
	}
	int32 iLastNum = LobbyChatPages.Num();

	//no chat tab, create new chat
	AddParty(*CurrentPartyId);
	LobbyChatPages[iLastNum]->AppendConversation(DisplayName, Response.Payload);
}

void SLobbyChat::AppendMessage(FString Id, FString Sender, FString Message, bool bIsPartyMode)
{
	//if success append message to existing UI component, return
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->Id.Equals(Id))
		{
			LobbyChatPages[i]->AppendConversation(Sender, Message);
			return;
		}
	}
	//else if component UI not exist then add it first
	int32 iLastNum = LobbyChatPages.Num();
	bIsPartyMode ? AddParty(*CurrentPartyId) : AddPrivate(Id, Sender);
	LobbyChatPages[iLastNum]->AppendConversation(Sender, Message);
	return;
}