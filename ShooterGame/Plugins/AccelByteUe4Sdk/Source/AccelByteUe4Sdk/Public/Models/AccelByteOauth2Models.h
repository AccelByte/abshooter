// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "Misc/DateTime.h"
#include "CoreMinimal.h"
#include "AccelByteOauth2Models.generated.h"

// Emulate namespace with long class names

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsOauth2TokenPermission
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token | Permission")
		FString Resource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token | Permission")
		int32 Action;
};

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsOauth2TokenBan
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token | Ban")
		FString Ban;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token | Ban")
		FDateTime EndDate;
};

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsOauth2Token
{
	// UE4 JSON parser is case-insensitive and we have to match the variable names against the backend's model.
	// But "namespace" is a reserved keyword so we capitalize the first character.
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString Access_token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString Refresh_token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString Token_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		float Expires_in;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		TArray<FAccelByteModelsOauth2TokenPermission> Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		TArray<FString> Roles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		TArray<FAccelByteModelsOauth2TokenBan> Bans;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString User_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString Display_name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
		FString Namespace;
};



//{
//    "Namespace": "shootergame",
//    "UserId" : "a7ea3a4c55174658b1b435ec86db92df",
//    "DisplayName" : "Friends A",
//    "AuthType" : "EMAILPASSWD",
//    "LoginId" : "friendsA@accelbyte.net",
//    "EmailAddress" : "friendsA@accelbyte.net",
//    "OldEmailAddress" : "friendsA@accelbyte.net",
//    "CreatedAt" : "2018-08-16T01:53:02.458383712Z",
//    "Roles" : [
//        "2251438839e948d783ec0e5281daf05b"
//    ],
//    "Permissions" : [{
//            "Resource": "NAMESPACE:{namespace}:USER:{userId}:MESSAGE",
//                "Action" : 1
//
//                ,
//                "PhoneVerified" : false,
//                "EmailVerified" : false,
//                "Enabled" : true,
//                "LastEnabledChangedTime" : "0001-01-01T00:00:00Z",
//                "Country" : ""
//        }]
//}
USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsOauth2UserInfo
{
    // UE4 JSON parser is case-insensitive and we have to match the variable names against the backend's model.
    // But "namespace" is a reserved keyword so we capitalize the first character.
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString Namespace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString UserId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString AuthType;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString LoginId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Oauth2 | Models | Oauth2Token")
        FString EmailAddress;
};