// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "Core/AvengersAsyncTaskManager.h"
#include "Core/AvengersLog.h"
#include "HAL/Event.h"
#include "HAL/PlatformProcess.h"
#include "Misc/ScopeLock.h"
#include "Core/AvengersHTTP.h"
#include "Core/AvengersError.h"

void FJusticeAsyncTask::Tick()
{
	AccelByte::FAvengersHTTP::CreateRawRequest(
		URL, 
		Verb, 
		ContentType,
		Content, AccelByte::THandler<FString>::CreateLambda([this](const FString& Result) {

		}), AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
		{
			UE_LOG(LogAvengers, Log, TEXT("Cannot send frametime telemetry: Code %d, Message: %s"), ErrorCode, *ErrorMessage);
		}));
}

//-----------------------------------------------------------------------------

int32 FAsyncTaskManagerJustice::InvocationCount = 0;

bool FAsyncTaskManagerJustice::Init(void)
{
	WorkEvent = FPlatformProcess::GetSynchEventFromPool();
	int32 PollingConfig = POLLING_INTERVAL_MS;
	//if (GConfig->GetInt(TEXT("OnlineSubsystem"), TEXT("PollingIntervalInMs"), PollingConfig, GEngineIni))
	//{
		PollingInterval = (uint32)PollingConfig;
	//}
	return WorkEvent != nullptr;
}

void FAsyncTaskManagerJustice::OnlineTick()
{
	check(FPlatformTLS::GetCurrentThreadId() == OnlineThreadId || !FPlatformProcess::SupportsMultithreading());
	int32 QueueSize = 0;
	{
		FScopeLock LockInQueue(&InJusticeQueueLock);
		QueueSize = InJusticeQueue.Num();
	}
	if (QueueSize > 0)
	{
		FJusticeAsyncTask* Task = nullptr;
		{
			FScopeLock LockInQueue(&InJusticeQueueLock);
			Task = InJusticeQueue[0];
		}

		UE_LOG(LogAvengers, Log, TEXT("Executing Online Task"));
		Task->Tick();
		{
			FScopeLock LockInQueue(&InJusticeQueueLock);
			InJusticeQueue.RemoveAt(0);
		}
	}
}

void FAsyncTaskManagerJustice::AddQueue(FString URL, FString Verb, FString Content, FString ContentType)
{
	FScopeLock Lock(&InJusticeQueueLock);
	FJusticeAsyncTask* NewTask = new FJusticeAsyncTask(URL, Verb, Content, ContentType);
	InJusticeQueue.Add(NewTask);
}

void FAsyncTaskManagerJustice::ClearQueue()
{
	FScopeLock Lock(&InJusticeQueueLock);
	InJusticeQueue.Empty();
}

uint32 FAsyncTaskManagerJustice::Run()
{
	InvocationCount++;
	check(OnlineThreadId == 0);
	FPlatformAtomics::InterlockedExchange((volatile int32*)&OnlineThreadId, FPlatformTLS::GetCurrentThreadId());
	do
	{
		// Wait for a trigger event to start work
		WorkEvent->Wait(PollingInterval);
		if (!bRequestingExit)
		{
			OnlineTick();
		}
	} while (!bRequestingExit);

	return 0;
}

void FAsyncTaskManagerJustice::Stop()
{
	UE_LOG(LogAvengers, Display, TEXT("FOnlineAsyncTaskManager::Stop() "));
	bRequestingExit = true;
	WorkEvent->Trigger();
}

void FAsyncTaskManagerJustice::Exit()
{
	UE_LOG(LogAvengers, Log, TEXT("FOnlineAsyncTaskManager::Exit() started"));
	FPlatformProcess::ReturnSynchEventToPool(WorkEvent);
	WorkEvent = nullptr;
	OnlineThreadId = 0;
	InvocationCount--;
	UE_LOG(LogAvengers, Log, TEXT("FOnlineAsyncTaskManager::Exit() finished"));
}
