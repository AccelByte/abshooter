// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "FileUtils.h"

FString FShooterFileUtils::GetAvatarCachePatch(FString UserId)
{
	IFileManager& FileManager = IFileManager::Get();
	FString CacheTextDir = FString::Printf(TEXT("%sCache\\%s.txt"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserId);
	if (FileManager.FileExists(*CacheTextDir))
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterFileUtils] cache avatar found"));

		FString FileToLoad;
		if (FFileHelper::LoadFileToString(FileToLoad, *CacheTextDir))
		{
			UE_LOG(LogTemp, Log, TEXT("[FShooterFileUtils] File to load:%s"), *FileToLoad);
			TArray<FString> Raw;
			FileToLoad.ParseIntoArray(Raw, TEXT("\n"), true);
			if (Raw.Num() > 0)
			{
				FString ImageFilename = Raw[0];
				return FString::Printf(TEXT("%s\\Cache\\%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *ImageFilename);
			}
		}
	}
	return TEXT("");
}
