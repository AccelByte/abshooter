// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AccelByteCategoryModels.h"
#include "AccelByteCategoryBlueprints.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UAccelByteBlueprintsCategory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FBlueprintErrorHandler, int32, ErrorCode, FString, ErrorMessage);
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetRootCategoriesSuccess, const TArray<FAccelByteModelsFullCategoryInfo>&, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetRootCategories(const FString& AccessToken, const FString& Namespace, const FString& Language, const FGetRootCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetRootCategoriesEasy(const FString& Language, const FGetRootCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetCategorySuccess, const FAccelByteModelsFullCategoryInfo&, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetCategory(const FString& AccessToken, const FString& Namespace, const FString& ParentPath, const FString& Language, const FGetCategorySuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetCategoryEasy(const FString& ParentPath, const FString& Language, const FGetCategorySuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetChildCategoriesSuccess, const TArray<FAccelByteModelsFullCategoryInfo>&, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetChildCategories(const FString& AccessToken, const FString& Namespace, const FString& Language, const FString& CategoryPath, const FGetChildCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetChildCategoriesEasy(const FString& Language, const FString& CategoryPath, const FGetChildCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetDescendantCategoriesSuccess, const TArray<FAccelByteModelsFullCategoryInfo>&, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetDescendantCategories(const FString& AccessToken, const FString& Namespace, const FString& Language, const FString& CategoryPath, const FGetDescendantCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Category | Api ")
	static void GetDescendantCategoriesEasy(const FString& Language, const FString& CategoryPath, const FGetDescendantCategoriesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

};