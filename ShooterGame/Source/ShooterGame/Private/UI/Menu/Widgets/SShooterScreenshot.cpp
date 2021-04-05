// Copyright (c) 2018 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SShooterScreenshot.h"
#include "ShooterGame.h"
#include "SShooterScreenshotPreview.h"
#include "SShooterScreenshotEdit.h"
#include "SShooterScreenshotResolver.h"
#include "ShooterStyle.h"
#include "SShooterMenuWidget.h"
#include "ShooterMenuWidgetStyle.h"
#include "GalleryStyle.h"
#include "ShooterMenuWidgetStyle.h"
#include "ShooterUIHelpers.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "Api/AccelByteOrderApi.h"
#include "Api/AccelByteItemApi.h"
#include "Core/AccelByteError.h"
#include "Api/AccelByteCloudStorageApi.h"
#include "Core/AccelByteRegistry.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "Runtime/ImageWriteQueue/Public/ImagePixelData.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Engine/Public/ImageUtils.h"
#include "Models/ShooterGalleryModels.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "UMG/GeneralNotificationPopupUI.h"

using namespace AccelByte::Api;
const int SAVE_SLOT_SIZE = 4;
const FString STATUS_PENDING_CONST_STRING = "Pending";

FSlateColorBrush GreyBackgroundBrush = FSlateColorBrush(FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
FSlateColorBrush BlackBackgroundBrush = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5f));
FSlateColorBrush BackgroundImage = FSlateColorBrush(FLinearColor(1, 1, 1, 0.5f));

struct FScreenshotSelection
{
	int PreviousSaveSlot;
	int CurrentSaveSlot;
};

struct FScreenshotSelectionEntry : FScreenshotSelection
{
	const FScreenshotEntry& ScreenshotEntry;
	FScreenshotSelectionEntry(const FScreenshotSelection& ScreenshotSelection, const FScreenshotEntry& ScreenshotEntry)
		: FScreenshotSelection(ScreenshotSelection)
		, ScreenshotEntry(ScreenshotEntry)
	{}
};

struct FScreenShotSelectedEntry
{
	TSharedPtr<FScreenshotEntry> Entry;
	int SaveSlot = 0;
};

// need UTexture2D resource
TSharedPtr<TImagePixelData<FColor>> FSlateBrushToPixelData(const FSlateBrush* Brush)
{
	UTexture2D* Texture2D = Cast<UTexture2D>(Brush->GetResourceObject());

	if (!Texture2D)
	{
		return nullptr;
	}

	int Width = Texture2D->GetSizeX();
	int Height = Texture2D->GetSizeY();

	FIntPoint Size = FIntPoint(Width, Height);
	TSharedPtr<TImagePixelData<FColor>> PixelData = MakeShared<TImagePixelData<FColor>>(Size);
	TArray64<FColor>& Color = PixelData->Pixels;
	Color.SetNum(Width * Height);

	uint8* MipData = static_cast<uint8*>(Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));

	const uint8* SrcPtr = NULL;
	FColor* DestPtr = NULL;
	for (int32 y = 0; y < Height; y++)
	{
		SrcPtr = &MipData[(Height - 1 - y) * Width * sizeof(FColor)];
		DestPtr = &Color[(Height - 1 - y) * Width];
		for (int32 x = 0; x < Width; x++)
		{
			DestPtr->B = *SrcPtr++;
			DestPtr->G = *SrcPtr++;
			DestPtr->R = *SrcPtr++;
			DestPtr->A = *SrcPtr++;
			DestPtr++;
		}
	}

	// Unlock the texture
	Texture2D->PlatformData->Mips[0].BulkData.Unlock();

	return PixelData;
}

FString GetBase64Thumbnail(TSharedPtr<TImagePixelData<FColor>> PixelData, EImageFormat InFormat)
{
	IImageWrapperModule* ImageWrapperModule = FModuleManager::GetModulePtr<IImageWrapperModule>("ImageWrapper");
	if (!ensure(ImageWrapperModule))
	{
		return "";
	}

	const void* RawPtr = nullptr;
	int32 SizeBytes = 0;

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(InFormat);

	int Width = PixelData->GetSize().X;
	int Height = PixelData->GetSize().Y;

	float Scale = 240.0f / Height;
	int NewWidth = Width * Scale;
	int NewHeight = Height * Scale;
	TArray<FColor> ResizedImage;
	ResizedImage.SetNum(NewWidth * NewHeight);
	FImageUtils::ImageResize(Width, Height, PixelData->Pixels, NewWidth, NewHeight, ResizedImage, false);

	RawPtr = static_cast<const void*>(&ResizedImage[0]);
	SizeBytes = ResizedImage.Num() * sizeof(FColor);
	{
		uint8      BitDepth = PixelData->GetBitDepth();
		ERGBFormat PixelLayout = PixelData->GetPixelLayout();

		if (ImageWrapper->SetRaw(ResizedImage.GetData(), SizeBytes, NewWidth, NewHeight, PixelLayout, BitDepth))
		{            
            
			//TArray64<uint8> Array = ImageWrapper->GetCompressed();
            TArray<uint8> Array32;
            ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, Array32);
			return FBase64::Encode(Array32);
		}
	}
	return "";
}

TArray64<uint8> GetCompressedImage(TSharedPtr<TImagePixelData<FColor>> PixelData, EImageFormat InFormat)
{
	IImageWrapperModule* ImageWrapperModule = FModuleManager::GetModulePtr<IImageWrapperModule>("ImageWrapper");
	if (!ensure(ImageWrapperModule))
	{
		return TArray64<uint8>();
	}

	const void* RawPtr = nullptr;
	int32 SizeBytes = 0;

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(InFormat);

	int Width = PixelData->GetSize().X;
	int Height = PixelData->GetSize().Y;

	RawPtr = static_cast<const void*>(&PixelData->Pixels[0]);
	SizeBytes = PixelData->Pixels.Num() * sizeof(FColor);
	{
		uint8      BitDepth = PixelData->GetBitDepth();
		ERGBFormat PixelLayout = PixelData->GetPixelLayout();

		if (ImageWrapper->SetRaw(RawPtr, SizeBytes, Width, Height, PixelLayout, BitDepth))
		{
			return ImageWrapper->GetCompressed();
		}
	}

	return TArray64<uint8>();
}

TArray64<uint8> GetCompressedAndScaledImage(TSharedPtr<TImagePixelData<FColor>> PixelData, EImageFormat InFormat)
{
    IImageWrapperModule* ImageWrapperModule = FModuleManager::GetModulePtr<IImageWrapperModule>("ImageWrapper");
    if (!ensure(ImageWrapperModule))
    {
        return TArray64<uint8>();
    }

	const void* RawPtr = nullptr;
	int32 SizeBytes = 0;

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(InFormat);

	int Width = PixelData->GetSize().X;
	int Height = PixelData->GetSize().Y;

	float Scale = 240.0f / Height;
	int NewWidth = Width * Scale;
	int NewHeight = Height * Scale;
	TArray<FColor> ResizedImage;
	ResizedImage.SetNum(NewWidth * NewHeight);
	FImageUtils::ImageResize(Width, Height, PixelData->Pixels, NewWidth, NewHeight, ResizedImage, false);

	RawPtr = static_cast<const void*>(&ResizedImage[0]);
	SizeBytes = ResizedImage.Num() * sizeof(FColor);
	{
		uint8      BitDepth = PixelData->GetBitDepth();
		ERGBFormat PixelLayout = PixelData->GetPixelLayout();

        if (ImageWrapper->SetRaw(ResizedImage.GetData(), SizeBytes, NewWidth, NewHeight, PixelLayout, BitDepth))
        {            
            return ImageWrapper->GetCompressed();
        }
    }

    return TArray64<uint8>();
}

static FString MD5HashArray(const TArray<uint8>& Array)
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

class SScreenshotSlotComboBox : public SCompoundWidget
{
public:
	typedef typename TSlateDelegates<const FScreenshotSelection&>::FOnSelectionChanged FOnSelectionChanged;

	SLATE_BEGIN_ARGS(SScreenshotSlotComboBox)
	{}
	SLATE_ARGUMENT(TSharedPtr<FScreenshotComboBoxGroup>, ComboBoxGroup)
	SLATE_ARGUMENT(int32, SaveSlot)
	SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged)
	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs)
	{
		ComboBoxGroup = InArgs._ComboBoxGroup;
		OnSelectionChanged = InArgs._OnSelectionChanged;
		Options = MakeShareable(new TArray<FScreenshotComboBoxType>());
		for (FScreenshotComboBoxType Item : *ComboBoxGroup->AvailableOptions)
		{
			Options->Add(Item);
		}

		if (InArgs._SaveSlot != 0)
		{
			size_t i = 0;
			for (i = 0; i < Options->Num(); i++)
			{
				if (*(*Options.Get())[i] >= InArgs._SaveSlot)
				{
					break;
				}
			}
			CurrentItem = MakeShareable(new int{ InArgs._SaveSlot });
			Options->Insert(CurrentItem, i);
		}
		else
		{
			CurrentItem = (*Options)[0];
		}

		ChildSlot
		[
			SAssignNew(ComboBox, SComboBox<FScreenshotComboBoxType>)
			.OptionsSource(Options.Get())
			.OnSelectionChanged(this, &SScreenshotSlotComboBox::InternalOnSelectionChanged)
			.OnGenerateWidget(this, &SScreenshotSlotComboBox::MakeWidgetForOption)
			.InitiallySelectedItem(CurrentItem)
			[
				SNew(STextBlock)
				.Text(this, &SScreenshotSlotComboBox::GetCurrentItemLabel)
			]
		];
	}

	TSharedRef<SWidget> MakeWidgetForOption(FScreenshotComboBoxType InOption)
	{
		return SNew(STextBlock).Text(GetItemLabel(InOption));
	}

	FText GetItemLabel(FScreenshotComboBoxType InItem) const
	{
		if (*InItem != 0)
		{
			return FText::FromString(FString::Printf(TEXT("Slot %d"), *InItem));
		}
		return FText::FromString("Select Slot");
	}

	FText GetCurrentItemLabel() const
	{
		return GetItemLabel(CurrentItem);
	}

	void RefreshOptions()
	{
		Options->Empty();

		for (FScreenshotComboBoxType item : *ComboBoxGroup->AvailableOptions)
		{
			Options->Add(item);
		}

		if (*CurrentItem != 0)
		{
			size_t i;
			for (i = 0; i < ComboBoxGroup->AvailableOptions->Num(); i++)
			{
				if (*(*ComboBoxGroup->AvailableOptions)[i] > *CurrentItem)
				{
					break;
				}
			}
			Options->Insert(CurrentItem, i);
		}
		ComboBox->RefreshOptions();
	}

private:
	void InternalOnSelectionChanged(FScreenshotComboBoxType InItem, ESelectInfo::Type SelectInfo)
	{
		if (!InItem.IsValid())
		{
			return;
		}

		if (*CurrentItem != 0)
		{
			// insert shorted
			size_t i;
			for (i = 0; i < ComboBoxGroup->AvailableOptions->Num(); i++)
			{
				if (*(*ComboBoxGroup->AvailableOptions)[i] > *CurrentItem)
				{
					break;
				}
			}
			ComboBoxGroup->AvailableOptions->Insert(CurrentItem, i);
		}

		Options->Empty();
		for (FScreenshotComboBoxType Item : *ComboBoxGroup->AvailableOptions)
		{
			Options->Add(Item);
		}

		if (*InItem != 0)
		{
			ComboBoxGroup->AvailableOptions->Remove(InItem);
		}

		int PreviousSaveSlot = *CurrentItem;
		int CurrentSaveSlot = *InItem;
		CurrentItem = InItem;

		for (TSharedPtr<SScreenshotSlotComboBox> Item : ComboBoxGroup->ListComboBox)
		{
			Item->RefreshOptions();
		}

		OnSelectionChanged.ExecuteIfBound(FScreenshotSelection{PreviousSaveSlot, CurrentSaveSlot}, SelectInfo);
	}

	FOnSelectionChanged OnSelectionChanged;

	FScreenshotComboBoxType CurrentItem;
	TSharedPtr<TArray<FScreenshotComboBoxType>> Options;
	TSharedPtr<FScreenshotComboBoxGroup> ComboBoxGroup;
	TSharedPtr<SComboBox<FScreenshotComboBoxType>> ComboBox;
};

class SShooterScreenshotListItem : public STableRow< TSharedPtr<FScreenShotSelectedEntry> >
{
public:
	typedef typename TSlateDelegates<const FScreenshotSelectionEntry&>::FOnSelectionChanged FOnSelectionChanged;

	SLATE_BEGIN_ARGS(SShooterScreenshotListItem) {}
	SLATE_ARGUMENT(TSharedPtr<FScreenshotComboBoxGroup>, ComboBoxGroup)
	SLATE_EVENT(FOnSelectionChanged, OnComboBoxSelectionChanged)
	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FScreenShotSelectedEntry> InItem)
	{
		Item = InItem;
		PlayerOwner = InPlayerOwner;
		OnComboBoxSelectionChanged = InArgs._OnComboBoxSelectionChanged;

		STableRow< TSharedPtr<FScreenShotSelectedEntry> >::Construct(STableRow::FArguments(), InOwnerTable);
	
		ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(FMargin(0, 10))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.WidthOverride(200)
				.HeightOverride(100)
				[
					SNew(SScaleBox)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Center)
					.Stretch(EStretch::ScaleToFit)
					[
						SNew(SImage)
						.Image(!InItem->Entry->Image.IsValid() ? FShooterStyle::Get().GetBrush("ShooterGame.Image") : InItem->Entry->Image.Get())
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString(InItem->Entry->Title))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(SlotComboBox, SScreenshotSlotComboBox).ComboBoxGroup(InArgs._ComboBoxGroup)
					.SaveSlot(InItem->SaveSlot)
					.OnSelectionChanged_Lambda([&](const FScreenshotSelection& InItem, ESelectInfo::Type SelectInfo)
					{
						if (this->Item.IsValid())
						{
							const FScreenshotEntry& Entry = *(this->Item.Pin().Get()->Entry);
							this->Item.Pin()->SaveSlot = InItem.CurrentSaveSlot;
							
							OnComboBoxSelectionChanged.ExecuteIfBound(FScreenshotSelectionEntry(InItem, Entry), SelectInfo);
						}
					})
				]
			]
		];

		InArgs._ComboBoxGroup->ListComboBox.Add(SlotComboBox);
	}

	/** pointer to Item */
	TWeakPtr<FScreenShotSelectedEntry> Item;

	/** pointer to our owner PC */
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;

	TSharedPtr<SScreenshotSlotComboBox> SlotComboBox;

	FOnSelectionChanged OnComboBoxSelectionChanged;
};

class SShooterScreenshotTileItem : public STableRow< TSharedPtr<FScreenshotEntry> >
{
	const FGalleryStyle *GalleryStyle;
	
public:
	DECLARE_DELEGATE_OneParam(FOnDeleteClick, const FString&)
	DECLARE_DELEGATE_OneParam(FOnResolveClick, int32)
	DECLARE_DELEGATE_OneParam(FOnRetryClick, int32)

	SLATE_BEGIN_ARGS(SShooterScreenshotTileItem) {}
	SLATE_EVENT(FOnDeleteClick, OnDeleteClick)
	SLATE_EVENT(FOnResolveClick, OnResolveClick)
	SLATE_EVENT(FOnRetryClick, OnRetryClick)
	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FScreenshotEntry> InItem)
	{
		Item = InItem;
		PlayerOwner = InPlayerOwner;
		OnDeleteClick = InArgs._OnDeleteClick;
		OnResolveClick = InArgs._OnResolveClick;
		OnRetryClick = InArgs._OnRetryClick;

		GalleryStyle = &FShooterStyle::Get().GetWidgetStyle<FGalleryStyle>("DefaultGalleryMenuStyle");

		STableRow< TSharedPtr<FScreenshotEntry> >::Construct(STableRow::FArguments().ShowSelection(false) , InOwnerTable);

		ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(4)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&GalleryStyle->SlotBackground)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.Padding(FMargin(5))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.FillHeight(1)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SScaleBox)
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Center)
						.Stretch(EStretch::ScaleToFit)
						[
							SNew(SImage)
							.Image(this, &SShooterScreenshotTileItem::GetScreenshotImage)
						]
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SImage)
						.Image(&InactiveBrush)
						.Visibility(this, &SShooterScreenshotTileItem::ShowInactiveBackground)
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Right)
					[
						SNew(SBox)
						.WidthOverride(20)
						.HeightOverride(20)
						.Visibility(this, &SShooterScreenshotTileItem::ShowCloudImage)
						[
							SNew(SImage)
							.Image(this, &SShooterScreenshotTileItem::GetCloudImage)
						]
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SSafeZone)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.Padding(10.0f)
						.IsTitleSafe(true)
						[
							SAssignNew(LoadingBar, SThrobber)
							.Visibility(this, &SShooterScreenshotTileItem::ShowLoadingBar)
						]
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					SNew(SImage)
					.Image(&GalleryStyle->SlotTextImage)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(VAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Bottom)
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString::Printf(TEXT("SLOT %0d"), InItem->SlotNumber)))
						.TextStyle(&GalleryStyle->SlotNumberStyle)
					]
					+ SHorizontalBox::Slot()
					.Padding(FMargin(5, 0, 0, 0))
					.FillWidth(1)
					.VAlign(VAlign_Bottom)
					[
						SAssignNew(TextTitle, STextBlock)
						.Text(this, &SShooterScreenshotTileItem::GetTitle)
						.TextStyle(&GalleryStyle->SlotTitleStyle)
					]
				]
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SAssignNew(SelectedWidget, SImage)
				.Image(&SelectedBrush)
				.Visibility(this, &SShooterScreenshotTileItem::GetSelectedVisibility)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SShooterScreenshotTileItem::GetSelectedVisibility)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 0))
				.AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(40)
					.HeightOverride(40)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SButton) // preview button
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						.ButtonStyle(&GalleryStyle->ZoomOut)
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							SAssignNew(this->ScreenshotPreviewWidget, SShooterScreenshotPreview)
								.Image(Item.Pin()->Image.Get());
							this->ScreenshotPreviewWidget->Show();
							return FReply::Handled();
						}))
					]
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 0))
				.AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(40)
					.HeightOverride(40)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SButton) // edit button
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						.ButtonStyle(&GalleryStyle->Edit)
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							SAssignNew(this->ScreenshotEditWidget, SShooterScreenshotEdit)
								.Entry(Item.Pin().Get())
								.OnSave(SShooterScreenshotEdit::FOnSave::CreateLambda([&]() {
									TextTitle->SetText(FText::FromString(Item.Pin()->Title));
									FRegistry::CloudStorage.UpdateSlotMetadata(Item.Pin()->SlotID, "", { "" }, Item.Pin()->Title, "", nullptr, nullptr, nullptr);
								}));
							this->ScreenshotEditWidget->Show();
							return FReply::Handled();
						}))
					]
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 0))
				.AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(40)
					.HeightOverride(40)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SButton) // delete button
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						.ButtonStyle(&GalleryStyle->Close)
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							OnDeleteClick.ExecuteIfBound(Item.Pin()->SlotID);
							return FReply::Handled();
						}))
					]
				]
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SVerticalBox)
				.Visibility(this, &SShooterScreenshotTileItem::ShowConflict)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Conflict"))
				] 
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton) // Resolve
					.ButtonStyle(&GalleryStyle->Resolve)
					.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
						OnResolveClick.ExecuteIfBound(Item.Pin()->SlotNumber - 1);
						return FReply::Handled();
					}))
				]
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SVerticalBox)
				.Visibility(this, &SShooterScreenshotTileItem::ShowRetry)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Upload Failed"))
				] 
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton) // Retry
					.ButtonStyle(&GalleryStyle->Retry)
					.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
						OnRetryClick.ExecuteIfBound(Item.Pin()->SlotNumber - 1);
						return FReply::Handled();
					}))
				]
			]
		];
	}

	const FSlateBrush* GetScreenshotImage() const 
	{
		return !Item.Pin()->Image.IsValid() ? &GalleryStyle->SlotEmptyBackground : Item.Pin()->Image.Get();
	}

	const FSlateBrush* GetCloudImage() const
	{
		switch (Item.Pin()->State)
		{
		case DONE:
			return &GalleryStyle->CloudDone;
		case DOWNLOADING:
			return &GalleryStyle->CloudDownload;
		case UPLOADING:
			return &GalleryStyle->CloudUpload;
		case ERROR_UNKNOWN:
		case ERROR_UPLOAD:
			return &GalleryStyle->CloudOff;
		case CONFLICT:
			return &GalleryStyle->SyncProblem;
		}

		return &GalleryStyle->CloudOff;
	}

	FText GetTitle() const
	{
		return FText::FromString(Item.Pin()->Title);
	}


	EVisibility ShowLoadingBar() const
	{
		if (Item.Pin()->State <= DONE)
		{
			return EVisibility::Hidden;
		}
		else
		{
			return EVisibility::Visible;
		}
	}

	EVisibility ShowInactiveBackground() const
	{
		if (Item.Pin()->State > DONE || Item.Pin()->State == CONFLICT)
		{
			return EVisibility::Visible;
		}
		else
		{
			return EVisibility::Hidden;
		}
	}

	EVisibility ShowCloudImage() const
	{
		return Item.Pin()->State == NONE ? EVisibility::Hidden : EVisibility::Visible;
	}

	EVisibility ShowConflict() const
	{
		return Item.Pin()->State == CONFLICT ? EVisibility::Visible : EVisibility::Collapsed;
	}

	EVisibility ShowRetry() const
	{
		return Item.Pin()->State == ERROR_UPLOAD ? EVisibility::Visible : EVisibility::Collapsed;
	}

	EVisibility GetSelectedVisibility() const {
		return IsSelected() 
			&& Item.IsValid() 
			&& Item.Pin()->Image.IsValid() 
			&& Item.Pin()->State != CONFLICT
			? EVisibility::Visible 
			: EVisibility::Collapsed;
	}

private:
	static const FSlateColorBrush BorderBrush;
	static const FSlateColorBrush ImageBrush;
	static const FSlateColorBrush SelectedBrush;
	static const FSlateColorBrush ButtonBackgrounBrush;
	static const FSlateColorBrush InactiveBrush;

	TSharedPtr< class SShooterScreenshotPreview > ScreenshotPreviewWidget;
	TSharedPtr< class SShooterScreenshotEdit > ScreenshotEditWidget;
	TSharedPtr<SWidget> SelectedWidget;
	FTableRowStyle Style;

	TSharedPtr<SThrobber> LoadingBar;

	TSharedPtr<STextBlock> TextTitle;

	FOnDeleteClick OnDeleteClick;
	FOnResolveClick OnResolveClick;
	FOnRetryClick OnRetryClick;

	/** pointer to Item */
	TWeakPtr<FScreenshotEntry> Item;

	/** pointer to our owner PC */
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
};

const FSlateColorBrush SShooterScreenshotTileItem::BorderBrush{ FLinearColor(0, 0, 0) };
const FSlateColorBrush SShooterScreenshotTileItem::ImageBrush{ FLinearColor(1, 1, 1) };
const FSlateColorBrush SShooterScreenshotTileItem::SelectedBrush{ FLinearColor(0, 1, 1, 0.3) };
const FSlateColorBrush SShooterScreenshotTileItem::ButtonBackgrounBrush{ FLinearColor(0.3, 0.3, 0.3) };
const FSlateColorBrush SShooterScreenshotTileItem::InactiveBrush{ FLinearColor(0, 0, 0, 0.5) };

SShooterScreenshot::SShooterScreenshot()
	:bMainMenuMode(false)
{
}

void SShooterScreenshot::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	bIsMenuUp = false;
	
	const FGalleryStyle *GalleryStyle;
	GalleryStyle = &FShooterStyle::Get().GetWidgetStyle<FGalleryStyle>("DefaultGalleryMenuStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");

	const int32 TileWidth = 430;
	const int32 TileHeight = 300;
	const int32 TileColumn = 2;
	const int32 TileRow = 2;

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.HeightOverride(TAttribute<FOptionalSize>::Create([&]() { return GetScreenSize().Y; }))
			.WidthOverride(TAttribute<FOptionalSize>::Create([&]() { return GetScreenSize().X; }))
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&GalleryStyle->GalleryBackground)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(0, 0, 30, 0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(0)
				.WidthOverride(TileWidth * TileColumn)
				.HeightOverride(TileHeight * TileRow + 4 )
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SAssignNew(SavedScreenshotListWidget, STileView< TSharedPtr<FScreenshotEntry> >)
						.ItemWidth(TileWidth)
						.ItemHeight(TileHeight)
						.ListItemsSource(&SavedScreenshotList)
						.ScrollbarVisibility(EVisibility::Collapsed)
						.OnSelectionChanged(this, &SShooterScreenshot::EntrySelectionChanged)
						.OnGenerateTile(this, &SShooterScreenshot::OnGenerateWidgetForTileView)
						.SelectionMode(ESelectionMode::Single)
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.WidthOverride(870)
				.HeightOverride(TileHeight * TileRow + 4)
				.Visibility(TAttribute<EVisibility>::Create([&]() { return bMainMenuMode ? EVisibility::Hidden : EVisibility::Visible; }))
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						SNew(SImage)
						.Image(&GalleryStyle->GalleryListViewBackground)
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SAssignNew(ScreenshotListWidget, SListView< TSharedPtr<FScreenShotSelectedEntry> >)
						.ListItemsSource(&ScreenshotList)
						.OnGenerateRow(this, &SShooterScreenshot::OnGenerateWidgetForListView)
						.OnRowReleased(this, &SShooterScreenshot::OnReleaseWidgetForListView)
						.SelectionMode(ESelectionMode::Single)
					]

				]
			]
		]

		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Right)
		.Padding(0, 0, 200, 17)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.ButtonStyle(&MenuStyle->EscapeButton)
				.VAlign(VAlign_Bottom)
				.Visibility(TAttribute<EVisibility>::Create([&]() { return bMainMenuMode ? EVisibility::Visible : EVisibility::Collapsed; }))
				.OnClicked(FOnClicked::CreateLambda([&]()
				{
					static_cast<SShooterMenuWidget*>(OwnerWidget.Get())->MenuGoBack();
					return FReply::Handled();
				}))
			]
			+ SHorizontalBox::Slot()
			.Padding(10, 0, 0, 0)
			.AutoWidth()
			[
				SNew(SImage)
				.Visibility(TAttribute<EVisibility>::Create([&]() { return bMainMenuMode ? EVisibility::Visible : EVisibility::Collapsed; }))
				.Image(&MenuStyle->EscapeMainMenuInfo)
			]
		]
	];
	ComboBoxGroup = MakeShareable(new FScreenshotComboBoxGroup);
	ComboBoxGroup->AvailableOptions = MakeShareable(new TArray<FScreenshotComboBoxType>());
	for (int i = 0; i <= SAVE_SLOT_SIZE; i++)
	{
		ComboBoxGroup->AvailableOptions->Add(MakeShareable(new int{ i }));
		PreviousSelectedScreenshot.Add(FScreenshotEntry());
	}

	BuildScreenshotItem();
}

FVector2D SShooterScreenshot::GetScreenSize() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return Result;
}

FString SShooterScreenshot::GetScreenshotsDir() const
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString ScreenshotsDir = FPaths::ProjectSavedDir() / "Screenshots";
	if (!PlatformFile.DirectoryExists(*ScreenshotsDir))
	{
		PlatformFile.CreateDirectory(*ScreenshotsDir);

		if (!PlatformFile.DirectoryExists(*ScreenshotsDir))
		{
			return "";
		}
	}      
	return ScreenshotsDir;
}

FString SShooterScreenshot::GetUserScreenshotsDir() const
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());

	if (GI->UserProfileInfo.UserId.IsEmpty())
	{
		return "";
	}

	FString ScreenshotsDir = FPaths::ProjectSavedDir() / "Screenshots" / GI->UserProfileInfo.UserId;
	if (!PlatformFile.DirectoryExists(*ScreenshotsDir))
	{
		PlatformFile.CreateDirectory(*ScreenshotsDir);

		if (!PlatformFile.DirectoryExists(*ScreenshotsDir))
		{
			return "";
		}
	}
	return ScreenshotsDir;
}

bool SShooterScreenshot::IsScreenshotMetadataExists()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString ScreenshotsDir = GetScreenshotsDir();
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());

	if (GI->UserProfileInfo.UserId.IsEmpty())
	{
		return false;
	}

	FString SavePath = ScreenshotsDir / GI->UserProfileInfo.UserId + ".json";

	return PlatformFile.FileExists(*SavePath);
}

void SShooterScreenshot::SaveScreenshotMetadata()
{
	FString ScreenshotsDir = GetScreenshotsDir();

	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());

	if (GI->UserProfileInfo.UserId.IsEmpty())
	{
		return;
	}

	FString SavePath = ScreenshotsDir / GI->UserProfileInfo.UserId + ".json";
	FScreenshotSave ScreenshotSave;
	FString SaveString;

	ScreenshotSave.Screenshots = LocalSlots;

	if (FJsonObjectConverter::UStructToJsonObjectString(ScreenshotSave, SaveString))
	{
		if (FFileHelper::SaveStringToFile(SaveString, *SavePath))
		{
			UE_LOG(LogTemp, Log, TEXT("File successfullly saved, Path :%s"), *SavePath)
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("File failed to saved, Path :%s"), *SavePath)
		}
	}
}

void SShooterScreenshot::LoadScreenshotMetadata()
{
	FString ScreenshotsDir = GetScreenshotsDir();

	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());

	if (GI->UserProfileInfo.UserId.IsEmpty())
	{
		return;
	}

	FString SavePath = ScreenshotsDir / GI->UserProfileInfo.UserId + ".json";

	FString SaveString;
	FFileHelper::LoadFileToString(SaveString, *SavePath);

	FScreenshotSave ScreenshotSave;
	FJsonObjectConverter::JsonObjectStringToUStruct(SaveString, &ScreenshotSave, 0, 0);
	LocalSlots = ScreenshotSave.Screenshots;
	
}

void SShooterScreenshot::SaveLocalScreenshotImage(int32 Index, const TArray64<uint8>& Binary)
{
	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

	FFileHelper::SaveArrayToFile(Binary, *ImageName);
}

void SShooterScreenshot::SaveScreenshotCloudImage(int32 Index, const TArray64<uint8>& Binary)
{
	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + "-cloud.png";

	FFileHelper::SaveArrayToFile(Binary, *ImageName);
}

void SShooterScreenshot::ResolveUseCloudScreenshot(int32 Index)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString CloudImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + "-cloud.png";
	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

	PlatformFile.DeleteFile(*ImageName);
	PlatformFile.MoveFile(*CloudImageName, *ImageName);
}

void SShooterScreenshot::ResolveUseLocalScreenshot(int32 Index)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString CloudImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + "-cloud.png";

	PlatformFile.DeleteFile(*CloudImageName);
}

bool SShooterScreenshot::LoadScreenshotImage(int32 Index, TArray64<uint8>& Result)
{
	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return false;
	}

	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

	return FFileHelper::LoadFileToArray(Result, *ImageName);
}

void SShooterScreenshot::DeleteScreenshotImage(int32 Index)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

	PlatformFile.DeleteFile(*ImageName);
}

bool SShooterScreenshot::IsDownloadedSlotValid(int32 Index) const
{
	if (Index < 4)
	{
		const FString ScreenshotsDir = GetUserScreenshotsDir();

		if (ScreenshotsDir.IsEmpty())
		{
			return false;
		}

		const FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

		if (!FPaths::FileExists(ImageName))
		{
			return false;
		}

		TArray<uint8> Data;
		bool Result = FFileHelper::LoadFileToArray(Data, *ImageName);

		if (!Result)
		{
			return false;
		}

		const FString Hash = MD5HashArray(Data);
		Result = Hash == LocalSlots[Index].Checksum;
		return Result;
	}
	else
	{
		return false;
	}
}

void SShooterScreenshot::SaveToCloud(int32 Index)
{
	TArray64<uint8> ImageData64;
	LoadScreenshotImage(Index, ImageData64);

    TArray<uint8> ImageData(MoveTemp(ImageData64));

	FString Label = SavedScreenshotList[Index]->Title;
	TArray<FString> Tags = { FString::Printf(TEXT("SlotIndex=%d"), Index) };
	FString SlotId = LocalSlots[Index].SlotId;

	LocalSlots[Index].Status_DEPRECATED = STATUS_PENDING_CONST_STRING;
	LocalSlots[Index].Checksum = MD5HashArray(ImageData);

	SaveScreenshotMetadata();

	SavedScreenshotList[Index]->State = UPLOADING;

	auto OnSuccess = AccelByte::THandler<FAccelByteModelsSlot>::CreateLambda([&, Index](const FAccelByteModelsSlot& Output) {
		if (Output.Checksum == LocalSlots[Index].Checksum)
		{
			UE_LOG(LogTemp, Log, TEXT("File successfully saved, Index: %d, SlotID :%s"), Index, *Output.SlotId);
			SavedScreenshotList[Index]->State = DONE;
			SavedScreenshotList[Index]->Title = Output.Label;
			SavedScreenshotList[Index]->SlotID = Output.SlotId;

			LocalSlots[Index].UserId = Output.UserId;
			LocalSlots[Index].SlotId = Output.SlotId;
			LocalSlots[Index].Label = Output.Label;
			LocalSlots[Index].MimeType = Output.MimeType;
			LocalSlots[Index].Namespace = Output.Namespace;
			LocalSlots[Index].OriginalName = Output.OriginalName;
			LocalSlots[Index].SlotId = Output.SlotId;
			LocalSlots[Index].Status_DEPRECATED = Output.Status_DEPRECATED;
			LocalSlots[Index].StoredName = Output.StoredName;
			LocalSlots[Index].Tags = Output.Tags;
			LocalSlots[Index].DateAccessed = Output.DateAccessed;
			LocalSlots[Index].DateCreated = Output.DateCreated;
			LocalSlots[Index].DateModified = Output.DateModified;

			// compatibility to store save slot index, please remove when custom metadata available
			bool SlotIndexTagFound = false;
			for (int i = 0; i < Output.Tags.Num(); i++)
			{
				if (Output.Tags[i].StartsWith("SlotIndex="))
				{
					SlotIndexTagFound = true;
					break;
				}
			}

			if (!SlotIndexTagFound)
			{
				LocalSlots[Index].Tags.Insert(FString::Printf(TEXT("SlotIndex=%d"), Index), 0);
			}

			SaveScreenshotMetadata();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Upload to cloud storage. Checksum mismatch: %s == %s"), *LocalSlots[Index].Checksum, *Output.Checksum);
			SavedScreenshotList[Index]->State = ERROR_UPLOAD;
		}
	});

	auto OnProgress = FHttpRequestProgressDelegate::CreateLambda([](FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived) {
		UE_LOG(LogTemp, Log, TEXT("Upload Progress :%d"), BytesSent);
	});

	auto OnError = AccelByte::FErrorHandler::CreateLambda([&, Index](int32 ErrorCode, FString ErrorString) {
		UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Upload to cloud storage. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
		// If the index is not okay, don't handle the error at all.
		if (Index >= SavedScreenshotList.Num()) { return; }
		if (!SavedScreenshotList[Index].IsValid())
		{
			SavedScreenshotList[Index] = MakeShareable(new FScreenshotEntry{ Index + 1, "No Image", nullptr });
		}
		SavedScreenshotList[Index]->State = ERROR_UPLOAD;
		SavedScreenshotList[Index]->Title = TEXT("Upload failed");
		SavedScreenshotList[Index]->Image = nullptr;
	});

	if (SlotId.IsEmpty())
	{
		FRegistry::CloudStorage.CreateSlot(ImageData, "Screenshot.png", Tags, Label, "",
			OnSuccess, OnProgress, OnError);
	}
	else
	{
		FRegistry::CloudStorage.UpdateSlot(SlotId, ImageData, "Screenshot.png", Tags, Label, "",
			OnSuccess, OnProgress, OnError);
	}
}

TSharedPtr<FSlateDynamicImageBrush> SShooterScreenshot::CreateBrushFromFile(const FString& Path)
{
	return TSharedPtr<FSlateDynamicImageBrush>();
}

void SShooterScreenshot::SaveMetaData(const FString& FileName, const FDateTime&  DateTaken)
{
	//make sure it's updated
	LoadScreenshotMetadata();
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());
	const FString ScreenshotDir = GetScreenshotsDir();
	const FString SavePath = ScreenshotDir / GI->UserProfileInfo.UserId + ".json";
	const FString UserId = AccelByte::FRegistry::Credentials.GetUserId();
	const FString Namespace = AccelByte::FRegistry::Settings.Namespace;

	FAccelByteModelsSlot Slot;
	Slot.UserId = UserId;
	Slot.DateAccessed = DateTaken;
	Slot.DateCreated  = DateTaken;
	Slot.DateModified = DateTaken;
	Slot.Namespace = Namespace;
	Slot.MimeType = "image/png";
	Slot.Label = FileName;
	Slot.OriginalName = FileName;
	Slot.StoredName = FileName;
	TArray<uint8> data;
	const bool OpenSuccess = FFileHelper::LoadFileToArray(data, *FileName);
	if (!OpenSuccess)
	{
		UE_LOG(LogShooter, Error, TEXT("ERROR, failed to load the image file! %s"), *FileName);
		TWeakObjectPtr<UGeneralNotificationPopupUI> Msgbox = MakeWeakObjectPtr<UGeneralNotificationPopupUI>(CreateWidget<UGeneralNotificationPopupUI>(GI, *GI->GeneralNotificationPopupClass.Get()));
		Msgbox->Show(ENotificationType::ERROR_UNKNOWN, TEXT("Failed to load the image file!"));
		return;
	}
	Slot.Checksum = MD5HashArray(data);

	LocalSlots.Add(Slot);
	SaveScreenshotMetadata();
}

void SShooterScreenshot::BuildScreenshotItem()
{
	SavedScreenshotList.Empty();
	for (int i = 0; i < SAVE_SLOT_SIZE; i++)
	{
		SavedScreenshotList.Add(MakeShareable(new FScreenshotEntry{ i + 1, "No Image", nullptr }));
	}

	SavedScreenshotListWidget->RequestListRefresh();

	UpdateCurrentScreenshotList();
}

void SShooterScreenshot::EntrySelectionChanged(TSharedPtr<FScreenshotEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

void SShooterScreenshot::OnReleaseWidgetForListView(const TSharedRef<ITableRow>& TableRow)
{
	TSharedRef<SShooterScreenshotListItem> Row = StaticCastSharedRef<SShooterScreenshotListItem>(TableRow);
	ComboBoxGroup->ListComboBox.Remove(Row->SlotComboBox);
	Row->SlotComboBox.Reset();
}

TSharedRef<ITableRow> SShooterScreenshot::OnGenerateWidgetForListView(TSharedPtr<FScreenShotSelectedEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterScreenshotListItem, OwnerTable, PlayerOwner, Item)
		.ComboBoxGroup(ComboBoxGroup)
		.OnComboBoxSelectionChanged_Lambda([&](const FScreenshotSelectionEntry& InItem, ESelectInfo::Type SelectInfo)
		{
			int Index = InItem.CurrentSaveSlot - 1;
			int PreviousIndex = InItem.PreviousSaveSlot - 1;
			if (Index >= 0)
			{
				PreviousSelectedScreenshot[Index].Image = SavedScreenshotList[Index]->Image;
				SavedScreenshotList[Index]->Image = InItem.ScreenshotEntry.Image;
				SavedScreenshotList[Index]->Title = InItem.ScreenshotEntry.Title;
				//SavedScreenshotListWidget->RebuildList();

				FString Label = FString::Printf(TEXT("Screenshot-%s"), *FDateTime::Now().ToString());
				LocalSlots[Index].DateModified = FDateTime::UtcNow().ToUnixTimestamp();
				auto PixelData = FSlateBrushToPixelData(SavedScreenshotList[Index]->Image.Get());
				auto ByteData = GetCompressedImage(PixelData, EImageFormat::PNG);
				SaveLocalScreenshotImage(Index, ByteData);
				SaveToCloud(Index);
			}
			
			if (PreviousIndex >= 0)
			{
				SavedScreenshotList[PreviousIndex]->Image = PreviousSelectedScreenshot[PreviousIndex].Image;
				PreviousSelectedScreenshot[PreviousIndex].Image = nullptr;
				PreviousSelectedScreenshot[PreviousIndex].Title = "";
				//SavedScreenshotListWidget->RebuildList();
			}
			
		});
}

TSharedRef<ITableRow> SShooterScreenshot::OnGenerateWidgetForTileView(TSharedPtr<FScreenshotEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{	
	return SNew(SShooterScreenshotTileItem, OwnerTable, PlayerOwner, Item)
		.OnDeleteClick(this, &SShooterScreenshot::OnDeleteSlot)
		.OnResolveClick(this, &SShooterScreenshot::OnResolveSlot)
		.OnRetryClick(this, &SShooterScreenshot::SaveToCloud);
}

void SShooterScreenshot::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SShooterScreenshot::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(SavedScreenshotListWidget.ToSharedRef(), EFocusCause::SetDirectly);
}

void SShooterScreenshot::UpdateCurrentScreenshotList()
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(PlayerOwner->GetWorld(), 0));

	if (PlayerController)
	{
		const TArray<FDateTime>& Timestamps = PlayerController->GetScreenshotTimestamps();
		for (int i = ScreenshotList.Num(); i < PlayerController->GetScreenshotList().Num(); i++)
		{
			FString Label = FString::Printf(TEXT("Screenshot-%s"), *Timestamps[i].ToString());
			TSharedPtr<FScreenShotSelectedEntry> Item = MakeShareable(new FScreenShotSelectedEntry());
			Item->Entry = MakeShareable(new FScreenshotEntry{ i, Label, PlayerController->GetScreenshotList()[i] });
			ScreenshotList.Add(Item);
		}
		ScreenshotListWidget->RequestListRefresh();
	}
}

void SShooterScreenshot::ToggleScreenshotWindow()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayerOwner->GetWorld(), 0);
	if (bIsMenuUp)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
		bIsMenuUp = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
	else
	{
		GEngine->GameViewport->AddViewportWidgetContent(AsShared());
		bIsMenuUp = true;
		UpdateCurrentScreenshotList();
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	}
}

bool SShooterScreenshot::IsShowing()
{
	return bIsMenuUp;
}

FReply SShooterScreenshot::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const FKey Key = InKeyEvent.GetKey();
	if (!bMainMenuMode && (Key == EKeys::Escape || Key == EKeys::Virtual_Back || Key == EKeys::Gamepad_Special_Left))
	{
		ToggleScreenshotWindow();
		Result = FReply::Handled();
	}
	return Result;
}

TSharedPtr<FSlateDynamicImageBrush> SShooterScreenshot::CreateBrush(FString ContentType, FName ResourceName, const TArray<uint8>& ImageData)
{
	
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

	IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		TSharedPtr<FSlateDynamicImageBrush> Brush;

		Width = ImageWrapper->GetWidth();
		Height = ImageWrapper->GetHeight();

        TArray<uint8> RawData;

        if (ImageWrapper->GetRaw(RgbFormat, BitDepth, RawData))
        {
            DecodedImage = RawData;
            bSucceeded = true;
        }

		FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(),
			RawData
		);

		Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
		return Brush;
    }


	return nullptr;
}

void SShooterScreenshot::LoadSingleSlot(const FAccelByteModelsSlot& Slot, int32 SlotIndex)
{
	SavedScreenshotList[SlotIndex]->State = DOWNLOADING;
	auto OnSuccess = AccelByte::THandler<TArray<uint8>>::CreateLambda([&, Slot, SlotIndex](const TArray<uint8>& Result) {
        
        // do not use MoveTemp if source is Const &
        TArray64<uint8> Result64(Result);
		OnReceiveSlotImage(Result64, Slot, SlotIndex);
	});
	FRegistry::CloudStorage.GetSlot(Slot.SlotId, OnSuccess,
		AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
		UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Error Load Slot. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
	}));
}

void SShooterScreenshot::OnReceiveSlotImage(const TArray64<uint8>& Result64, const FAccelByteModelsSlot& Slot, int32 SlotIndex)
{
    UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Load slot %d success, updating brush"), SlotIndex);


    TArray<uint8> Result(Result64);
	auto ImageBrush = CreateBrush(TEXT("image/png"), FName(*Slot.Checksum), Result);

	// If the specified index doesn't exist, abort the operation.
	if (SlotIndex >= LocalSlots.Num()) { return; }

	if (LocalSlots[SlotIndex].Status_DEPRECATED == STATUS_PENDING_CONST_STRING)
	{
		SaveScreenshotCloudImage(SlotIndex, Result64);
		ConflictImages.Add(SlotIndex, ImageBrush);
		SavedScreenshotList[SlotIndex]->State = CONFLICT;
		return;
	}
	
	SavedScreenshotList[SlotIndex]->Image = ImageBrush;
	SavedScreenshotList[SlotIndex]->Title = !Slot.Label.IsEmpty() ? Slot.Label : TEXT("No Label");
	SavedScreenshotList[SlotIndex]->State = DONE;
	SavedScreenshotList[SlotIndex]->SlotID = Slot.SlotId;
	SavedScreenshotList[SlotIndex]->Checksum = Slot.Checksum;

	TArray64<uint8> Image64;
	if (LoadScreenshotImage(SlotIndex, Image64))
	{
        TArray<uint8> Image(MoveTemp(Image64));
		FString Checksum = MD5HashArray(Image);
		if (Checksum != Slot.Checksum)
		{
			SaveLocalScreenshotImage(SlotIndex, Result64);
		}
	}
	else
	{
		SaveLocalScreenshotImage(SlotIndex, Result64);
	}
}

void SShooterScreenshot::OnDeleteSlot(const FString& SlotID)
{
	UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Deleting slot:  %s"), *SlotID);

	FRegistry::CloudStorage.DeleteSlot(SlotID, 
		AccelByte::FVoidHandler::CreateLambda([&, SlotID]() {
			
		UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Deleting slot:  %s SUCCESS, updating the slot tile..."), *SlotID);
		for (int i = 0; i < SavedScreenshotList.Num(); i++)
		{
			if (SavedScreenshotList[i]->SlotID == SlotID)
			{
				// clear the image
				SavedScreenshotList[i]->Image = nullptr;
				SavedScreenshotList[i]->State = NONE;
				SavedScreenshotList[i]->Title = TEXT("No Image");
				SavedScreenshotList[i]->SlotID = TEXT("");

				LocalSlots[i].SlotId = TEXT("");
				LocalSlots[i].Label = TEXT("No Image");
				LocalSlots[i].Checksum = TEXT("");

				DeleteScreenshotImage(i);
				break;
			}
		}
		SaveScreenshotMetadata();
	}),
		AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
		UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Error Load Slot. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
	}));
}

void SShooterScreenshot::OnResolveSlot(int32 Index)
{
	const FAccelByteModelsSlot& LocalSlot = LocalSlots[Index];
	const FAccelByteModelsSlot& CloudSlot = ConflictSlots[Index];
	TSharedPtr<SShooterScreenshotResolver> Resolver;
	SAssignNew(Resolver, SShooterScreenshotResolver)
		.PlayerOwner(PlayerOwner)
		.OwnerWidget(OwnerWidget)
		.LocalEntry(MakeShareable(new FScreenshotResolveEntry(LocalSlot, SavedScreenshotList[Index]->Image)))
		.CloudEntry(MakeShareable(new FScreenshotResolveEntry(CloudSlot, ConflictImages[Index])))
		.OnResolve(SShooterScreenshotResolver::FOnResolve::CreateLambda([&, Index](EScreenshotResolveResult Result) {
			if (Result == RESULT_CLOUD)
			{
				LocalSlots[Index] = ConflictSlots[Index];
				SavedScreenshotList[Index]->Image = ConflictImages[Index];
				SavedScreenshotList[Index]->Title = !CloudSlot.Label.IsEmpty() ? CloudSlot.Label : TEXT("No Label");
				SavedScreenshotList[Index]->State = DONE;
				SavedScreenshotList[Index]->SlotID = CloudSlot.SlotId;
				SavedScreenshotList[Index]->Checksum = CloudSlot.Checksum;
				ResolveUseCloudScreenshot(Index);
				SaveScreenshotMetadata();
			}
			else if (Result == RESULT_LOCAL)
			{
				TArray64<uint8> ImageData64;
				LoadScreenshotImage(Index, ImageData64);
                TArray<uint8> ImageData(MoveTemp(ImageData64));

				LocalSlots[Index].Status_DEPRECATED = STATUS_PENDING_CONST_STRING;
				LocalSlots[Index].Checksum = MD5HashArray(ImageData);

				SaveScreenshotMetadata();

				LocalSlots[Index].DateModified = FDateTime::UtcNow().ToUnixTimestamp();

				SaveToCloud(Index);
			}
		}));
	Resolver->Show();
}

/// Called on back to main menu from match to ensure we have clean gallery
void SShooterScreenshot::RemoveErrorSlots()
{
	// Cleanup pending local slot
	for (auto& slot : LocalSlots)
	{
		if (slot.Status_DEPRECATED == STATUS_PENDING_CONST_STRING)
		{
			slot = FAccelByteModelsSlot();
		}
	}
	SaveScreenshotMetadata();

	for (int i = 0; i < SAVE_SLOT_SIZE; i++)
	{
		switch (SavedScreenshotList[i]->State)
		{
			case EScreenshotState::ERROR_UNKNOWN:
			case EScreenshotState::ERROR_UPLOAD:
				SavedScreenshotList[i]->Image = nullptr;
				SavedScreenshotList[i]->State = NONE;
				SavedScreenshotList[i]->Title = TEXT("No Image");
				SavedScreenshotList[i]->SlotID = TEXT("");
				DeleteScreenshotImage(i);
				break;
			default:
				break;
		}
	}
}

void SShooterScreenshot::RefreshFromCloud()
{
	if (!IsScreenshotMetadataExists())
	{
		for (int i = LocalSlots.Num(); i < SAVE_SLOT_SIZE; i++)
		{
			FAccelByteModelsSlot EmptySlot;
			EmptySlot.Tags.Add(FString::Printf(TEXT("SlotIndex=%d"), i));
			LocalSlots.Add(EmptySlot);
		}
	}
	else
	{
		LoadScreenshotMetadata();
	}

	for (int i = 0; i < LocalSlots.Num(); i++)
	{
		FAccelByteModelsSlot LocalSlot = LocalSlots[i];
		bool Pending = LocalSlot.Status_DEPRECATED == STATUS_PENDING_CONST_STRING;
		if (!LocalSlot.SlotId.IsEmpty() || Pending)
		{
			SavedScreenshotList[i]->Checksum = LocalSlot.Checksum;
			SavedScreenshotList[i]->SlotID = LocalSlot.SlotId;
			SavedScreenshotList[i]->Title = LocalSlot.Label;
			SavedScreenshotList[i]->State = Pending ? ERROR_UPLOAD : NONE;
			TArray64<uint8> ImageData64;
			if (LoadScreenshotImage(i, ImageData64))
			{
				FString Name;
				if (Name.IsEmpty())
				{
					Name = FString::Printf(TEXT("Screenshot-%d-%d"), i, FMath::Rand());
				}
				else
				{
					Name = FString::Printf(TEXT("%s-%d"), *LocalSlot.SlotId, FMath::Rand());
				}

                TArray<uint8> ImageData(MoveTemp(ImageData64));
				SavedScreenshotList[i]->Image = CreateBrush(TEXT("png"), FName(*Name), ImageData);
				if (SavedScreenshotList[i]->Image.IsValid())
				{
					SavedScreenshotList[i]->State = Pending ? ERROR_UPLOAD : NONE;
				}
			}
		}
	}

	FRegistry::CloudStorage.GetAllSlots(AccelByte::THandler<TArray<FAccelByteModelsSlot>>::CreateLambda([&](const TArray<FAccelByteModelsSlot>& Result) {
		for (int i = 0; i < Result.Num(); i++)
		{
			FAccelByteModelsSlot Slot = Result[i];
			UE_LOG(LogTemp, Log, TEXT("[Accelbyte] Response from cloud. slot result: %s, Original:%s"), *Slot.SlotId, *Slot.OriginalName);
			if (i < SAVE_SLOT_SIZE)
			{
				int SlotIndex = -1;

				// find SlotIndex by tags
				FString SlotIndexStr = "SlotIndex=";
				for (int j = 0; j < Slot.Tags.Num(); j++)
				{
					if (Slot.Tags[j].StartsWith(SlotIndexStr))
					{
						FString Num = Slot.Tags[j].RightChop(SlotIndexStr.Len());
						if (Num.IsNumeric())
						{
							SlotIndex = FCString::Atoi(*Num);
						}
						break;
					}
				}

				UE_LOG(LogTemp, Log, TEXT("SLOT INDEX %d"), SlotIndex);
				// SlotIndex tag not found, find by SlotId
				if (SlotIndex == -1)
				{
					for (int j = 0; j < LocalSlots.Num(); j++)
					{
						const FAccelByteModelsSlot& LocalSlot = LocalSlots[j];
						UE_LOG(LogTemp, Log, TEXT("SLOT INDEX %s == %s"), *LocalSlot.SlotId, *Slot.SlotId);
						// load to existing slot
						if (LocalSlot.SlotId == Slot.SlotId)
						{
							SlotIndex = j;
							break;
						}
					}
				}

				if (SlotIndex == -1)
				{
					for (int j = 0; j < SavedScreenshotList.Num(); j++)
					{
						TSharedPtr<FScreenshotEntry> SavedSlot = SavedScreenshotList[j];
						// load to empty slot
						if (SavedSlot->SlotID.IsEmpty() && SavedSlot->State == NONE)
						{
							LocalSlots[j] = Result[i];
							LoadSingleSlot(Slot, j);
							break;
						}
					}
				}
				else
				{
					if (!LocalSlots[SlotIndex].SlotId.IsEmpty() && LocalSlots[SlotIndex].Checksum != Slot.Checksum
						&& LocalSlots[SlotIndex].Status_DEPRECATED == STATUS_PENDING_CONST_STRING
						)
					{
						ConflictSlots.Add(SlotIndex, Slot);
					}
					else
					{
						LocalSlots[SlotIndex] = Slot;
					}

					TSharedPtr<FScreenshotEntry> SavedSlot = SavedScreenshotList[SlotIndex];
					if (!IsDownloadedSlotValid(SlotIndex))
					{
						LoadSingleSlot(Slot, SlotIndex);
					}
					else
					{
						TArray64<uint8> Result64;
						LoadScreenshotImage(SlotIndex, Result64);
						//load the file, convert it to TArray from TArray64, then make the brush from the image (function only takes TArray array type)
						TArray<uint8> Result(MoveTemp(Result64));
						auto ImageBrush = CreateBrush(TEXT("image/png"), FName(*Slot.Checksum), Result);
						//mark it as done
						SavedScreenshotList[i]->State = DONE;
						SavedScreenshotList[i]->Image = ImageBrush;
					}
				}
			}
		}

		for (int i = 0; i < LocalSlots.Num(); i++)
		{
			if (i >= Result.Num())
			{
				SavedScreenshotList[i]->SlotID = LocalSlots[i].SlotId = "";
				SavedScreenshotList[i]->Checksum = LocalSlots[i].Checksum = "";
				SavedScreenshotList[i]->Title = LocalSlots[i].Label = "";
				SavedScreenshotList[i]->State = NONE;
				SavedScreenshotList[i]->Image = nullptr;
				LocalSlots[i].Tags.Empty();
				LocalSlots[i].Tags.Add(FString::Printf(TEXT("SlotIndex=%d"), i));
			}
			else
			{
				SavedScreenshotList[i]->SlotID = LocalSlots[i].SlotId;
				SavedScreenshotList[i]->Checksum = LocalSlots[i].Checksum;
				SavedScreenshotList[i]->Title = LocalSlots[i].Label;
			}
		}

		SaveScreenshotMetadata();

		SavedScreenshotListWidget->RequestListRefresh();
	}),
		AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
		UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] FRegistry::CloudStorage.GetAllSlot Error. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
	}));
}
