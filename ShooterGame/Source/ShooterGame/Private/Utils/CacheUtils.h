// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCacheModels.h"

typedef TSharedPtr<const FSlateBrush> FCacheBrush;

class FShooterCacheUtils
{
public:
	/** Load user caches. */
	static void LoadUserCaches();

	/**
	* @brief Save user cache.
	*
	* @param UserCache The data of the user cache.
	*/
	static void SaveUserCache(FUserCache UserCache);

	/**
	* @brief Get user cache based on the user id.
	*
	* @param UserId The id of the user who is cached.
	* @return The data of the user cache.
	*/
	static FUserCache GetUserCache(FString UserId);

	/**
	* @brief Check wether the user cache is exist or not.
	*
	* @param UserId The id of the user.
	* @return True if the user cache is exist or false otherwise.
	*/
	static bool IsUserCacheExist(FString UserId);

	/**
	* @brief Save user avatar cached.
	*
	* @param Filename The filename of the avatar image cache.
	* @param Binary The binary file of the avatar image.
	* @return True if the avatar image cache is successfully saved of false otherwise.
	*/
	static bool SaveUserAvatarCache(const FString& Filename, const TArray<uint8>& Binary);

	/**
	* @brief Get user avatar cache.
	*
	* @param UserId The id of the user.
	* @return Avatar image brush of the user.
	*/
	static FCacheBrush GetUserAvatarCache(FString UserId);

	/** Cache directory. */
	static FString CacheDir;

private:
	/** The list of the user caches. */
	static FUserCaches UserCaches;
};
