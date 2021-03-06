// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "SShooterMenuWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "Framework/Text/RichTextMarkupProcessing.h"
#include "Framework/Text/IRichTextMarkupParser.h"
#include "Framework/Text/IRichTextMarkupWriter.h"
#include "LobbyStyle.h"
#include "Models/AccelByteLobbyModels.h"
#include "Api/AccelByteUserApi.h"
#include "Api/AccelByteUserProfileApi.h"
#include "Api/AccelByteOauth2Api.h"
#include "Api/AccelByteLobbyApi.h"
#include "Core/AccelByteRegistry.h"

#include "SLobbyParty.h"
#include "SLobbyChat.h"
#include "SLobbyChatPage.h"
#include "SLobbyChatTabButton.h"

enum FriendEntryTypeDeprecated
{
	FRIEND,
	INCOMING,
	OUTGOING
};

struct FFriendEntryDeprecated
{
	FString UserId;
	FString Name;
	FString Presence; //ONLINE, INGAME, IDLE, OFFLINE
	FString AvatarSmallUrl;
	FriendEntryTypeDeprecated Type;
};

//class declare
class SLobby : public SCompoundWidget
{
public:
	DECLARE_DELEGATE(FOnStartMatch)

	SLobby();

	SLATE_BEGIN_ARGS(SLobby)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_EVENT(FOnStartMatch, OnStartMatch)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override
	{
		return true;
	}

	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FFriendEntryDeprecated> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FFriendEntryDeprecated> InItem, ESelectInfo::Type SelectInfo);
	void UpdateSearchStatus();
	void InitializeFriends();
	void SetCurrentUser(FString UserID, FString DisplayName, FString AvatarURL);
	void SetCurrentUserFromCache(FString UserID, FString DisplayName, FString AvatarPath);
	FString GetCurrentUserID();
	void AddFriend(FString UserID, FString DisplayName, FString Avatar, FriendEntryTypeDeprecated Type);
	void RemoveFriend(FString UserId);
	void RefreshFriendList();
	void UpdateFriendList();

	void MoveSelection(int32 MoveBy);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	TSharedPtr<SLobbyChat> LobbyChatWidget;

	typedef TMap<FString, FString> ProfileCache;

	TSharedPtr < ProfileCache, ESPMode::ThreadSafe > AvatarListCache;
	TSharedPtr < ProfileCache, ESPMode::ThreadSafe > DiplayNameListCache;
	TMap<FString, TSharedPtr<FSlateDynamicImageBrush> >  ThumbnailBrushCache;
	FIntPoint ScreenRes;
	float GetLobbyHeight(float DivideBy) const;
	float GetLobbyWidth(float DivideBy) const;

	bool CheckDisplayName(const FString& UserID) const
	{
		return DiplayNameListCache->Contains(UserID);
	}
	FString GetDisplayName(const FString& UserID) const
	{
		return (*DiplayNameListCache)[UserID];
	}

	bool CheckAvatar(const FString& UserID) const
	{
		return ThumbnailBrushCache.Contains(UserID);
	}

	TSharedPtr<FSlateDynamicImageBrush> GetAvatar(const FString& UserID) const
	{
		return ThumbnailBrushCache[UserID];
	}

	FSlateBrush* GetAvatarOrDefault(const FString& UserId) const;

	void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID);

protected:
	bool bSearchingForFriends;
	bool bIsPartyLeader{ false };
	double LastSearchTime;
	double MinTimeBetweenSearches;
	FString CurrentUserDisplayName;
	FString CurrentUserID;
	FString CurrentAvatarURL;
	TSharedPtr<SEditableTextBox> FriendSearchBar;
	TArray< TSharedPtr<FFriendEntryDeprecated> > FriendList;
	TArray< TSharedPtr<FFriendEntryDeprecated> > CompleteFriendList;
	TSharedPtr< SListView< TSharedPtr<FFriendEntryDeprecated> > > LobbyWidget;
	TSharedPtr<FFriendEntryDeprecated> SelectedItem;
	FAccelByteModelsInfoPartyResponse PartyInfo;

	FString MapFilterName;

	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;
	TSharedPtr<class SWidget> OwnerWidget;
	TSharedPtr<SScrollBar> FriendScrollBar;
	FText GetFriendHeaderText() const;

#pragma region FRIENDS_SERVICE

#pragma endregion FRIENDS_SERVICE

#pragma region MESSAGE_DIALOG
	TSharedPtr<SWidget> MessageDialogWidget;
	FSlateColorBrush ConfirmationBackgroundBrush;
	void ShowMessageDialog(FString Message, FOnClicked OnClicked);
	void CloseMessageDialog();
#pragma endregion

#pragma region Matchmaking
	void StartMatch(const FString&, const FString& PartyId, const FString& DedicatedServerAddress);
	bool bMatchmakingStarted{ false };
	FString GameMode{ "test" };
	FOnStartMatch OnStartMatch;
	FString DedicatedServerBaseUrl;
	FString DedicatedServerAddress;
	bool bReadyConsent;
	bool bAlreadyEnteringLevel = false;
#pragma endregion Matchmaking

public:
#pragma region PARTY
	TSharedPtr<SParty> PartyWidget;
	TSharedPtr<SOverlay> InvitationOverlay;
	FString CurrentPartyID;
	FSlateColorBrush OverlayBackgroundBrush;
#pragma endregion PARTY

	TSharedPtr<SOverlay> NotificationOverlay;
	void CloseOverlay(TSharedPtr<SOverlay> Overlay);
	void OnIncomingNotification(const FAccelByteModelsNotificationMessage& MessageNotification);
};
