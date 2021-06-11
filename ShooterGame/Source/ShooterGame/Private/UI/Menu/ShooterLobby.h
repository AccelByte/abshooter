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
#include "UMG/LobbyMenu/PartyMemberEntryInterface.h"
#include "UMG/LobbyMenu/PartyInvitationPopupInterface.h"
// AccelByte
#include "Models/AccelByteUserModels.h"
#include "Models/AccelByteLobbyModels.h"

#include "ShooterGameConfig.h"

#define READY_CONSENT_TIMEOUT 20

/** Handle Lobby stuffs. */
class ShooterLobby : public TSharedFromThis<ShooterLobby>, public ILobbyMenuInterface, public IFriendSearchResultEntryInterface, public IFriendEntryInterface, public IIncomingFriendRequstPopupInterface,
	public IPartyMemberEntryInterface, public IPartyInvitationPopupInterface
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	* @param _LobbyMenuUI Lobby menu ui container.
	*/
	ShooterLobby(TWeakObjectPtr<class UShooterGameInstance> _GameInstance, TWeakObjectPtr<class ULobbyMenuUI> _LobbyMenuUI);

	/** Start Match Delegate */
	DECLARE_DELEGATE(FOnStartMatch);

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
	void OnLobbyConnectSuccess();

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

	#pragma region PARTY_SERVICE
	void OnInfoPartyResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo);
	void OnCreatePartyResponse(const FAccelByteModelsCreatePartyResponse& PartyInfo);
	void OnPartyLeaveNotification(const FAccelByteModelsLeavePartyNotice& LeaveInfo);
	void OnInvitePartyResponse(const FAccelByteModelsPartyInviteResponse& Response);
	void OnInvitePartyKickMemberResponse(const FAccelByteModelsKickPartyMemberResponse& Response);
	void OnPartyJoinNotification(const FAccelByteModelsPartyJoinNotice& Notification);
	void OnPartyKickNotification(const FAccelByteModelsGotKickedFromPartyNotice& KickInfo);
	void OnLeavePartyResponse(const FAccelByteModelsLeavePartyResponse& Response);
	void OnPartyGetInvitedNotification(const FAccelByteModelsPartyGetInvitedNotice& Notification);
	void OnInvitePartyJoinResponse(const FAccelByteModelsPartyJoinReponse& Response);
	#pragma endregion PARTY_SERVICE

#pragma region MATCHMAKING_SERVICE
	void OnMatchmakingNotification(const FAccelByteModelsMatchmakingNotice& Response);
	void OnRematchmakingNotification(const FAccelByteModelsRematchmakingNotice& Response);
	void OnStartMatchmakingResponse(const FAccelByteModelsMatchmakingResponse& Response);
	void OnCancelMatchmakingResponse(const FAccelByteModelsMatchmakingResponse& Response);
	void OnDsNotification(const FAccelByteModelsDsNotice& Notice);
#pragma endregion

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

	void OnAvatarReceived(FCacheBrush Image, FPartyMemberEntry PartyMember);

	/**
	* @brief Update friend entry.
	*
	* @param UserId The id of the friend.
	* @param FriendType The type of the friend.
	* @param Presence The current presence of the friend. Default is Offline.
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

	/** Populate Game Mode. */
	void LoadGameModes();

	/**
	* @brief Add party member entry to party member list.
	*
	* @param UserId The id of the party member.
    * @param isLeader True if party member is leader or false otherwise. Default is false.
	*/
	void AddPartyMember(FString UserId, bool isLeader = false);

	bool IsLeader() const;

	/** Update party member list. */
	void UpdatePartyMemberList();

	/** Update party member list based on matchmaking status. */
	void UpdatePartyMatchmakingStatus(const bool bMatchmakingStarted);

	void UpdateLobbyMenuMatchmakingState();

	#pragma region Override Lobby Menu Interface
	/**
	* @brief Add friend based on the its username.
	*
	* @param Username Friend's username who will be added.
	*/
	void AddFriend(FString Username) override;

	/** Refresh friend list. */
	void RefreshFriendList() override;

	/** Create a party. */
	void CreateParty() override;

	/**
	* @brief Change Game Mode.
	*
	* @param GameModeName The Game Mode name for the matchmaking.
	*/
	void ChangeGameMode(FString GameModeName) override;
	#pragma endregion Override Lobby Menu Interface

	#pragma region Override Matchmaking Interface

	/**
	* @brief Start the Matchmaking.
	*
	* @param GameModeDisplayName The Game Mode DisplayName for the matchmaking (Name that appears on the UI).
	*/
	void StartMatchmaking(FString GameModeDisplayName) override;

	/**
	* @brief Cancel Matchmaking.
	*
	*/
	void CancelMatchmaking() override;

	/**
	* @brief Readies Matchmaking.
	*
	*/
	void ReadyMatchmaking() override;

	/* MatchId returned by MatchmakingNotification. */
	FString CurrentMatchId;
	
	/* Countdown for Matchmaking until timeout, currently hardcoded based on Server. */
	int32 MatchmakingCountdown = READY_CONSENT_TIMEOUT;

	/* Countdown seconds for matchmaking ban lift */
	int32 MatchmakingBanPeriod = 0;

	/**
	* @brief Start the Match, called in DSNotif to signify the game is ready to begin.
	*
	* @param MatchId Current MatchId, received from DsNotif.
	* @param PartyId Current PartyId.
	* @param DedicatedServerAddress IP Address of the server, received from DsNotif when the DS is ready.
	*/
	void StartMatch(const FString& MatchId, const FString& PartyId, const FString& DedicatedServerAddress);

	/** Matchmaking Helper Function & Variable */

	/* TODO: Temporary solution, currently setup on StartMatchmaking,
	Solution :
	- should be setup when GameMode is changed from lobbyMenuUI
	- take from ComboBox LobbyMenuUI Variable
	- in case we're using the Select Match -> Lobby flow, this should be setup when entering the lobby
	*/
	/** Currently Selected Game Mode. */
	FGameModeEntry CurrentGameMode;

	/** Whether Matchmaking is started already or not */
	bool bMatchmakingStarted = false;

	/** Whether Game is Connected to Lobby Server or not */
	bool bIsLobbyConnected = true;

	/** Whether Game is entering Level or not, this means the Game managed to Join a Server already*/
	bool bAlreadyEnteringLevel = false;

	/** Whether Client is ready to start the match or not. */
	bool bReadyConsent = false;

	#pragma endregion

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
	* @brief Send a party invitation request.
	*
	* @param UserId Friend's user id who will be invited to the party.
	*/
	void SendPartyInvitationRequest(FString UserId) override;

	/**
	* @brief Send an unfriend request.
	*
	* @param UserId Friend's user id who will be unfriend.
	*/
	void SendUnfriendRequest(FString UserId) override;

	/**
	* @brief Send accept incoming friend request.
	*
	* @param UserId Friend's user id who send the friend request.
	*/
	void SendAcceptFriendRequest(FString UserId) override;

	/**
	* @brief Send reject incoming friend request.
	*
	* @param UserId Friend's user id who send the friend request.
	*/
	void SendRejectFriendRequest(FString UserId) override;

	/**
	* @brief Send cancel outgoing friend request.
	*
	* @param UserId Friend's user id who will be cancelled.
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
	#pragma endregion Override Incoming Friend Request Popup Interface

	#pragma region Override Party Member Entry Interface
	/** Leave a party.	*/
	virtual void LeaveParty() override;

	/**
	* @brief Kick a party member.
	*
	* @param UserId The id of party member who is kicked.
	*/
	void KickPartyMember(FString UserId) override;
	#pragma endregion Override Party Member Entry Interface

	#pragma region Override Party Invitation Popup Interface
	/**
	* @brief Accept party invitation.
	*
	* @param InvitationInformation The information of the party invitation.
	*/
	void AcceptPartyInvitation(FAccelByteModelsPartyGetInvitedNotice InvitationInformation) override;
	#pragma endregion Override Party Invitation Popup Interface

	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;

	/** Lobby sub-menu UI. */
	TWeakObjectPtr<class ULobbyMenuUI> LobbyMenuUI;

	/** Friend search result popup. */
	TWeakObjectPtr<class UFriendSearchResultPopupUI> FriendSearchResultPopup;

	/** Friend search result list. */
	TArray<class UFriendSearchResultEntryUI*> FriendSearchResultList;

	/** Friend list. */
	TArray<class UFriendEntryUI*> FriendList;

	/** Array of online friends when lobby is connected at first time. */
	TArray<FString> OnlineFriends;

	/** Game Mode options. */
	TArray<FGameModeEntry> GameModes;

	/** Game Mode Names. */
	TArray<FString> GameModeNames;

	/** Array of party members. */
	TArray<class UPartyMemberEntryUI*> PartyMembers;

	/** Current user party id. */
	FString CurrentPartyId;

	/** Current Game Mode for the matchmaking. */
	FGameModeEntry CurrenGameMode;

	/** Holds value if this player is leader or not */
	bool bIsLeader;
};
