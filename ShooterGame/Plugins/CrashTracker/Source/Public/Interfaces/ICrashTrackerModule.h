// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

namespace EWriteUserCaptureVideoError
{
	/**
	 * Enumerates video capture write error codes.
	 */
	enum Type
	{
		None,

		/** The video capture instance was invalid. */
		VideoCaptureInvalid,

		/** Video capture is not running. */
		CaptureNotRunning,

		/** Failed to create destination directory for the video. */
		FailedToCreateDirectory,
	};
}


/**
 * Interface for crash tracker modules.
 */
class ICrashTrackerModule
	: public IModuleInterface
{
public:
	static inline ICrashTrackerModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ICrashTrackerModule>("CrashTracker");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("CrashTracker");
	}

public:

	/**
	 * Virtual destructor.
	 */
	virtual ~ICrashTrackerModule() { }
};
