#include "ImageUtils.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"
#include "CacheUtils.h"

TLruCache<FString, FCacheBrush> ImageCache(100);
TMap<FString, TSharedPtr<TQueue<FOnImageReceived>>> ImageReceivedQueue;
FCriticalSection ShooterImageUtilsMutex;

void FShooterImageUtils::GetImage(const FString &Url, const FOnImageReceived& OnReceived, const FString& Filename)
{
	ShooterImageUtilsMutex.Lock();
	auto Ptr = ImageCache.FindAndTouch(Url);

	if (Ptr)
	{
		OnReceived.ExecuteIfBound(*Ptr);
		ShooterImageUtilsMutex.Unlock();
	}
	else
	{
		auto QueuePtr = ImageReceivedQueue.Find(Url);
		if (!QueuePtr)
		{
			QueuePtr = &ImageReceivedQueue.Add(Url, MakeShareable(new TQueue<FOnImageReceived>()));
		}
		bool QueueEmpty = (*QueuePtr)->IsEmpty();
		(*QueuePtr)->Enqueue(OnReceived); // queue request for same url
		ShooterImageUtilsMutex.Unlock();

		if (QueueEmpty)
		{
			TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
			ThumbRequest->SetVerb("GET");
			ThumbRequest->SetURL(Url);
			ThumbRequest->OnProcessRequestComplete().BindLambda([Filename](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
			{
				FCacheBrush ImageBrush = nullptr;
				if (bWasSuccessful && Response.IsValid())
				{
					FString ContentType = Response->GetHeader("Content-Type");
					EImageFormat ImageFormat = EImageFormat::Invalid;

					if (ContentType == "image/jpeg")
					{
						ImageFormat = EImageFormat::JPEG;
					}
					else if (ContentType == "image/png")
					{
						ImageFormat = EImageFormat::PNG;
					}
					else if (ContentType == "image/bmp")
					{
						ImageFormat = EImageFormat::BMP;
					}

					if (ImageFormat != EImageFormat::Invalid)
					{
						TArray<uint8> ImageData = Response->GetContent();
						UE_LOG(LogTemp, Display, TEXT("[FShooterImageUtils] GetImage URL: %s"), *Request->GetURL());

						FString ResourceName = Request->GetURL();
						if (!Filename.IsEmpty()) ResourceName = Filename;

						ImageBrush = MakeShareable(CreateBrush(FName(*ResourceName), ImageData, ImageFormat));
						{
							FScopeLock Lock(&ShooterImageUtilsMutex);
							ImageCache.Add(Request->GetURL(), ImageBrush);
						}
						if (!Filename.IsEmpty() && ImageBrush.IsValid())
						{
							FShooterCacheUtils::SaveUserAvatarCache(Filename, ImageData);
						}
					}
				}

				{
					FScopeLock Lock(&ShooterImageUtilsMutex);
					auto QueueRef = ImageReceivedQueue.FindRef(Request->GetURL());
					if (QueueRef.IsValid())
					{
						FOnImageReceived OnImageReceived;
						while (QueueRef->Dequeue(OnImageReceived))
						{
							OnImageReceived.ExecuteIfBound(ImageBrush);
						}
					}
				}
			});
			ThumbRequest->ProcessRequest();
		}
	}
}

FSlateDynamicImageBrush* FShooterImageUtils::CreateBrush(const FName& ResourceName, const TArray<uint8>& ImageData, const EImageFormat InFormat)
{
	FSlateDynamicImageBrush* Brush = nullptr;

	uint32 BytesPerPixel = 4;
	int32 Width = 0;
	int32 Height = 0;

	bool bSucceeded = false;
	TArray<uint8> DecodedImage;
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(InFormat);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		Width = ImageWrapper->GetWidth();
		Height = ImageWrapper->GetHeight();

		const TArray<uint8>* RawData = NULL;
		
		ERGBFormat RGBFormat = ERGBFormat::RGBA;
		if (InFormat == EImageFormat::PNG || InFormat == EImageFormat::BMP)
		{
			RGBFormat = ERGBFormat::BGRA;
		}

		if (ImageWrapper->GetRaw( RGBFormat, 8, RawData))
		{
			DecodedImage = *RawData;
			bSucceeded = true;
		}
	}

	if (bSucceeded && FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), DecodedImage))
	{
		Brush = new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));
	}

	return Brush;
}

TSharedPtr<FSlateDynamicImageBrush> FShooterImageUtils::CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData)
{
	TSharedPtr<FSlateDynamicImageBrush> Brush;

	uint32 BytesPerPixel = 4;
	int32 Width = 0;
	int32 Height = 0;

	bool bSucceeded = false;
	TArray<uint8> DecodedImage;
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	int BitDepth = 8;
	//jpg
	EImageFormat ImageFormat = EImageFormat::JPEG;
	ERGBFormat RgbFormat = ERGBFormat::BGRA;
	//png
	if (ContentType.Contains(TEXT("png")))
	{
		ImageFormat = EImageFormat::PNG;
		RgbFormat = ERGBFormat::BGRA;
	}
	//bmp
	else if (ContentType.Contains(TEXT("bmp")))
	{
		ImageFormat = EImageFormat::BMP;
		RgbFormat = ERGBFormat::BGRA;
	}

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		Width = ImageWrapper->GetWidth();
		Height = ImageWrapper->GetHeight();

		const TArray<uint8>* RawData = NULL;

		if (ImageWrapper->GetRaw(RgbFormat, BitDepth, RawData))
		{
			DecodedImage = *RawData;
			bSucceeded = true;
		}
	}

	if (bSucceeded && FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), DecodedImage))
	{
		Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
	}

	return Brush;
}

FString FShooterImageUtils::MD5HashArray(const TArray<uint8>& Array)
{
	uint8 Digest[16];

	FMD5 Md5Gen;

	Md5Gen.Update(Array.GetData(), Array.Num());
	Md5Gen.Final(Digest);

	FString MD5;
	for (int32 i = 0; i < 16; i++)
	{
		MD5 += FString::Printf(TEXT("%02x"), Digest[i]);
	}
	return MD5;
}
