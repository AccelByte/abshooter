// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "HAL/PlatformTime.h"
#include "HAL/PlatformProcess.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "Misc/SingleThreadRunnable.h"


#define POLLING_INTERVAL_MS 1000

DECLARE_DELEGATE_TwoParams(FOnScheduleTickDelegate, struct FDateTime, int32);
DECLARE_DELEGATE(FOnJusticeTickDelegate);


class FJusticeAsyncTask 
{
public:
	FJusticeAsyncTask(FString URL, FString Verb, FString Content, FString ContentType):
		bDone(false), 
		URL(URL),
		Verb(Verb),
		Content(Content),
		ContentType(ContentType)
	{}
	virtual ~FJusticeAsyncTask() {}

	virtual bool IsDone()
	{
		return bDone;
	}

	virtual bool WasSuccessful()
	{
		return bDone;
	}

	virtual FString ToString() const { return TEXT("FJusticeAsyncTask"); }
	virtual void Tick();
	
	void SetAsDone() { bDone = true; }

private:
	bool bDone;
	FString URL;
	FString Verb;
	FString Content;
	FString ContentType;
};


/**
 *	Justice version of the async task manager to register the various Justice callbacks with the engine
 */
class FAsyncTaskManagerJustice : public FRunnable, FSingleThreadRunnable
{
public:

	FAsyncTaskManagerJustice():
		OnlineThreadId(0),
		WorkEvent(nullptr),
		PollingInterval(POLLING_INTERVAL_MS),
		bRequestingExit(false) {}

	~FAsyncTaskManagerJustice()	{}

	bool Init(void);
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();
	virtual void Tick() {};
	virtual void OnlineTick() ;
	void AddQueue(FString URL, FString Verb, FString Content, FString ContentType);
	void ClearQueue();

private:	
	volatile uint32 OnlineThreadId;
	static int32 InvocationCount;
	FEvent* WorkEvent;
	uint32 PollingInterval;
	FThreadSafeBool bRequestingExit;
	TArray<FJusticeAsyncTask*> InJusticeQueue;
	FCriticalSection InJusticeQueueLock;
};
