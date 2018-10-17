// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsTelemetry.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsTelemetry() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
// End Cross Module References
class UScriptStruct* FAccelByteModelsTelemetryEvent::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsTelemetryEvent"), sizeof(FAccelByteModelsTelemetryEvent), Get_Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsTelemetryEvent(FAccelByteModelsTelemetryEvent::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsTelemetryEvent"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsTelemetryEvent
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsTelemetryEvent()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsTelemetryEvent")),new UScriptStruct::TCppStructOps<FAccelByteModelsTelemetryEvent>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsTelemetryEvent;
	struct Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Ux_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Ux;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Uuid_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Uuid;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EventType_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_EventType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EventTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_EventTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EventLevel_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_EventLevel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EventId_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_EventId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeviceId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DeviceId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Data;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ClientId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ClientId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AppId_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AppId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AgentType_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AgentType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsTelemetryEvent>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Ux_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Ux = { UE4CodeGen_Private::EPropertyClass::Int, "Ux", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, Ux), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Ux_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Ux_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Uuid_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Uuid = { UE4CodeGen_Private::EPropertyClass::Str, "Uuid", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, Uuid), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Uuid_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Uuid_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventType_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventType = { UE4CodeGen_Private::EPropertyClass::Int, "EventType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, EventType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventTime = { UE4CodeGen_Private::EPropertyClass::Str, "EventTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, EventTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventLevel_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventLevel = { UE4CodeGen_Private::EPropertyClass::Int, "EventLevel", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, EventLevel), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventLevel_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventLevel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventId_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventId = { UE4CodeGen_Private::EPropertyClass::Int, "EventId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, EventId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_DeviceId_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_DeviceId = { UE4CodeGen_Private::EPropertyClass::Str, "DeviceId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, DeviceId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_DeviceId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_DeviceId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Data_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Data = { UE4CodeGen_Private::EPropertyClass::Str, "Data", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, Data), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Data_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Data_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_ClientId_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_ClientId = { UE4CodeGen_Private::EPropertyClass::Str, "ClientId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, ClientId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_ClientId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_ClientId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AppId_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AppId = { UE4CodeGen_Private::EPropertyClass::Int, "AppId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, AppId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AppId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AppId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AgentType_MetaData[] = {
		{ "Category", "AccelByte | Models | Telemetry | TelemetryEvent" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsTelemetry.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AgentType = { UE4CodeGen_Private::EPropertyClass::Int, "AgentType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsTelemetryEvent, AgentType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AgentType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AgentType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Ux,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Uuid,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventLevel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_EventId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_DeviceId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_ClientId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AppId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::NewProp_AgentType,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsTelemetryEvent",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsTelemetryEvent),
		alignof(FAccelByteModelsTelemetryEvent),
		Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsTelemetryEvent"), sizeof(FAccelByteModelsTelemetryEvent), Get_Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsTelemetryEvent_CRC() { return 1868050427U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
