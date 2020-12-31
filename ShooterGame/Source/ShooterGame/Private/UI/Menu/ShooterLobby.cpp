// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterLobby.h"
#include "ShooterGameInstance.h"
#include "Utils/CacheUtils.h"
#include "UMG/GeneralNotificationPopupUI.h"
#include "UMG/LobbyMenu/LobbyMenuUI.h"
#include "UMG/LobbyMenu/FriendSearchResultEntryUI.h"
#include "UMG/LobbyMenu/FriendSearchResultPopupUI.h"
#include "UMG/LobbyMenu/FriendEntryUI.h"
#include "UMG/LobbyMenu/IncomingFriendRequestPopupUI.h"
#include "UMG/LobbyMenu/PartyMemberEntryUI.h"
#include "UMG/LobbyMenu/PartyInvitationPopupUI.h"
// AccelByte
#include "Core/AccelByteRegistry.h"
#include "Api/AccelByteUserApi.h"
#include "Api/AccelByteLobbyApi.h"

#define GAME_NAME TEXT("Shooter Game")

FCriticalSection ShooterLobbyMutex;

ShooterLobby::ShooterLobby(TWeakObjectPtr<UShooterGameInstance> _GameInstance, TWeakObjectPtr<ULobbyMenuUI> _LobbyMenuUI)
	: GameInstance(_GameInstance)
	, LobbyMenuUI(_LobbyMenuUI)
{}

void ShooterLobby::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] Initialize!"));

	FriendList.Empty();

	AccelByte::FRegistry::Lobby.SendSetPresenceStatus(Availability::Availabe, GAME_NAME);
	AccelByte::FRegistry::Lobby.SendLeavePartyRequest();
	ReloadFriendList();

	PartyMembers.Empty();

	LobbyMenuUI->SetInterface(this);

	LoadGameModes();
}

void ShooterLobby::Connect()
{
	LobbyMenuUI->OpenConnectProcessPanel();
	SetLobbyDelegate();
	if (AccelByte::FRegistry::Lobby.IsConnected())
	{
		OnLobbyConnectSuccess();
	}
	else
	{
		AccelByte::FRegistry::Lobby.Connect();
	}
}

void ShooterLobby::ReloadFriendList()
{
	AccelByte::FRegistry::Lobby.SendGetOnlineUsersRequest(); // Get online friends list.
	AccelByte::FRegistry::Lobby.ListIncomingFriends();
	AccelByte::FRegistry::Lobby.ListOutgoingFriends();
}

void ShooterLobby::SetLobbyDelegate()
{

#pragma region Lobby Connection Delegate
	AccelByte::FRegistry::Lobby.SetConnectSuccessDelegate(FSimpleDelegate::CreateSP(this, &ShooterLobby::OnLobbyConnectSuccess));

	AccelByte::FErrorHandler OnLobbyConnectFailed = AccelByte::FErrorHandler::CreateLambda([this](int32 Code, FString Message) {
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Lobby Connect Failed! Code: %d, Message: %s."), Code, *Message);
		if (LobbyMenuUI != nullptr)
		{
			LobbyMenuUI->OpenConnectFailedPanel(TEXT("Lobby Failed to Connect!"));
		}
	});
	AccelByte::FRegistry::Lobby.SetConnectFailedDelegate(OnLobbyConnectFailed);

	AccelByte::FErrorHandler OnLobbyParsingError = AccelByte::FErrorHandler::CreateLambda([](int32 Code, FString Message) {
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Lobby Parsing Error! Code: %d, Message: %s."), Code, *Message);
	});
	AccelByte::FRegistry::Lobby.SetParsingErrorDelegate(OnLobbyParsingError);

	AccelByte::Api::Lobby::FConnectionClosed OnLobbyConnectionClosed = AccelByte::Api::Lobby::FConnectionClosed::CreateLambda([this](int32 StatusCode, const FString& Reason, bool WasClean) {
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Lobby Disconnected! Code: %d, Message: %s, WasClean: %d."), StatusCode, *Reason, WasClean);
		if (LobbyMenuUI != nullptr)
		{
			LobbyMenuUI->OpenConnectFailedPanel(TEXT("Lobby is Disconnected!"));
		}
	});
	AccelByte::FRegistry::Lobby.SetConnectionClosedDelegate(OnLobbyConnectionClosed);

#pragma region Lobby Friend List Delegate
	AccelByte::FRegistry::Lobby.SetGetAllUserPresenceResponseDelegate(AccelByte::Api::Lobby::FGetAllFriendsStatusResponse::CreateSP(this, &ShooterLobby::OnGetAllUserPresenceResponse));
	AccelByte::FRegistry::Lobby.SetLoadFriendListResponseDelegate(AccelByte::Api::Lobby::FLoadFriendListResponse::CreateSP(this, &ShooterLobby::OnLoadFriendListResponse));
	AccelByte::FRegistry::Lobby.SetListIncomingFriendsResponseDelegate(AccelByte::Api::Lobby::FListIncomingFriendsResponse::CreateSP(this, &ShooterLobby::OnListIncomingFriendsResponse));
	AccelByte::FRegistry::Lobby.SetListOutgoingFriendsResponseDelegate(AccelByte::Api::Lobby::FListOutgoingFriendsResponse::CreateSP(this, &ShooterLobby::OnListOutgoingFriendsResponse));
	AccelByte::FRegistry::Lobby.SetOnFriendRequestAcceptedNotifDelegate(AccelByte::Api::Lobby::FAcceptFriendsNotif::CreateSP(this, &ShooterLobby::OnFriendRequestAcceptedNotification));
	AccelByte::FRegistry::Lobby.SetOnIncomingRequestFriendsNotifDelegate(AccelByte::Api::Lobby::FRequestFriendsNotif::CreateSP(this, &ShooterLobby::OnIncomingRequestFriendsNotification));
	AccelByte::FRegistry::Lobby.SetUserPresenceNotifDelegate(AccelByte::Api::Lobby::FFriendStatusNotif::CreateSP(this, &ShooterLobby::OnUserPresenceNotification));
	AccelByte::FRegistry::Lobby.SetRequestFriendsResponseDelegate(AccelByte::Api::Lobby::FRequestFriendsResponse::CreateSP(this, &ShooterLobby::OnRequestFriendsResponse));
#pragma endregion
#pragma region Party Delegate
	AccelByte::FRegistry::Lobby.SetCreatePartyResponseDelegate(AccelByte::Api::Lobby::FPartyCreateResponse::CreateSP(this, &ShooterLobby::OnCreatePartyResponse));
	AccelByte::FRegistry::Lobby.SetInfoPartyResponseDelegate(AccelByte::Api::Lobby::FPartyInfoResponse::CreateSP(this, &ShooterLobby::OnInfoPartyResponse));
	AccelByte::FRegistry::Lobby.SetPartyLeaveNotifDelegate(AccelByte::Api::Lobby::FPartyLeaveNotif::CreateSP(this, &ShooterLobby::OnPartyLeaveNotification));
	AccelByte::FRegistry::Lobby.SetInvitePartyResponseDelegate(AccelByte::Api::Lobby::FPartyInviteResponse::CreateSP(this, &ShooterLobby::OnInvitePartyResponse));
	AccelByte::FRegistry::Lobby.SetInvitePartyKickMemberResponseDelegate(AccelByte::Api::Lobby::FPartyKickResponse::CreateSP(this, &ShooterLobby::OnInvitePartyKickMemberResponse));
	AccelByte::FRegistry::Lobby.SetPartyJoinNotifDelegate(AccelByte::Api::Lobby::FPartyJoinNotif::CreateSP(this, &ShooterLobby::OnPartyJoinNotification));
	AccelByte::FRegistry::Lobby.SetPartyKickNotifDelegate(AccelByte::Api::Lobby::FPartyKickNotif::CreateSP(this, &ShooterLobby::OnPartyKickNotification));
	AccelByte::FRegistry::Lobby.SetLeavePartyResponseDelegate(AccelByte::Api::Lobby::FPartyLeaveResponse::CreateSP(this, &ShooterLobby::OnLeavePartyResponse));
	AccelByte::FRegistry::Lobby.SetPartyGetInvitedNotifDelegate(AccelByte::Api::Lobby::FPartyGetInvitedNotif::CreateSP(this, &ShooterLobby::OnPartyGetInvitedNotification));
	AccelByte::FRegistry::Lobby.SetInvitePartyJoinResponseDelegate(AccelByte::Api::Lobby::FPartyJoinResponse::CreateSP(this, &ShooterLobby::OnInvitePartyJoinResponse));

#pragma endregion

#pragma region Matchmaking Delegate
	AccelByte::FRegistry::Lobby.SetMatchmakingNotifDelegate(AccelByte::Api::Lobby::FMatchmakingNotif::CreateSP(this, &ShooterLobby::OnMatchmakingNotification));
	AccelByte::FRegistry::Lobby.SetRematchmakingNotifDelegate(AccelByte::Api::Lobby::FRematchmakingNotif::CreateSP(this, &ShooterLobby::OnRematchmakingNotification));
	AccelByte::FRegistry::Lobby.SetStartMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateSP(this, &ShooterLobby::OnStartMatchmakingResponse));
	AccelByte::FRegistry::Lobby.SetCancelMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateSP(this, &ShooterLobby::OnCancelMatchmakingResponse));
	AccelByte::FRegistry::Lobby.SetDsNotifDelegate(AccelByte::Api::Lobby::FDsNotif::CreateSP(this, &ShooterLobby::OnDsNotification));
#pragma endregion

}

void ShooterLobby::OnLobbyConnectSuccess()
{
	UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] Lobby Login...Connected!"));
	if (LobbyMenuUI != nullptr)
	{
		LobbyMenuUI->OpenConnectSuccessPanel();
		Initialize();
	}
}

void ShooterLobby::OnGetAllUserPresenceResponse(const FAccelByteModelsGetOnlineUsersResponse& Response)
{
	OnlineFriends.Empty();
	for (int i = 0; i < Response.friendsId.Num(); i++)
	{
		if (Response.activity[i] == GAME_NAME)
		{
			if (Response.availability[i] == TEXT("1"))
			{
				OnlineFriends.Add(Response.friendsId[i]);
			}
		}
	}
	AccelByte::FRegistry::Lobby.LoadFriendsList(); // Force to load friend list to obtain UserID & displayname list
}

void ShooterLobby::OnLoadFriendListResponse(const FAccelByteModelsLoadFriendListResponse& Response)
{
	if (Response.Code != TEXT("0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnLoadFriendListResponse response code: %s"), *Response.Code);
		return;
	}

	for (int i = 0; i < Response.friendsId.Num(); i++)
	{
		EFriendPresence Presence = EFriendPresence::OFFLINE;
		bool isOnline = OnlineFriends.Contains(Response.friendsId[i]);
		if (isOnline)
		{
			Presence = EFriendPresence::ONLINE;
			OnlineFriends.Remove(Response.friendsId[i]);
		}
		UpdateFriendEntry(Response.friendsId[i], EFriendType::FRIEND, Presence);
	}
}

void ShooterLobby::OnListIncomingFriendsResponse(const FAccelByteModelsListIncomingFriendsResponse& Response)
{
	for (int i = 0; i < Response.friendsId.Num(); i++)
	{
		UpdateFriendEntry(Response.friendsId[i], EFriendType::INCOMING);
	}
}

void ShooterLobby::OnListOutgoingFriendsResponse(const FAccelByteModelsListOutgoingFriendsResponse& Response)
{
	for (int i = 0; i < Response.friendsId.Num(); i++)
	{
		UpdateFriendEntry(Response.friendsId[i], EFriendType::OUTGOING);
	}
}

void ShooterLobby::AddFriendSearchResultEntry(FPublicUserInfo UserInfo)
{
	if (!GameInstance.IsValid()) return;

	FScopeLock Lock(&ShooterLobbyMutex);

	TWeakObjectPtr<UFriendSearchResultEntryUI> Entry = MakeWeakObjectPtr<UFriendSearchResultEntryUI>(CreateWidget<UFriendSearchResultEntryUI>(GameInstance.Get(), *GameInstance->FriendSearchResultEntryClass.Get()));
	Entry->UserId = UserInfo.UserId;
	Entry->DisplayName = UserInfo.DisplayName;
	Entry->Email = UserInfo.EmailAddress;
	Entry->SetInterface(this);
	FriendSearchResultList.Add(Entry.Get());
}

void ShooterLobby::ShowFriendSearchResultPopup(FPagedPublicUsersInfo UsersInfo)
{
	FriendSearchResultList.Empty();
	for (int i = 0; i < UsersInfo.Data.Num(); i++)
	{
		AddFriendSearchResultEntry(UsersInfo.Data[i]);
	}
	FriendSearchResultPopup->UpdateSearchResultList(FriendSearchResultList);
}

void ShooterLobby::GetFriendEntryData(FString UserId, EFriendType FriendType, EFriendPresence Presence)
{
	FFriendEntry Friend;
	Friend.UserId = UserId;
	Friend.Type = FriendType;
	Friend.Presence = Presence;
	bool isCached = FShooterCacheUtils::IsUserCacheExist(UserId);
	if (isCached)
	{
		FUserCache UserCache = FShooterCacheUtils::GetUserCache(UserId);
		Friend.DisplayName = UserCache.DisplayName;
		FCacheBrush Avatar = FShooterCacheUtils::GetUserAvatarCache(UserId);
		if (Avatar.IsValid())
		{
			Friend.Avatar = *Avatar.Get();
		}
		AddFriendEntry(Friend);
		UpdateFriendList();
	}
	else
	{
		AccelByte::FRegistry::User.GetUserByUserId(
			Friend.UserId,
			THandler<FUserData>::CreateLambda([this, Friend](const FUserData& User) mutable
				{
					Friend.DisplayName = User.DisplayName;
					AccelByte::FRegistry::UserProfile.GetPublicUserProfileInfo(
						Friend.UserId,
						AccelByte::THandler<FAccelByteModelsPublicUserProfileInfo>::CreateLambda([this, Friend](const FAccelByteModelsPublicUserProfileInfo& UserProfileInfo)
							{
								UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] Get User Public Profile: %s - > %s Success."), *UserProfileInfo.UserId, *UserProfileInfo.AvatarSmallUrl);
							
								FString Filename = FShooterCacheUtils::CacheDir / Friend.UserId + TEXT(".png");
								FString AvatarUrl = UserProfileInfo.AvatarSmallUrl;
								FShooterImageUtils::GetImage(
									AvatarUrl,
									FOnImageReceived::CreateLambda([this, Friend](const FCacheBrush Image) {
										OnAvatarReceived(Image, Friend);
									}),
									Filename
								);
							}
						),
						AccelByte::FErrorHandler::CreateLambda([this, Friend](int32 Code, FString Message)
							{
								UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetPublicUserProfileInfo Failed UserId: %s! Code: %d, Message: %s."), *Friend.UserId, Code, *Message);

								AddFriendEntry(Friend);
								UpdateFriendList();
							}
						)
					);
				}
			),
			FErrorHandler::CreateLambda([UserId](int32 Code, FString Message)
				{
					UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetUserByUserId Failed UserId: %s! Code: %d, Message: %s."), *UserId, Code, *Message);
				}
			)
		);
	}
}

void ShooterLobby::AddFriendEntry(FFriendEntry Friend)
{
	if (!GameInstance.IsValid()) return;

	FScopeLock Lock(&ShooterLobbyMutex);

	TWeakObjectPtr<UFriendEntryUI> Entry = MakeWeakObjectPtr<UFriendEntryUI>(CreateWidget<UFriendEntryUI>(GameInstance.Get(), *GameInstance->FriendEntryClass.Get()));
	Entry->Data = Friend;
	Entry->SetInterface(this);

	// Avoid Adding existing entry
	int32 Index = FriendList.IndexOfByPredicate([Friend](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == Friend.UserId;
	});

	if (Index == INDEX_NONE)
	{
		FriendList.Add(Entry.Get());
	}
}

void ShooterLobby::OnAvatarReceived(FCacheBrush Image, FFriendEntry Friend)
{
	if (!GameInstance.IsValid()) return;

	if (Image.IsValid())
	{
		Friend.Avatar = *Image.Get();

		FUserCache UserCache;
		UserCache.UserId = Friend.UserId;
		UserCache.DisplayName = Friend.DisplayName;
		FShooterCacheUtils::SaveUserCache(UserCache);
	}

	FScopeLock Lock(&ShooterLobbyMutex);

	int32 Index = FriendList.IndexOfByPredicate([Friend](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == Friend.UserId;
	});
	if (Index != INDEX_NONE)
	{
		FriendList[Index]->Data = Friend;
		UpdateFriendList();
	}
	else
	{
		AddFriendEntry(Friend);
		UpdateFriendList();
	}
}

void ShooterLobby::OnAvatarReceived(FCacheBrush Image, FPartyMemberEntry PartyMember)
{
	if (!GameInstance.IsValid()) return;

	TWeakObjectPtr<UPartyMemberEntryUI> Entry = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
	Entry->Data.UserId = PartyMember.UserId;
	Entry->Data.DisplayName = PartyMember.DisplayName;

	if (Image.IsValid())
	{
		Entry->Data.Avatar = *Image.Get();

		FUserCache UserCache;
		UserCache.UserId = PartyMember.UserId;
		UserCache.DisplayName = PartyMember.DisplayName;
		FShooterCacheUtils::SaveUserCache(UserCache);
	}

	FScopeLock Lock(&ShooterLobbyMutex);

	Entry->SetInterface(this);
	PartyMembers.Add(Entry.Get());
	UpdatePartyMemberList();
}

void ShooterLobby::UpdateFriendEntry(FString UserId, EFriendType FriendType, EFriendPresence Presence)
{
	FScopeLock Lock(&ShooterLobbyMutex);

	int32 Index = FriendList.IndexOfByPredicate([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	if (Index != INDEX_NONE)
	{
		FriendList[Index]->Data.Presence = Presence;
		FriendList[Index]->Data.Type = FriendType;
		UpdateFriendList();
	}
	else
	{
		GetFriendEntryData(UserId, FriendType, Presence);
	}
}

void ShooterLobby::UpdateFriendList()
{
	for (auto FriendEntry : FriendList)
	{
		if(CurrentPartyId.IsEmpty())
		{ 
			FriendEntry->Data.onParty = true;
		}
		else
		{
			if (FriendEntry->Data.Presence == EFriendPresence::ONLINE)
			{
				// If Matchmaking is started, collapse the Invite Party Member functionality
				if (bMatchmakingStarted == true)
				{
					FriendEntry->Data.onParty = true;
				}
				else 
				{
					FriendEntry->Data.onParty = PartyMembers.ContainsByPredicate([FriendEntry](UPartyMemberEntryUI* Entry) {
						return Entry->Data.UserId == FriendEntry->Data.UserId;
					});
				}
			}
			else
			{
				FriendEntry->Data.onParty = false;
			}
		}
	}

	FriendList.StableSort([](const UFriendEntryUI& EntryA, const UFriendEntryUI& EntryB) {
		bool isSorted = false;
		if ((uint8)EntryA.Data.Type < (uint8)EntryB.Data.Type) isSorted = true;
		else if (((uint8)EntryA.Data.Type == (uint8)EntryB.Data.Type))
		{
			if ((uint8)EntryA.Data.Presence < (uint8)EntryB.Data.Presence) isSorted = true;
			else if ((uint8)EntryA.Data.Presence == (uint8)EntryB.Data.Presence)
			{
				if(EntryA.Data.onParty < EntryB.Data.onParty) isSorted = true;
			}
		}
		return isSorted;
	});
	LobbyMenuUI->UpdateFriendList(FriendList);
}

void ShooterLobby::ShowIncomingFriendRequestPopup(FString UserId, FString DisplayName)
{
	if (!GameInstance.IsValid()) return;

	TWeakObjectPtr<class UIncomingFriendRequestPopupUI> IncomingFriendRequestPopup = MakeWeakObjectPtr<UIncomingFriendRequestPopupUI>(CreateWidget<UIncomingFriendRequestPopupUI>(GameInstance.Get(), *GameInstance->IncomingFriendRequestPopupClass.Get()));
	IncomingFriendRequestPopup->Show(UserId, DisplayName);
	IncomingFriendRequestPopup->SetInterface(this);
}

void ShooterLobby::OnFriendRequestAcceptedNotification(const FAccelByteModelsAcceptFriendsNotif& Response)
{
	FScopeLock Lock(&ShooterLobbyMutex);

	FString FriendId = Response.friendId;
	int32 Index = FriendList.IndexOfByPredicate([FriendId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == FriendId;
	});
	if (Index != INDEX_NONE)
	{
		FriendList[Index]->Data.Presence = EFriendPresence::ONLINE;
		FriendList[Index]->Data.Type = EFriendType::FRIEND;
		UpdateFriendList();
	}
	else
	{
		GetFriendEntryData(FriendId, EFriendType::FRIEND, EFriendPresence::ONLINE);
	}

	//TODO: Create notification.
}

void ShooterLobby::OnIncomingRequestFriendsNotification(const FAccelByteModelsRequestFriendsNotif& Response)
{
	UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnIncomingRequestFriendsNotification..."));

	FString UserId = Response.friendId;
	bool isCached = FShooterCacheUtils::IsUserCacheExist(UserId);
	if (isCached)
	{
		FUserCache UserCache = FShooterCacheUtils::GetUserCache(UserId);
		ShowIncomingFriendRequestPopup(UserId, UserCache.DisplayName);
	}
	else
	{
		AccelByte::FRegistry::User.GetUserByUserId(
			UserId,
			THandler<FUserData>::CreateLambda([this, UserId](const FUserData& User)
				{
					ShowIncomingFriendRequestPopup(UserId, User.DisplayName);
				}
			),
			FErrorHandler::CreateLambda([this, UserId](int32 Code, FString Message)
				{
					UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetUserByUserId Failed UserId: %s! Code: %d, Message: %s."), *UserId, Code, *Message);

					ShowIncomingFriendRequestPopup(UserId, TEXT(""));
				}
			)
		);
	}
}

void ShooterLobby::OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response)
{
	FScopeLock Lock(&ShooterLobbyMutex);

	FString UserId = Response.UserID;
	int32 Index = FriendList.IndexOfByPredicate([UserId](UFriendEntryUI* Entry)
	{
		return Entry->Data.UserId == UserId;
	});
	if (Index != INDEX_NONE)
	{
		if (Response.Activity == GAME_NAME && Response.Availability == TEXT("1"))
		{
			FriendList[Index]->Data.Presence = EFriendPresence::ONLINE;
		}
		else
		{
			FriendList[Index]->Data.Presence = EFriendPresence::OFFLINE;

			if (PartyMembers.Num() > 0)
			{
				if (PartyMembers[0]->Data.UserId == UserId)
				{
					LeaveParty();
				}
				else if (PartyMembers[0]->Data.UserId == GameInstance->UserToken.User_id)
				{
					KickPartyMember(UserId);
				}
			}
		}
		UpdateFriendList();
	}

	// TODO: Create notification popup.
}

void ShooterLobby::OnRequestFriendsResponse(const FAccelByteModelsRequestFriendsResponse& Response)
{
	ReloadFriendList();
	if (Response.Code != TEXT("0"))
	{
		TWeakObjectPtr<UGeneralNotificationPopupUI> AddingFriendResponsePopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));
		AddingFriendResponsePopup->Show(ENotificationType::ERROR_UNKNOWN, TEXT("Failed to Add Friend!"));
	}
}

void ShooterLobby::LoadGameModes()
{
	GameModes.Empty();

	// TODO: Read from game config. Below is just a hardcoded-mock up.
	GameModes.Add({ "FFA", "10ffa", 1 });
	GameModes.Add({ "1 vs 1", "1vs1", 1 });
	GameModes.Add({ "2 vs 2", "2vs2", 2 });
	GameModes.Add({ "3 vs 3", "3vs3", 3 });
	GameModes.Add({ "4 vs 4", "4vs4", 4 });
	GameModes.Add({ "5 vs 5", "5vs5", 5 });

	if (GameModes.Num() > 0)
	{
		for (auto& GameMode : GameModes)
		{
			GameModeNames.Add(GameMode.DisplayName);
		}
		CurrenGameMode = GameModes[0];
		LobbyMenuUI->SetGameModes(GameModeNames);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("[ShooterLobby] Failed to set Game Mode. GameMode options is empty."));
	}
}

void ShooterLobby::AddPartyMember(FString UserId, bool isLeader)
{
	auto onCreateEntry = TBaseDelegate<void, FString, FSlateBrush>::CreateLambda([this, UserId, isLeader](FString DisplayName, FSlateBrush Avatar)
	{
		int32 Index = PartyMembers.IndexOfByPredicate([](UPartyMemberEntryUI* Entry){
			return Entry->Data.UserId.IsEmpty();
		});
		if (Index != INDEX_NONE)
		{
			PartyMembers[Index]->Data.UserId = UserId;
			PartyMembers[Index]->Data.DisplayName = DisplayName;
			PartyMembers[Index]->Data.Avatar = Avatar;
			PartyMembers[Index]->Data.isLeader = isLeader;
		}
		else
		{
			TWeakObjectPtr<UPartyMemberEntryUI> Entry = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
			Entry->Data.UserId = UserId;
			Entry->Data.DisplayName = DisplayName;
			Entry->Data.Avatar = Avatar;
			Entry->Data.isLeader = isLeader;
			Entry->SetInterface(this);
			PartyMembers.Add(Entry.Get());
		}
		UpdatePartyMemberList();
	});
	int32 Index = FriendList.IndexOfByPredicate([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	if (Index != INDEX_NONE)
	{
		onCreateEntry.ExecuteIfBound(FriendList[Index]->Data.DisplayName, FriendList[Index]->Data.Avatar);
	}
	else
	{
		bool isCached = FShooterCacheUtils::IsUserCacheExist(UserId);
		if (isCached)
		{
			FUserCache UserCache = FShooterCacheUtils::GetUserCache(UserId);
			FCacheBrush Avatar = FShooterCacheUtils::GetUserAvatarCache(UserId);
			if (Avatar.IsValid())
			{
				onCreateEntry.ExecuteIfBound(UserCache.DisplayName, *Avatar.Get());
			}
			else
			{
				onCreateEntry.ExecuteIfBound(UserCache.DisplayName, FSlateBrush());
			}
		}
		else
		{
			AccelByte::FRegistry::User.GetUserByUserId(
				UserId,
				THandler<FUserData>::CreateLambda([this, UserId, isLeader, onCreateEntry](const FUserData& User) mutable
					{
						FPartyMemberEntry PartyMember;
						PartyMember.UserId = UserId;
						PartyMember.DisplayName = User.DisplayName;
						PartyMember.isLeader = isLeader;
						AccelByte::FRegistry::UserProfile.GetPublicUserProfileInfo(
							UserId,
							AccelByte::THandler<FAccelByteModelsPublicUserProfileInfo>::CreateLambda([this, UserId, PartyMember](const FAccelByteModelsPublicUserProfileInfo& UserProfileInfo)
								{
									UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] Get User Public Profile: %s - > %s Success."), *UserProfileInfo.UserId, *UserProfileInfo.AvatarSmallUrl);

									FString Filename = FShooterCacheUtils::CacheDir / UserId + TEXT(".png");
									FString AvatarUrl = UserProfileInfo.AvatarSmallUrl;
									FShooterImageUtils::GetImage(
										AvatarUrl,
										FOnImageReceived::CreateLambda([this, PartyMember](const FCacheBrush Image) {
											OnAvatarReceived(Image, PartyMember);
										}),
										Filename
									);
								}
							),
							AccelByte::FErrorHandler::CreateLambda([this, PartyMember, onCreateEntry](int32 Code, FString Message)
								{
									UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetPublicUserProfileInfo Failed UserId: %s! Code: %d, Message: %s."), *PartyMember.UserId, Code, *Message);

									onCreateEntry.ExecuteIfBound(PartyMember.DisplayName, FSlateBrush());
								}
							)
						);
					}
				),
				FErrorHandler::CreateLambda([UserId, onCreateEntry](int32 Code, FString Message)
					{
						UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetUserByUserId Failed UserId: %s! Code: %d, Message: %s."), *UserId, Code, *Message);

						onCreateEntry.ExecuteIfBound(UserId, FSlateBrush());
					}
				)
			);
		}
	}
}

void ShooterLobby::UpdatePartyMemberList()
{
	if (!CurrentPartyId.IsEmpty())
	{
		if (PartyMembers.Num() > 0)
		{
			PartyMembers.RemoveAll([](UPartyMemberEntryUI* Entry) {
				return Entry->Data.UserId.IsEmpty();
			});

			LobbyMenuUI->SetOverPartyMember(0);
			if (PartyMembers[0]->Data.UserId == GameInstance->UserToken.User_id)
			{
				if (PartyMembers.Num() <= CurrenGameMode.MaxMembers)
				{
					for (int i = PartyMembers.Num(); i < CurrenGameMode.MaxMembers; i++)
					{
						TWeakObjectPtr<UPartyMemberEntryUI> Entry = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
						Entry->SetInterface(this);
						PartyMembers.Add(Entry.Get());
					}
				}
				else
				{
					LobbyMenuUI->SetOverPartyMember(PartyMembers.Num() - CurrenGameMode.MaxMembers);
				}
			}

			PartyMembers.StableSort([](const UPartyMemberEntryUI& EntryA, const UPartyMemberEntryUI& EntryB) {
				return EntryB.Data.UserId.IsEmpty() ? true : false;
			});

			if (PartyMembers.Num() > 0 && PartyMembers[0]->Data.UserId == GameInstance->UserToken.User_id)
			{
				for (int i = 1; i < PartyMembers.Num(); i++)
				{
					PartyMembers[i]->Data.isKickable = true;
				}
			}
		}

		LobbyMenuUI->UpdatePartyMemberList(PartyMembers);
		UpdateFriendList();
	}
}

void ShooterLobby::UpdatePartyMatchmakingStatus(const bool bMatchmakingStarted_)
{
	if (!CurrentPartyId.IsEmpty())
	{
		if (PartyMembers.Num() > 0)
		{
			for (auto& Members : PartyMembers)
			{
				if (bMatchmakingStarted_ == true)
				{
					Members->Data.isKickable = false;
				}
				else 
				{
					Members->Data.isKickable = true;
				}
			}
		}
		LobbyMenuUI->UpdatePartyMemberList(PartyMembers);
	}
}

void ShooterLobby::OnCreatePartyResponse(const FAccelByteModelsCreatePartyResponse& PartyInfo)
{
	if (PartyInfo.Code == TEXT("0"))
	{
		if (GameModes.Num() > 0)
		{
			CurrenGameMode = GameModes[0];
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("[ShooterLobby] GameMode options is empty."));
		}

		CurrentPartyId = PartyInfo.PartyId;

		AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

		TWeakObjectPtr<UPartyMemberEntryUI> Entry = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
		Entry->Data.UserId = GameInstance.Get()->UserToken.User_id;
		Entry->Data.DisplayName = GameInstance.Get()->UserToken.Display_name;
		if (GameInstance.Get()->PlayerAvatar.IsValid())
		{
			Entry->Data.Avatar = *GameInstance.Get()->PlayerAvatar.Get();
		}
		Entry->Data.isLeader = true;
		Entry->Data.isMySelf = true;
		Entry->SetInterface(this);
		PartyMembers.Add(Entry.Get());
		UpdatePartyMemberList();

		LobbyMenuUI->OpenPartySetupPanel();
		LobbyMenuUI->ShowGameModeComboBox(true);
	}
	else
	{
		LobbyMenuUI->OpenCreatePartyPanel();
		FString Message = TEXT("Failed to Create Party!");
		if (!PartyInfo.Code.IsEmpty())
		{
			Message.Append(FString::Printf(TEXT("\nCode: %s."), *PartyInfo.Code));
		}
		TWeakObjectPtr<UGeneralNotificationPopupUI> InvitePartyResponsePopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));
		InvitePartyResponsePopup->Show(ENotificationType::ERROR_UNKNOWN, Message);

		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] %s"), *Message);
	}
}

void ShooterLobby::OnInfoPartyResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo)
{
	if (PartyInfo.Code == TEXT("0"))
	{
		PartyMembers.RemoveAll([PartyInfo](UPartyMemberEntryUI* Entry) {
			return Entry->Data.onBeingKicked && !PartyInfo.Members.Contains(Entry->Data.UserId);
		});
		UpdatePartyMemberList();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Failed get info party! Code: %s."), *PartyInfo.Code);
	}

	// TODO: Add party chat tab
	//LobbyChatWidget->AddParty(PartyInfo.PartyId);
	//SLobby::PartyInfo = PartyInfo;
}

void ShooterLobby::OnPartyLeaveNotification(const FAccelByteModelsLeavePartyNotice& LeaveInfo)
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

	FString LeavingUserId = LeaveInfo.UserID;
	PartyMembers.RemoveAll([LeavingUserId](UPartyMemberEntryUI* Entry) {
		return Entry->Data.UserId == LeavingUserId;
	});

	FString LeaderId = LeaveInfo.LeaderID;
	int32 Index = PartyMembers.IndexOfByPredicate([LeaderId](UPartyMemberEntryUI* Entry) {
		return Entry->Data.UserId == LeaderId;
	});
	if (Index != INDEX_NONE)
	{
		PartyMembers[Index]->Data.isLeader = true;
	}

	if (LeaderId == GameInstance->UserToken.User_id)
	{
		LobbyMenuUI->ShowGameModeComboBox(true);
	}

	UpdatePartyMemberList();

	TWeakObjectPtr<UGeneralNotificationPopupUI> NotificationPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

	NotificationPopup->Show(ENotificationType::NOTIFICATION, FString("You have left the Party."));
}

void ShooterLobby::OnInvitePartyResponse(const FAccelByteModelsPartyInviteResponse& Response)
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

	if (Response.Code != TEXT("0"))
	{
		FString Message = TEXT("Failed to Invite Friend!");
		if (Response.Code == TEXT("11254"))
		{
			Message.Append(TEXT("\nFriend already has a party."));
		}
		else if (!Response.Code.IsEmpty())
		{
			Message.Append(FString::Printf(TEXT("\nCode: %s."), *Response.Code));
		}
		
		TWeakObjectPtr<UGeneralNotificationPopupUI> InvitePartyResponsePopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));
		InvitePartyResponsePopup->Show(ENotificationType::ERROR_UNKNOWN, Message);

		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] %s"), *Message);
	}
}

void ShooterLobby::OnInvitePartyKickMemberResponse(const FAccelByteModelsKickPartyMemberResponse& Response) // Kick a member
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

	if (Response.Code != TEXT("0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Failed to kick a member! Code: %s"), *Response.Code);
	}
}

// Other people Joined User's Party (Current User as Party Leader)
void ShooterLobby::OnPartyJoinNotification(const FAccelByteModelsPartyJoinNotice& Notification)
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

	FString UserId = Notification.UserId;
	int32 Index = PartyMembers.IndexOfByPredicate([UserId](UPartyMemberEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	if (Index != INDEX_NONE)
	{
		PartyMembers[Index]->Data.onInvitation = false;
		UpdatePartyMemberList();
	}
	else
	{
		AddPartyMember(UserId);
	}

	// SCENARIO: if party member is more than max party member of the gamemode, show warning notification
	
	// TODO: Show join popup
}

void ShooterLobby::OnPartyKickNotification(const FAccelByteModelsGotKickedFromPartyNotice& KickInfo) // Is Kicked
{
	if (KickInfo.UserId == GameInstance->UserToken.User_id)
	{
		PartyMembers.Empty();
		UpdatePartyMemberList();

		CurrentPartyId = TEXT("");

		UpdateFriendList();

		// TODO: show "you has been kicked" popup
		TWeakObjectPtr<UGeneralNotificationPopupUI> NotificationPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		NotificationPopup->Show(ENotificationType::NOTIFICATION, FString("You have been kicked from the Party."));
	}
	else
	{
		AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

		FString UserId = KickInfo.UserId;
		PartyMembers.RemoveAll([UserId](UPartyMemberEntryUI* Entry) {
			return Entry->Data.UserId == UserId;
		});

		TWeakObjectPtr<UGeneralNotificationPopupUI> NotificationPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));
		// TODO: Show "user name has been kicked from the party."
		NotificationPopup->Show(ENotificationType::NOTIFICATION, FString::Printf(TEXT("%s have been kicked from the Party."), *KickInfo.UserId));
	}
}

void ShooterLobby::OnLeavePartyResponse(const FAccelByteModelsLeavePartyResponse& Response)
{
	if (Response.Code == TEXT("0"))
	{
		PartyMembers.Empty();
		UpdatePartyMemberList();

		CurrentPartyId = TEXT("");

		UpdateFriendList();

		LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::PRESTART);
	}
	else if (Response.Code != TEXT("0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Failed to leave party! Code: %s."), *Response.Code);

		AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
	}
}

void ShooterLobby::OnPartyGetInvitedNotification(const FAccelByteModelsPartyGetInvitedNotice& Notification)
{
	if (!GameInstance.IsValid()) return;

	auto onGetDispayName = TBaseDelegate<void, FString, FAccelByteModelsPartyGetInvitedNotice>::CreateLambda([this](FString DisplayName, FAccelByteModelsPartyGetInvitedNotice Notification)
	{
		TWeakObjectPtr<UPartyInvitationPopupUI> PartyInvitationPopup = MakeWeakObjectPtr<UPartyInvitationPopupUI>(CreateWidget<UPartyInvitationPopupUI>(GameInstance.Get(), *GameInstance->PartyInvitationPopupClass.Get()));
		PartyInvitationPopup->Show(DisplayName, Notification);
		PartyInvitationPopup->SetInterface(this);
	});

	FString UserId = Notification.From;
	int32 Index = FriendList.IndexOfByPredicate([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	if (Index != INDEX_NONE)
	{
		onGetDispayName.ExecuteIfBound(FriendList[Index]->Data.DisplayName, Notification);
	}
	else
	{
		bool isCached = FShooterCacheUtils::IsUserCacheExist(UserId);
		if (isCached)
		{
			FUserCache UserCache = FShooterCacheUtils::GetUserCache(UserId);
			onGetDispayName.ExecuteIfBound(UserCache.DisplayName, Notification);
		}
		else
		{
			AccelByte::FRegistry::User.GetUserByUserId(
				UserId,
				THandler<FUserData>::CreateLambda([Notification, onGetDispayName](const FUserData& User) mutable
					{
						onGetDispayName.ExecuteIfBound(User.DisplayName, Notification);
					}
				),
				FErrorHandler::CreateLambda([UserId, Notification, onGetDispayName](int32 Code, FString Message)
					{
						UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] AccelByte::FRegistry::User.GetUserByUserId Failed UserId: %s! Code: %d, Message: %s."), *UserId, Code, *Message);

						onGetDispayName.ExecuteIfBound(UserId, Notification);
					}
				)
			);
		}
	}
}

// Invited as Party Member (Current User as Party member)
void ShooterLobby::OnInvitePartyJoinResponse(const FAccelByteModelsPartyJoinReponse& Response)
{
	if (Response.Code == TEXT("0"))
	{
		CurrentPartyId = Response.PartyId;

		// Add party leader
		AddPartyMember(Response.LeaderId, true);

		// Disable Matchmaking if Current User is not a leader
		FString CurrentUserId = GameInstance.Get()->UserToken.User_id;
		if (CurrentUserId != Response.LeaderId)
		{
			LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::DISABLED);
		}

		// Add member
		for (FString Member : Response.Members)
		{
			if (Member == GameInstance.Get()->UserToken.User_id)
			{
				TWeakObjectPtr<UPartyMemberEntryUI> MySelf = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
				MySelf->Data.UserId = GameInstance.Get()->UserToken.User_id;
				MySelf->Data.DisplayName = GameInstance.Get()->UserToken.Display_name;
				if (GameInstance.Get()->PlayerAvatar.IsValid())
				{
					MySelf->Data.Avatar = *GameInstance.Get()->PlayerAvatar.Get();
				}
				MySelf->Data.isMySelf = true;
				MySelf->SetInterface(this);
				PartyMembers.Add(MySelf.Get());

				UpdatePartyMemberList();

				LobbyMenuUI->OpenPartySetupPanel();
				LobbyMenuUI->ShowGameModeComboBox(false);

			}
			else if(Member != Response.LeaderId)
			{
				// If member not a party leader.
				AddPartyMember(Member);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Invited member failed to join party! Code: %s."), *Response.Code);
	}
}


void ShooterLobby::OnMatchmakingNotification(const FAccelByteModelsMatchmakingNotice & Response)
{
	UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnMatchmakingNotification..."));

	if (Response.Status == EAccelByteMatchmakingStatus::Done)
	{
		// ShooterGameTelemetry::Get().StartMatch(Response.MatchId, this->GameMode);

		FString MatchId = Response.MatchId;

		CurrentMatchId = MatchId;

		// Start Matchmaking Countdown Timer
		LobbyMenuUI->SetMatchmakingCountdown(MatchmakingCountdown);
		TSharedPtr<FTimerHandle> ReadyTimerHandle = MakeShared<FTimerHandle>();
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(*ReadyTimerHandle, FTimerDelegate::CreateLambda([this, ReadyTimerHandle]() {
			// I didn't use FPlatformTime::Seconds because this doesn't need to be that accurate;
			MatchmakingCountdown -= 1;
			LobbyMenuUI->SetMatchmakingCountdown(MatchmakingCountdown);
			if (MatchmakingCountdown == 0)
			{
				MatchmakingCountdown = READY_CONSENT_TIMEOUT;
				// TO DO : Timeout, so we need to disable Matchmaking. currently just go back to PRESTART.
				LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::PRESTART);
				GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*ReadyTimerHandle);
			}
			else if (bReadyConsent == true)
			{
				MatchmakingCountdown = READY_CONSENT_TIMEOUT;
				GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*ReadyTimerHandle);
			}

			}), 1.0f, true);

		TWeakObjectPtr<UGeneralNotificationPopupUI> ReadyConsentPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		FOnNotificationButtonClicked NotificationDelegate = FOnNotificationButtonClicked::CreateLambda([ReadyConsentPopup, MatchId, this]()
		{
			AccelByte::FRegistry::Lobby.SendReadyConsentRequest(MatchId);
			bReadyConsent = true;
			LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::READY);
			ReadyConsentPopup->ClosePopup();
		});

		FOnNotificationCloseButtonClicked OnCloseButtonClickedDelegate = FOnNotificationCloseButtonClicked::CreateLambda([this]() {
			LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::FOUND);
			});

		// Disable Ready Consent popup because of a bug in timer for now
		// TODO : Check for the crash related to the timer.
		//ReadyConsentPopup->Show(ENotificationType::BUTTON, FString("READY"), NotificationDelegate, OnCloseButtonClickedDelegate);
		LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::FOUND);
	}
	// show loading for non leader party member
	else if (Response.Status == EAccelByteMatchmakingStatus::Start)
	{
		bMatchmakingStarted = true;
		LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::INPROGRESS);
		// Start Matchmaking Duration Timer, i think we can refactor this into function.
		double MatchmakingStartTime = FPlatformTime::Seconds();
		double MatchmakingDurationTime;
		int32 TimeSeconds;
		TSharedPtr<FTimerHandle> MatchmakingTimerHandle = MakeShared<FTimerHandle>();
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(*MatchmakingTimerHandle, FTimerDelegate::CreateLambda([&, this, MatchmakingTimerHandle, MatchmakingStartTime]() 
		{
			MatchmakingDurationTime = FPlatformTime::Seconds() - MatchmakingStartTime;
			TimeSeconds = floor(MatchmakingDurationTime);

			LobbyMenuUI->SetMatchmakingDuration(TimeSeconds);

			// Lobby Disconnected
			if (!AccelByte::FRegistry::Lobby.IsConnected())
			{
				UE_LOG(LogTemp, Warning, TEXT("Disconnected From Lobby, Canceling Matchmaking"));
				bMatchmakingStarted = false;
				if (GEngine->GameViewport != nullptr)
				{
					GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
				}
			}
			// Matchmaking cancelled via Cancel Button
			else if (bMatchmakingStarted == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Stopped Finding match, Cancelling Matchmaking"));
				if (GEngine->GameViewport != nullptr)
				{
					GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
				}
			}
			else if (bAlreadyEnteringLevel)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found a Match, Entering a level, disabling Matchmake Heartbeat"));
				if (GEngine->GameViewport != nullptr)
				{
					GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Finding Match..."));
			}
		}), 1.0f, true);
	}
	else
	{
		FString FailMatchmakingReason = "UNKNOWN";
		switch (Response.Status)
		{
		case EAccelByteMatchmakingStatus::Cancel:
			FailMatchmakingReason = "Matchmaking canceled by party leader";
			break;
		case EAccelByteMatchmakingStatus::Timeout:
			FailMatchmakingReason = "Timeout";
			break;
		case EAccelByteMatchmakingStatus::Unavailable:
			FailMatchmakingReason = "Dedicated server unavailable";
			break;
		default:
			FailMatchmakingReason = FString::Printf(TEXT("Code: %d"), (int32)Response.Status);
			break;
		}

		TWeakObjectPtr<UGeneralNotificationPopupUI> FailedMatchmakingPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		FOnNotificationCloseButtonClicked OnCloseButtonClickedDelegate = FOnNotificationCloseButtonClicked::CreateLambda([this]() {
			LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::PRESTART);
		});

		FailedMatchmakingPopup->Show(ENotificationType::NOTIFICATION, FailMatchmakingReason, NULL, OnCloseButtonClickedDelegate);

		bMatchmakingStarted = false;
	}
}

void ShooterLobby::OnRematchmakingNotification(const FAccelByteModelsRematchmakingNotice & Response)
{
	UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnRematchmakingNotification..."));
	bReadyConsent = false;
	if (Response.BanDuration == 0)
	{
		TWeakObjectPtr<UGeneralNotificationPopupUI> RematchmakingPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		FOnNotificationCloseButtonClicked CloseButtonDelegate = FOnNotificationCloseButtonClicked::CreateLambda([RematchmakingPopup, this]()
			{
				bMatchmakingStarted = true;
				UpdatePartyMatchmakingStatus(bMatchmakingStarted);
			});

		RematchmakingPopup->Show(ENotificationType::NOTIFICATION, FString("Your Opponent's Party Have been Banned Because of Long Term Inactivity. We'll Rematch You with Another Party."), NULL , CloseButtonDelegate);
	}
	else
	{

		TWeakObjectPtr<UGeneralNotificationPopupUI> RematchmakingPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		FOnNotificationCloseButtonClicked CloseButtonDelegate = FOnNotificationCloseButtonClicked::CreateLambda([RematchmakingPopup, this]()
			{
				bMatchmakingStarted = false;
				UpdatePartyMatchmakingStatus(bMatchmakingStarted);
			});

		RematchmakingPopup->Show(ENotificationType::NOTIFICATION, FString::Printf(TEXT("You're Banned for %d sec Because of Long Term Inactivity. You Can Search for A Match Again After the Ban is Lifted."), Response.BanDuration), NULL, CloseButtonDelegate);
	}
}

void ShooterLobby::OnStartMatchmakingResponse(const FAccelByteModelsMatchmakingResponse & Response)
{
	UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnStartMatchmakingResponse, Respone Code = %s"), *Response.Code);
	if (Response.Code != "0")
	{
		bMatchmakingStarted = false;
		UpdatePartyMatchmakingStatus(bMatchmakingStarted);
	}
}

void ShooterLobby::OnCancelMatchmakingResponse(const FAccelByteModelsMatchmakingResponse & Response)
{
	UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] OnCancelMatchmakingResponse..."));
}

void ShooterLobby::OnDsNotification(const FAccelByteModelsDsNotice& Notice)
{
	UE_LOG(LogOnlineGame, Log, TEXT("DS Notif Status: %s"), *Notice.Status);

	if (Notice.Status.Compare(TEXT("READY")) == 0 || Notice.Status.Compare(TEXT("BUSY")) == 0)
	{
		FString ServerAddress;
		if (ShooterGameConfig::Get().IsLocalMode_)
		{
			ServerAddress = FString::Printf(TEXT("%s:%i"), *ShooterGameConfig::Get().LocalServerIP_, ShooterGameConfig::Get().ServerPort_);
		}
		else
		{
			ServerAddress = FString::Printf(TEXT("%s:%i"), *Notice.Ip, Notice.Port);
		}
		UE_LOG(LogOnlineGame, Log, TEXT("StartMatch: %s"), *ServerAddress);
		StartMatch(Notice.MatchId, CurrentPartyId, ServerAddress);
	}
	else if (Notice.Status.Compare(TEXT("CREATING")) == 0)
	{
		bAlreadyEnteringLevel = false;
	}
}

#pragma region Override Lobby Menu Interface
void ShooterLobby::AddFriend(FString Username)
{
	if (!GameInstance.IsValid()) return;

	FriendSearchResultPopup = MakeWeakObjectPtr<UFriendSearchResultPopupUI>(CreateWidget<UFriendSearchResultPopupUI>(GameInstance.Get(), *GameInstance->FriendSearchResultPopupClass.Get()));
	FriendSearchResultPopup->Show();
	AccelByte::FErrorHandler OnSearchUserFailed = AccelByte::FErrorHandler::CreateLambda([this, Username](int32 Code, FString Message)
	{
		FString ErrorMessage = Message;
		if (Code == 404)
		{
			ErrorMessage = FString::Printf(TEXT("[ShooterLobby] %s is not found."), *Username);
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ErrorMessage);

		FriendSearchResultPopup->ShowUserNotFound(Username);
	});

	AccelByte::FRegistry::User.SearchUsers(
		Username,
		AccelByte::THandler<FPagedPublicUsersInfo>::CreateLambda([this, OnSearchUserFailed](const FPagedPublicUsersInfo& Result)
			{
				FString PlayerId = GameInstance.Get()->UserToken.User_id;
				FPagedPublicUsersInfo UsersInfo = Result;
				UsersInfo.Data.RemoveAll([PlayerId](FPublicUserInfo UserInfo)
				{
					return UserInfo.UserId == PlayerId;
				});

				if (UsersInfo.Data.Num() == 0)
				{
					OnSearchUserFailed.Execute(404, TEXT("Username not found"));
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] AccelByte::FRegistry::User.SearchUsers Success."));					
					ShowFriendSearchResultPopup(UsersInfo);
				}
			}
		),
		OnSearchUserFailed
	);
}

void ShooterLobby::RefreshFriendList()
{
	FriendList.Empty();
	ReloadFriendList();
}

void ShooterLobby::StartMatchmaking(FString GameModeDisplayName)
{
	if (GEngine->GameViewport == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find Game Viewport, this shouldn't happen!"));
		return;
	}

	CurrentGameMode = *GameModes.FindByPredicate([GameModeDisplayName](FGameModeEntry Entry)
		{
			return Entry.DisplayName == GameModeDisplayName;
		});
	FString GameModeName = CurrentGameMode.GameMode;
	if (PartyMembers.Num() > CurrentGameMode.MaxMembers)
	{
		TWeakObjectPtr<UGeneralNotificationPopupUI> MatchmakingPopup = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GameInstance.Get(), *GameInstance->GeneralNotificationPopupClass.Get()));

		MatchmakingPopup->Show(ENotificationType::NOTIFICATION, FString::Printf(TEXT("Your Party has too much member, please remove some of your party member.")));

		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Start Match Called, Game Mode Name : %s"), *GameModeName);

	TSharedPtr<FTimerHandle> MatchmakingTimerHandle = MakeShared<FTimerHandle>();

	// Heartbeat to make sure Lobby is still connected into the Lobby Server
	if (bMatchmakingStarted == false)
	{
		bMatchmakingStarted = true;

		// Set the Widget Status into MatchmakingInProgress
		LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::INPROGRESS);
		UpdatePartyMatchmakingStatus(bMatchmakingStarted);

		// Update Friend List state once Matchmaking starts, need to do it to disable Invite Party while in matchmaking
		UpdateFriendList();

		double MatchmakingStartTime = FPlatformTime::Seconds();
		double MatchmakingDurationTime;
		int32 TimeSeconds;

		// we don't have access to GetWorld natively so we have to Access the Game ViewPort to get TimerManager
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(*MatchmakingTimerHandle, TFunction<void(void)>([&, MatchmakingTimerHandle, MatchmakingStartTime]()
			{
				MatchmakingDurationTime = FPlatformTime::Seconds() - MatchmakingStartTime;
				TimeSeconds = floor(MatchmakingDurationTime);

				LobbyMenuUI->SetMatchmakingDuration(TimeSeconds);

				// Lobby Disconnected
				if (!AccelByte::FRegistry::Lobby.IsConnected())
				{
					UE_LOG(LogTemp, Warning, TEXT("Disconnected From Lobby, Canceling Matchmaking"));
					bMatchmakingStarted = false;
					if (GEngine->GameViewport != nullptr)
					{
						GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
					}
				}
				// Matchmaking cancelled via Cancel Button
				else if (bMatchmakingStarted == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Stopped Finding match, Cancelling Matchmaking"));
					if (GEngine->GameViewport != nullptr)
					{
						GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
					}
				}
				else if (bAlreadyEnteringLevel)
				{
					UE_LOG(LogTemp, Warning, TEXT("Found a Match, Entering a level, disabling Matchmake Heartbeat"));
					if (GEngine->GameViewport != nullptr)
					{
						GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*MatchmakingTimerHandle);
					}
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Finding Match..."));
				}
			}), 1.0f, true, 0.f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Matchmaking Already Started"));
	}
	if (ShooterGameConfig::Get().IsLocalMode_)
	{
		AccelByte::FRegistry::Lobby.SendStartMatchmaking(
			*GameModeName,
			ShooterGameConfig::Get().LocalServerName_
		);
	}
	else
	{
		TArray<TPair<FString, float>> SelectionRegions = ShooterGameConfig::Get().SelectedRegion_;
		AccelByte::FRegistry::Lobby.SendStartMatchmaking(
			*GameModeName,
			TEXT(""),
			ShooterGameConfig::Get().ServerImageVersion_,
			ShooterGameConfig::Get().SelectedRegion_
		);
	}
}

void ShooterLobby::CancelMatchmaking()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancelling Matchmaking"));

	// I think we should bundle setting bMatchmakingStarted with UpdateFriendlist, or make a worker to continously update FriendList in the background
	bMatchmakingStarted = false;
	// Update Friend List state once Matchmaking is cancelled, need to do it to enable Invite Party
	UpdateFriendList();
	UpdatePartyMatchmakingStatus(bMatchmakingStarted);
	LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::PRESTART);

	AccelByte::FRegistry::Lobby.SendCancelMatchmaking(*CurrentGameMode.GameMode);
}

void ShooterLobby::ReadyMatchmaking()
{
	AccelByte::FRegistry::Lobby.SendReadyConsentRequest(CurrentMatchId);
	bReadyConsent = true;
	LobbyMenuUI->SetMatchmakingWidgetStatus(EMatchmakingState::READY);
}


void ShooterLobby::CreateParty()
{
	AccelByte::FRegistry::Lobby.SendCreatePartyRequest();
}

void ShooterLobby::ChangeGameMode(FString GameModeName)
{
	if(GameModes.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterLobby] Failed change GameMode. GameMode is empty."));
		return;
	}

	int32 Index = GameModes.IndexOfByPredicate([GameModeName](FGameModeEntry Entry) {
		return Entry.DisplayName == GameModeName;
	});
	if (Index != INDEX_NONE)
	{
		CurrenGameMode = GameModes[Index];

	}
	else
	{
		CurrenGameMode = GameModes[0];
	}

	UpdatePartyMemberList();
}

void ShooterLobby::StartMatch(const FString& MatchId, const FString& PartyId, const FString& DedicatedServerAddress)
{
	if (this->bAlreadyEnteringLevel == false)
	{
		this->bAlreadyEnteringLevel = true;
		UE_LOG(LogOnlineGame, Log, TEXT("OpenLevel: %s"), *DedicatedServerAddress);

		// Add delay to ensure the server has received a heartbeat response contains matchmaking result
		// Player only entering level once
		FTimerHandle dummyHandle;
		FString UserID = GameInstance->UserProfileInfo.UserId;
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(dummyHandle, TFunction<void(void)>([this, DedicatedServerAddress, PartyId, MatchId, UserID]()
		{
			GameInstance->GotoState(ShooterGameInstanceState::Playing);
			UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), FName(*DedicatedServerAddress), true, FString::Printf(TEXT("PartyId=%s?MatchId=%s?UserId=%s"), *PartyId, *MatchId, *UserID));
		}), 1.0f, false, ShooterGameConfig::Get().PlayerEnteringServerDelay_);
	}
}

#pragma endregion Override Lobby Menu Interface

#pragma region Override Friend Search Result Entry Interface
void ShooterLobby::SendFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.RequestFriend(UserId);
	ReloadFriendList();

	FriendSearchResultPopup->ClosePopup();
	LobbyMenuUI->ClearFriendUsernameField();
}
#pragma endregion Override Friend Search Result Entry Interface

#pragma region Override Friend Entry Interface
void ShooterLobby::SendPartyInvitationRequest(FString UserId)
{
	if (!CurrentPartyId.IsEmpty())
	{
		AccelByte::FRegistry::Lobby.SendInviteToPartyRequest(UserId);

		TWeakObjectPtr<UPartyMemberEntryUI> Entry = MakeWeakObjectPtr<UPartyMemberEntryUI>(CreateWidget<UPartyMemberEntryUI>(GameInstance.Get(), *GameInstance->PartyMemberEntryClass.Get()));
		Entry->Data.UserId = UserId;
		Entry->Data.DisplayName = UserId;
		Entry->Data.onInvitation = true;
		int32 Index = FriendList.IndexOfByPredicate([UserId](UFriendEntryUI* Entry) {
			return Entry->Data.UserId == UserId;
		});
		if (Index != INDEX_NONE)
		{
			Entry->Data.DisplayName = FriendList[Index]->Data.DisplayName;
			Entry->Data.Avatar = FriendList[Index]->Data.Avatar;
		}
		Entry->SetInterface(this);
		PartyMembers.Add(Entry.Get());
		UpdatePartyMemberList();
	}
}

void ShooterLobby::SendUnfriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.Unfriend(UserId);
	ReloadFriendList();

	FriendList.RemoveAll([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	UpdateFriendList();
}

void ShooterLobby::SendAcceptFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.AcceptFriend(UserId);
	ReloadFriendList();
	
	UpdateFriendEntry(UserId, EFriendType::FRIEND);
}

void ShooterLobby::SendRejectFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.RejectFriend(UserId);
	ReloadFriendList();

	FriendList.RemoveAll([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	UpdateFriendList();
}

void ShooterLobby::SendCancelFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.CancelFriendRequest(UserId);
	ReloadFriendList();

	FriendList.RemoveAll([UserId](UFriendEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});
	UpdateFriendList();
}
#pragma endregion Override Friend Entry Interface

#pragma region Override Incoming Friend Request Popup Interface
void ShooterLobby::IgnoreIncomingFriendRequest(FString UserId)
{
	ReloadFriendList();

	UpdateFriendEntry(UserId, EFriendType::INCOMING);
}

void ShooterLobby::RejectIncomingFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.RejectFriend(UserId);
	ReloadFriendList();
}

void ShooterLobby::AcceptIncomingFriendRequest(FString UserId)
{
	AccelByte::FRegistry::Lobby.AcceptFriend(UserId);
	ReloadFriendList();

	UpdateFriendEntry(UserId, EFriendType::FRIEND, EFriendPresence::ONLINE);
}
#pragma endregion Override Incoming Friend Request Popup Interface

#pragma region Override Party Member Entry Interface
void ShooterLobby::LeaveParty()
{
	AccelByte::FRegistry::Lobby.SendLeavePartyRequest();
}

void ShooterLobby::KickPartyMember(FString UserId)
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();

	int32 Index = PartyMembers.IndexOfByPredicate([UserId](UPartyMemberEntryUI* Entry) {
		return Entry->Data.UserId == UserId;
	});

	if (Index != INDEX_NONE)
	{
		if (!PartyMembers[Index]->Data.onInvitation)
		{
			AccelByte::FRegistry::Lobby.SendKickPartyMemberRequest(UserId);
		}

		PartyMembers[Index]->Data.onInvitation = false;
		PartyMembers[Index]->Data.onBeingKicked = true;
		UpdatePartyMemberList();
	}
}
#pragma endregion Override Party Member Entry Interface

#pragma region Override Party Invitation Popup Interface
void ShooterLobby::AcceptPartyInvitation(FAccelByteModelsPartyGetInvitedNotice InvitationInformation)
{
	CurrentPartyId = InvitationInformation.PartyId;
	AccelByte::FRegistry::Lobby.SendAcceptInvitationRequest(InvitationInformation.PartyId, InvitationInformation.InvitationToken);
}
#pragma endregion Override Party Invitation Popup Interface