#pragma once

#include "Delegate.h"
#include "SlateBasics.h"
#include "Runtime/Core/Public/Containers/LruCache.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"

DECLARE_DELEGATE_OneParam(FOnImageReceived, TSharedPtr<const FSlateBrush>);

class FShooterImageUtils
{
public:
	//Static class doesn't have constructors or destructor
	FShooterImageUtils() = delete;
	FShooterImageUtils(const FShooterImageUtils& other) = delete;
	FShooterImageUtils& operator=(const FShooterImageUtils& other) = delete;
	FShooterImageUtils(FShooterImageUtils&& other) = delete;
	FShooterImageUtils& operator=(FShooterImageUtils&& other) = delete;
	~FShooterImageUtils() = delete;

	static void GetImage(const FString& Url, const FOnImageReceived& OnReceived);
	static TSharedPtr<FSlateDynamicImageBrush> CreateBrush(const FName& ResourceName, const TArray<uint8>& ImageData, const EImageFormat InFormat);

private:
	static TMap<FString, TSharedPtr<const FSlateBrush>> ImageCache;
};