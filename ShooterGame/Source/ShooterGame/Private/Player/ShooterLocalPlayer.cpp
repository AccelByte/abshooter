// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Player/ShooterLocalPlayer.h"
#include "OnlineSubsystemUtilsClasses.h"
#include "ShooterGameInstance.h"

UShooterLocalPlayer::UShooterLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UShooterPersistentUser* UShooterLocalPlayer::GetPersistentUser() const
{
	// if persistent data isn't loaded yet, load it
	if (PersistentUser == nullptr)
	{
		UShooterLocalPlayer* const MutableThis = const_cast<UShooterLocalPlayer*>(this);
		// casting away constness to enable caching implementation behavior
		MutableThis->LoadPersistentUser();
	}
	return PersistentUser;
}

void UShooterLocalPlayer::LoadPersistentUser()
{
	FString SaveGameName = GetNickname();

#if PLATFORM_SWITCH
	// on Switch, the displayable nickname can change, so we can't use it as a save ID (explicitly stated in docs, so changing for pre-cert)
	FPlatformMisc::GetUniqueStringNameForControllerId(GetControllerId(), SaveGameName);
#endif

	// if we changed controllerid / user, then we need to load the appropriate persistent user.
	if (PersistentUser != nullptr && ( GetControllerId() != PersistentUser->GetUserIndex() || SaveGameName != PersistentUser->GetName() ) )
	{
		PersistentUser->SaveIfDirty();
		PersistentUser = nullptr;
	}

	if (PersistentUser == NULL)
	{
		// Use the platform id here to be resilient in the face of controller swapping and similar situations.
		FPlatformUserId PlatformId = GetControllerId();

		auto Identity = Online::GetIdentityInterface();
		if (Identity.IsValid() && GetPreferredUniqueNetId().IsValid())
		{
			PlatformId = Identity->GetPlatformUserIdFromUniqueNetId(*GetPreferredUniqueNetId());
		}

		PersistentUser = UShooterPersistentUser::LoadPersistentUser(SaveGameName, PlatformId );
	}
}

void UShooterLocalPlayer::SetControllerId(int32 NewControllerId)
{
	FString SaveGameName = GetNickname();

#if PLATFORM_SWITCH
	// on Switch, the displayable nickname can change, so we can't use it as a save ID (explicitly stated in docs, so changing for pre-cert)
	FPlatformMisc::GetUniqueStringNameForControllerId(GetControllerId(), SaveGameName);
#endif

	ULocalPlayer::SetControllerId(NewControllerId);

	// if we changed controllerid / user, then we need to load the appropriate persistent user.
	if (PersistentUser != nullptr && ( GetControllerId() != PersistentUser->GetUserIndex() || SaveGameName != PersistentUser->GetName() ) )
	{
		PersistentUser->SaveIfDirty();
		PersistentUser = nullptr;
	}

	if (!PersistentUser)
	{
		LoadPersistentUser();
	}
}

FString UShooterLocalPlayer::GetNickname() const
{
	UShooterGameInstance* GameInstance = GetWorld() != NULL ? Cast<UShooterGameInstance>(GetWorld()->GetGameInstance()) : NULL;
	return GameInstance->UserProfileInfo.DisplayName;
}
