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

struct FFriendEntry
{
	FString UserId;
	FString Name;
	FString Presence; //ONLINE, INGAME, IDLE, OFFLINE
	FString AvatarSmallUrl;
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

	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	FReply OnRequestFriend();

	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo);
	void UpdateSearchStatus();
    void InitializeFriends();
    void SetCurrentUser(FString UserID, FString DisplayName, FString AvatarURL);
    void SetCurrentUserFromCache(FString UserID, FString DisplayName, FString AvatarPath);
    FString GetCurrentUserID();
    void AddFriend(FString UserID, FString DisplayName, FString Avatar);
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

    bool CheckDisplayName(FString UserID) 
    {
        return DiplayNameListCache->Contains(UserID);
    }
    FString GetDisplayName(FString UserID)
    {
        return (*DiplayNameListCache)[UserID];
    }

    bool CheckAvatar(FString UserID)
    {
        return ThumbnailBrushCache.Contains(UserID);
    }

    TSharedPtr<FSlateDynamicImageBrush> GetAvatar(FString UserID)
    {
        return ThumbnailBrushCache[UserID];
    }

    void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID);
    TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData);


protected:
	bool bSearchingForFriends;
	bool bIsPartyLeader{ false };
	double LastSearchTime;
	double MinTimeBetweenSearches;
    FString CurrentUserDisplayName;
    FString CurrentUserID;
    FString CurrentAvatarURL;
	TSharedPtr<SEditableTextBox> FriendSearchBar;
	TArray< TSharedPtr<FFriendEntry> > FriendList;
	TArray< TSharedPtr<FFriendEntry> > CompleteFriendList;
	TSharedPtr< SListView< TSharedPtr<FFriendEntry> > > LobbyWidget;
	TSharedPtr<FFriendEntry> SelectedItem;
	
	FString MapFilterName;
	
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;
	TSharedPtr<class SWidget> OwnerWidget;
	TSharedPtr<SScrollBar> FriendScrollBar;
	FText GetFriendHeaderText() const;

#pragma region FRIENDS_SERVICE
	void OnRequestFriendSent(const FAccelByteModelsRequestFriendsResponse& Response);
	void OnIncomingListFriendRequest(const FAccelByteModelsListIncomingFriendsResponse& Response);
	void OnFriendListLoaded(const FAccelByteModelsLoadFriendListResponse& Response);
	void OnFriendRequestAcceptedNotification(const FAccelByteModelsAcceptFriendsNotif& Response);
	void OnIncomingFriendRequestNotification(const FAccelByteModelsRequestFriendsNotif& Response);
#pragma endregion FRIENDS_SERVICE

#pragma region Matchmaking
	void StartMatch(const FString&, const FString& PartyId);
	bool bMatchmakingStarted{ false };
	FString GameMode { "test" };
	FOnStartMatch OnStartMatch;
	FString DedicatedServerBaseUrl;
	FString DedicatedServerAddress;
#pragma endregion Matchmaking

    void OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response);

public:
#pragma region PARTY
	TSharedPtr<SParty> PartyWidget;
	TSharedPtr<SOverlay> InvitationOverlay;
    FString CurrentPartyID;
    void OnInvitedToParty(const FAccelByteModelsPartyGetInvitedNotice& Notification);
    void OnInvitedFriendJoinParty(const FAccelByteModelsPartyJoinNotice& Notification);
    void OnGetPartyInfoResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo);
	void OnCreatePartyResponse(const FAccelByteModelsCreatePartyResponse& CreatePartyInfo);
    void OnKickedFromParty(const FAccelByteModelsGotKickedFromPartyNotice& KickInfo);
    void OnLeavingParty(const FAccelByteModelsLeavePartyNotice& LeaveInfo);
    FSlateColorBrush OverlayBackgroundBrush;
#pragma endregion PARTY

	TSharedPtr<SOverlay> NotificationOverlay;
	void OnIncomingNotification(const FAccelByteModelsNotificationMessage& MessageNotification);
	void OnGetOnlineUserResponse(const FAccelByteModelsGetOnlineUsersResponse& Response);
};
