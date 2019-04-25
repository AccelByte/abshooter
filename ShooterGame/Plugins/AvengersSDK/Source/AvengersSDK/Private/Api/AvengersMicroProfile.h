// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JsonUtilities.h"
#include "GameFramework/GameModeBase.h"
#include "Core/AvengersLog.h"

DECLARE_DELEGATE_OneParam(FOnSessionIDReadyHandler, const FString&);

/**
* @brief Exposes functions for MicroProfile related.
*/
class AVENGERSSDK_API FAvengersMicroProfile
{
public:
	FAvengersMicroProfile();
	~FAvengersMicroProfile();

	void BeginPlay(APlayerController* PlayerController);
    void EndPlay();
    void NewSession();
	void Tick(const float &DeltaTime);
	void RenderTick();
	bool SendTick(float DeltaTime);
	void CaptureDump();
    FOnSessionIDReadyHandler OnSessionIDReady;
private:
	bool bIsReady;
	FString SessionID;
    bool bIsStillHasPendingRequestSessionID;
    bool bIsSendingDump;
    FString HtmlDump;
    int BufferTimeS;
    bool bEnableDynamicIntrument;
	bool bIsDumpReady;
	float RenderTimeThreshold;
	bool bIsFirstFrametimeDrop;
	int FrametimeDropInterval; 
	int DumpingIntervalTh; 
	int FrametimeDropIntervalTh; 
	double LastDump; 

	/** Online async task runnable */
	class FAsyncTaskManagerJustice* OnlineAsyncTaskThreadRunnable;

	/** Online async task thread */
	class FRunnableThread* OnlineAsyncTaskThread;

	FTickerDelegate SendTickDelegate;
	FDelegateHandle SendTickDelegateHandle;
};
