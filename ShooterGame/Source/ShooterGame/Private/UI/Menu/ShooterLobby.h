// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Utils/ImageUtils.h"
#include "ShooterLobbyModels.h"
#include "UMG/LobbyMenu/LobbyMenuInterface.h"
#include "UMG/LobbyMenu/FriendSearchResultEntryInterface.h"
#include "UMG/LobbyMenu/FriendEntryInterface.h"
#include "UMG/LobbyMenu/IncomingFriendRequestPopupInterface.h"
// AccelByte
#include "Models/AccelByteUserModels.h"
#include "Models/AccelByteLobbyModels.h"

/** Handle Lobby stuffs. */
class ShooterLobby : public TSharedFromThis<ShooterLobby>, public ILobbyMenuInterface, public IFriendSearchResultEntryInterface, public IFriendEntryInterface, public IIncomingFriendRequstPopupInterface
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	* @param _LobbyMenuUI Lobby menu ui container.
	*/
	ShooterLobby(TWeakObjectPtr<class UShooterGameInstance> _GameInstance, TWeakObjectPtr<class ULobbyMenuUI> _LobbyMenuUI);

	/** Initialize menu. */
	void Initialize();

	/** Connect lobby to the server. */
	void Connect();

private:
	/** Reload friend list. */
	void ReloadFriendList();

	/** Set AccelByte's lobby delegate. */
	void SetLobbyDelegate();

	// AccelByte's Lobby Delegate
	#pragma region FRIENDS_SERVICE
	void OnGetAllUserPresenceResponse(const FAccelByteModelsGetOnlineUsersResponse& Response);
	void OnLoadFriendListResponse(const FAccelByteModelsLoadFriendListResponse& Response);
	void OnListIncomingFriendsResponse(const FAccelByteModelsListIncomingFriendsResponse& Response);
	void OnListOutgoingFriendsResponse(const FAccelByteModelsListOutgoingFriendsResponse& Response);
	void OnFriendRequestAcceptedNotification(const FAccelByteModelsAcceptFriendsNotif& Response);
	void OnIncomingRequestFriendsNotification(const FAccelByteModelsRequestFriendsNotif& Response);
	void OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response);
	void OnRequestFriendsResponse(const FAccelByteModelsRequestFriendsResponse& Response);
	#pragma endregion FRIENDS_SERVICE

	/**
	* @brief Add friend search result entry.
	*
	* @param UserInfo The information of the user entry.
	*/
	void AddFriendSearchResultEntry(FPublicUserInfo UserInfo);

	/**
	* @brief Show friend search result popup.
	*
	* @param UsersInfo The information of the user entries.
	*/
	void ShowFriendSearchResultPopup(FPagedPublicUsersInfo UsersInfo);

	/**
	* @brief Get friend entry data.
	*
	* @param UserId The id of the friend.
	* @param FriendType The type of the friend.
	* @param Presence The current presence of the friend.
	*/
	void GetFriendEntryData(FString UserId, EFriendType FriendType, EFriendPresence Presence);

	/**
	* @brief Add friend entry to friend list.
	*
	* @param Friend The data of the friend.
	*/
	void AddFriendEntry(FFriendEntry Friend);

	/**
	* @brief Handle when friend's avatar is received.
	*
	* @param Image The avatar image of the friend.
	* @param Friend The data of the friend.
	*/
	void OnAvatarReceived(FCacheBrush Image, FFriendEntry Friend);

	/**
	* @brief Update friend entry.
	*
	* @param UserId The id of the friend.
	* @param FriendType The type of the friend.
	* @param Presence The current presence of the friend.
	*/
	void UpdateFriendEntry(FString UserId, EFriendType FriendType, EFriendPresence Presence = EFriendPresence::OFFLINE);

	/** Update friend list view. */
	void UpdateFriendList();

	/**
	* @brief Show incoming friend request popup.
	*
	* @param UserId The id of the incoming friend.
	* @param DisplayName The display name of the incoming friend.
	*/
	void ShowIncomingFriendRequestPopup(FString UserId, FString DisplayName);

	#pragma region Override Lobby Menu Interface
	/**
	* @brief Add friend based on the its username.
	*
	* @param Username Friend's username who will be added.
	*/
	void AddFriend(FString Username) override;

	/** Refresh friend list. */
	void RefreshFriendList() override;
	#pragma endregion Override Lobby Menu Interface

	#pragma region Override Friend Search Result Entry Interface
	/**
	* @brief Send a friend request.
	*
	* @param UserId Friend's userid who will be added.
	*/
	void SendFriendRequest(FString UserId) override;
	#pragma endregion Override Friend Search Result Entry Interface

	#pragma region Override Friend Entry Interface
	/**
	* @brief Send an unfriend request.
	*
	* @param UserId Friend's userid who will be unfriend.
	*/
	void SendUnfriendRequest(FString UserId) override;

	/**
	* @brief Send accept incoming friend request.
	*
	* @param UserId Friend's userid who send the friend request.
	*/
	void SendAcceptFriendRequest(FString UserId) override;

	/**
	* @brief Send reject incoming friend request.
	*
	* @param UserId Friend's userid who send the friend request.
	*/
	void SendRejectFriendRequest(FString UserId) override;

	/**
	* @brief Send cancel outgoing friend request.
	*
	* @param UserId Friend's userid who will be cancelled.
	*/
	void SendCancelFriendRequest(FString UserId) override;
	#pragma endregion Override Friend Entry Interface

	#pragma region Override Incoming Friend Request Popup Interface
	/**
	* @brief Ignore incoming friend request.
	*
	* @param UserId Friend's userid who send the friend request.
	*/
	void IgnoreIncomingFriendRequest(FString UserId) override;

	/**
	* @brief Reject incoming friend request.
	*
	* @param UserId Friend's userid who send the friend request.
	*/
	void RejectIncomingFriendRequest(FString UserId) override;

	/**
	* @brief Accept incoming friend request.
	*
	* @param UserId Friend's userid send the friend request.
	*/
	void AcceptIncomingFriendRequest(FString UserId) override;
	#pragma region Override Incoming Friend Request Popup Interface

	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;

	/** Lobby sub-menu UI. */
	TWeakObjectPtr<class ULobbyMenuUI> LobbyMenuUI;

	/** Friend search result popup. */
	TWeakObjectPtr<class UFriendSearchResultPopupUI> FriendSearchResultPopup;

	/** Incoming friend request popup. */
	TWeakObjectPtr<class UIncomingFriendRequestPopupUI> IncomingFriendRequestPopup;

	/** Adding friend response popup. */
	TWeakObjectPtr<class UAddingFriendResponsePopupUI> AddingFriendResponsePopup;

	/** Friend search result list. */
	TArray<class UFriendSearchResultEntryUI*> FriendSearchResultList;

	/** Friend list. */
	TArray<class UFriendEntryUI*> FriendList;

	/** Array of online friends when lobby is connected at first time. */
	TArray<FString> OnlineFriends;
};
