// Copyright (c) 2018 - 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AvengersSettings.generated.h"

namespace AccelByte
{

class AVENGERSSDK_API AvengersSettings
{
public:
    FString BaseURL;
    FString GameVersionID;
    FString Namespace;
    FString ProjectID;
    bool    bEnableProfiler;
    bool    bEnableCrashTracker; 
    bool    bEnableProfilerWebServer;
};

} // Namespace AccelByte

/**
 * @brief UObject for storing settings into configuration file.
 */
UCLASS(Config = Engine)
class AVENGERSSDK_API UAvengersSettings : public UObject
{
    GENERATED_BODY()
public:
    UAvengersSettings();

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    FString BaseURL;

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    FString GameVersionID;

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    FString Namespace;

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    bool bEnableProfiler;

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    bool bEnableCrashTracker;

    UPROPERTY(EditAnywhere, GlobalConfig, Category = "Avengers | Settings")
    bool bEnableProfilerWebServer;
};

/**
 * @brief Get or update settings via blueprint.
 */
UCLASS(Blueprintable, BlueprintType)
class UAvengersBlueprintsSettings : public UBlueprintFunctionLibrary
{
public:
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static FString GetBaseURL();

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static FString GetGameVersionID();

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static FString GetNamespace();

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static bool GetEnableProfiler();

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static bool GetEnableCrashTracker();

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static bool GetEnableProfilerWebServer();



    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetBaseURL(const FString& BaseURL);

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetGameVersionID(const FString& GameVersionID);

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetNamespace(const FString& Namespace);

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetEnableProfiler(const bool& Enable);

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetEnableCrashTracker(const bool& Enable);

    UFUNCTION(BlueprintCallable, Category = "Avengers | Settings")
    static void SetEnableProfilerWebServer(const bool& Enable);
};
