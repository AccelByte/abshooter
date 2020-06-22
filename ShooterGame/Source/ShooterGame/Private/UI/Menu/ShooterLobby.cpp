// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterLobby.h"
#include "ShooterGameInstance.h"
#include "Utils/CacheUtils.h"
#include "UMG/LobbyMenu/LobbyMenuUI.h"
#include "UMG/LobbyMenu/FriendSearchResultEntryUI.h"
#include "UMG/LobbyMenu/FriendSearchResultPopupUI.h"
#include "UMG/LobbyMenu/FriendEntryUI.h"
#include "UMG/LobbyMenu/IncomingFriendRequestPopupUI.h"
#include "UMG/LobbyMenu/AddingFriendResponsePopupUI.h"
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

	LobbyMenuUI->SetInterface(this);
}

void ShooterLobby::Connect()
{
	LobbyMenuUI->OpenConnectProcessPanel();
	SetLobbyDelegate();
	AccelByte::FRegistry::Lobby.Connect();
}

void ShooterLobby::ReloadFriendList()
{
	AccelByte::FRegistry::Lobby.SendGetOnlineUsersRequest(); // Get online friends list.
	AccelByte::FRegistry::Lobby.ListIncomingFriends();
	AccelByte::FRegistry::Lobby.ListOutgoingFriends();
}

void ShooterLobby::SetLobbyDelegate()
{
	AccelByte::Api::Lobby::FConnectSuccess OnLobbyConnectSuccess = AccelByte::Api::Lobby::FConnectSuccess::CreateLambda([this]() {
		UE_LOG(LogTemp, Log, TEXT("[ShooterLobby] Lobby Login...Connected!"));
		if (LobbyMenuUI != nullptr)
		{
			LobbyMenuUI->OpenConnectSuccessPanel();
			Initialize();
		}
	});
	AccelByte::FRegistry::Lobby.SetConnectSuccessDelegate(OnLobbyConnectSuccess);

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
	
	AccelByte::FRegistry::Lobby.SetGetAllUserPresenceResponseDelegate(AccelByte::Api::Lobby::FGetAllFriendsStatusResponse::CreateSP(this, &ShooterLobby::OnGetAllUserPresenceResponse));
	AccelByte::FRegistry::Lobby.SetLoadFriendListResponseDelegate(AccelByte::Api::Lobby::FLoadFriendListResponse::CreateSP(this, &ShooterLobby::OnLoadFriendListResponse));
	AccelByte::FRegistry::Lobby.SetListIncomingFriendsResponseDelegate(AccelByte::Api::Lobby::FListIncomingFriendsResponse::CreateSP(this, &ShooterLobby::OnListIncomingFriendsResponse));
	AccelByte::FRegistry::Lobby.SetListOutgoingFriendsResponseDelegate(AccelByte::Api::Lobby::FListOutgoingFriendsResponse::CreateSP(this, &ShooterLobby::OnListOutgoingFriendsResponse));
	AccelByte::FRegistry::Lobby.SetOnFriendRequestAcceptedNotifDelegate(AccelByte::Api::Lobby::FAcceptFriendsNotif::CreateSP(this, &ShooterLobby::OnFriendRequestAcceptedNotification));
	AccelByte::FRegistry::Lobby.SetOnIncomingRequestFriendsNotifDelegate(AccelByte::Api::Lobby::FRequestFriendsNotif::CreateSP(this, &ShooterLobby::OnIncomingRequestFriendsNotification));
	AccelByte::FRegistry::Lobby.SetUserPresenceNotifDelegate(AccelByte::Api::Lobby::FFriendStatusNotif::CreateSP(this, &ShooterLobby::OnUserPresenceNotification));
	AccelByte::FRegistry::Lobby.SetRequestFriendsResponseDelegate(AccelByte::Api::Lobby::FRequestFriendsResponse::CreateSP(this, &ShooterLobby::OnRequestFriendsResponse));
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
	FriendList.Add(Entry.Get());
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
	FriendList.StableSort([](const UFriendEntryUI& EntryA, const UFriendEntryUI& EntryB) {
		bool isSorted = false;
		if ((uint8)EntryA.Data.Type < (uint8)EntryB.Data.Type) isSorted = true;
		else if (((uint8)EntryA.Data.Type == (uint8)EntryB.Data.Type) && ((uint8)EntryA.Data.Presence < (uint8)EntryB.Data.Presence)) isSorted = true;
		return isSorted;
	});
	LobbyMenuUI->UpdateFriendList(FriendList);
}

void ShooterLobby::ShowIncomingFriendRequestPopup(FString UserId, FString DisplayName)
{
	if (!GameInstance.IsValid()) return;

	IncomingFriendRequestPopup = MakeWeakObjectPtr<UIncomingFriendRequestPopupUI>(CreateWidget<UIncomingFriendRequestPopupUI>(GameInstance.Get(), *GameInstance->IncomingFriendRequestPopupClass.Get()));
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
		}
		UpdateFriendList();
	}

	// TODO: Create notification popup.
}

void ShooterLobby::OnRequestFriendsResponse(const FAccelByteModelsRequestFriendsResponse& Response)
{
	ReloadFriendList();
	if (Response.Code == TEXT("0")) return;

	AddingFriendResponsePopup = MakeWeakObjectPtr<UAddingFriendResponsePopupUI>(CreateWidget<UAddingFriendResponsePopupUI>(GameInstance.Get(), *GameInstance->AddingFriendResponsePopupClass.Get()));
	AddingFriendResponsePopup->Show();
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
#pragma region Override Incoming Friend Request Popup Interface
