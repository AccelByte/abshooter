// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "AccelByteError.h"
#include "AccelByteCloudStorageModels.h"

namespace AccelByte
{
namespace Api
{

/**
 * @brief Cloud Storage API for storing binary data on the cloud
 * each player has slots
 * Each category has path, for example "/equipments/armor/legs". Items are grouped into a category. The root is equivalent to "/".
 */
class ACCELBYTEUE4SDK_API CloudStorage
{
public:
	DECLARE_DELEGATE_OneParam(FCreateSlotsSuccess, const FAccelByteModelsCreateSlotResponse&);
	static void IntializeSlots(const int32 SlotCount, const FCreateSlotsSuccess& OnSuccess, const FErrorHandler& OnError);

  DECLARE_DELEGATE_OneParam(FGetAllSlotsSuccess, const TArray<FAccelByteModelsSlot>&);
	static void GetAllSlot(const FGetAllSlotsSuccess& OnSuccess, const FErrorHandler& OnError);
	
  DECLARE_DELEGATE_OneParam(FSaveSlotSuccess, const FAccelByteModelsCreateSlotResponse&);
	static void SaveSlot(TArray<uint8> BinaryData, const FString& Tags, const FString& Label, const FSaveSlotSuccess& OnSuccess, FHttpRequestProgressDelegate OnProgress, const FErrorHandler& OnError);

  DECLARE_DELEGATE_OneParam(FLoadSlotSuccess, const TArray<uint8>&);
	static void LoadSlot(FString SlotID, const FLoadSlotSuccess& OnSuccess, const FErrorHandler& OnError);

	static void UpdateSlot(FString SlotID, const TArray<uint8> BinaryData, const FString& Tags, const FSaveSlotSuccess& OnSuccess, const FErrorHandler& OnError);

    DECLARE_DELEGATE(FDeleteSlotSuccess);
    static void DeleteSlot(FString SlotID, const FDeleteSlotSuccess& OnSuccess, const FErrorHandler& OnError);


private:
	CloudStorage() = delete; // static class can't have instance
	CloudStorage(CloudStorage const&) = delete;
	CloudStorage(CloudStorage&&) = delete;


    static void OnIntializeSlotsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FCreateSlotsSuccess OnSuccess, FErrorHandler OnError);
    static void OnGetAllSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetAllSlotsSuccess OnSuccess, FErrorHandler OnError);
    static void OnSaveSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError);
    static void OnLoadSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FLoadSlotSuccess OnSuccess, FErrorHandler OnError);
    static void OnUpdateSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError);
    static void OnDeleteSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FDeleteSlotSuccess OnSuccess, FErrorHandler OnError);


};

} // Namespace Api
} // Namespace AccelByte
