// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "CacheUtils.h"
#include "JsonObjectConverter.h"

FUserCaches FShooterCacheUtils::UserCaches = FUserCaches();
FString FShooterCacheUtils::CacheDir = TEXT("");

void FShooterCacheUtils::LoadUserCaches()
{
	UserCaches.Caches.Empty();
	CacheDir = FPaths::ProjectSavedDir() / TEXT("Caches");
	FString SavePath = CacheDir / TEXT("UserCaches.json");

	FString CachesString;
	if (!FFileHelper::LoadFileToString(CachesString, *SavePath)) return;
	FJsonObjectConverter::JsonObjectStringToUStruct(CachesString, &UserCaches, 0, 0);
}

void FShooterCacheUtils::SaveUserCache(FUserCache UserCache)
{
	UserCaches.Caches.Add(UserCache);

	FString SavePath = CacheDir / TEXT("UserCaches.json");
	FString CachesString;
	if (!FJsonObjectConverter::UStructToJsonObjectString(UserCaches, CachesString)) return;
	FFileHelper::SaveStringToFile(CachesString, *SavePath);
}

FUserCache FShooterCacheUtils::GetUserCache(FString UserId)
{
	int32 Index = UserCaches.Caches.IndexOfByPredicate([UserId](FUserCache UserCache)
	{
		return UserCache.UserId == UserId;
	});
	return UserCaches.Caches[Index];
}

FCacheBrush FShooterCacheUtils::GetUserAvatarCache(FString UserId)
{
	TArray<uint8> ImageData;
	FString AvatarPath = CacheDir / UserId + TEXT(".png");
	FCacheBrush AvatarImage;
	if (FFileHelper::LoadFileToArray(ImageData, *AvatarPath))
	{
		AvatarImage = FShooterImageUtils::CreateBrush(TEXT("png"), FName(*AvatarPath), ImageData);
	}
	return AvatarImage;
}

bool FShooterCacheUtils::SaveUserAvatarCache(const FString& Filename, const TArray<uint8>& Binary)
{
	if (Filename.IsEmpty() || Binary.Num() == 0) return false;
	if (!FFileHelper::SaveArrayToFile(Binary, *Filename)) return false;
	return true;
}

bool FShooterCacheUtils::IsUserCacheExist(FString UserId)
{
	int32 Index = UserCaches.Caches.IndexOfByPredicate([UserId](FUserCache UserCache)
	{
		return UserCache.UserId == UserId;
	});
	if (Index == INDEX_NONE) return false;
	FString AvatarPath = CacheDir / UserId + TEXT(".png");
	return IFileManager::Get().FileExists(*AvatarPath);
}
