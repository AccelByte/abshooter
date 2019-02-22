#include "ImageUtils.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"

TMap<FString, TSharedPtr<const FSlateBrush>> FShooterImageUtils::ImageCache;

void FShooterImageUtils::GetImage(const FString & Url, const FOnImageReceived & OnReceived)
{
	auto Ref = ImageCache.Find(Url);
	if (Ref)
	{
		OnReceived.ExecuteIfBound(*Ref);
	}
	else
	{
		TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
		ThumbRequest->SetVerb("GET");
		ThumbRequest->SetURL(Url);
		ThumbRequest->OnProcessRequestComplete().BindLambda([OnReceived](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			TSharedPtr<const FSlateBrush> ImageBrush;
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
					UE_LOG(LogTemp, Display, TEXT("URL: %s"), *Request->GetURL())
						ImageBrush = StaticCastSharedPtr<FSlateBrush>(CreateBrush(FName(*Request->GetURL()), ImageData, ImageFormat));

					ImageCache.Add(Request->GetURL(), ImageBrush);
				}
			}
			OnReceived.ExecuteIfBound(ImageBrush);
		});
		ThumbRequest->ProcessRequest();
	}
}

TSharedPtr<FSlateDynamicImageBrush> FShooterImageUtils::CreateBrush(const FName & ResourceName, const TArray<uint8>& ImageData, const EImageFormat InFormat)
{
	TSharedPtr<FSlateDynamicImageBrush> Brush;

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
		Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
	}

	return Brush;
}
