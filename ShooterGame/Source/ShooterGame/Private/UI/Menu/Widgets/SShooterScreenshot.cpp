
#include "ShooterGame.h"
#include "SShooterScreenshot.h"
#include "SShooterScreenshotPreview.h"
#include "SShooterScreenshotEdit.h"
#include "SShooterScreenshotResolver.h"
#include "ShooterStyle.h"
#include "ShooterUIHelpers.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteError.h"
#include "Api/AccelByteCloudStorageApi.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "Runtime/ImageWriteQueue/Public/ImagePixelData.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Engine/Public/ImageUtils.h"
#include "Models/ScreenshotSave.h"

using namespace AccelByte::Api;
const int SAVE_SLOT_SIZE = 4;
const FString STATUS_PENDING = "Pending";

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
	TArray<FColor>& Color = PixelData->Pixels;
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
			TArray<uint8> Array = ImageWrapper->GetCompressed();
			return FBase64::Encode(Array);
		}
	}
	return "";
}

TArray<uint8> GetCompressedImage(TSharedPtr<TImagePixelData<FColor>> PixelData, EImageFormat InFormat)
{
	IImageWrapperModule* ImageWrapperModule = FModuleManager::GetModulePtr<IImageWrapperModule>("ImageWrapper");
	if (!ensure(ImageWrapperModule))
	{
		return TArray<uint8>();
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

	return TArray<uint8>();
}

TArray<uint8> GetCompressedAndScaledImage(TSharedPtr<TImagePixelData<FColor>> PixelData, EImageFormat InFormat)
{
    IImageWrapperModule* ImageWrapperModule = FModuleManager::GetModulePtr<IImageWrapperModule>("ImageWrapper");
    if (!ensure(ImageWrapperModule))
    {
        return TArray<uint8>();
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

    return TArray<uint8>();
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

		STableRow< TSharedPtr<FScreenshotEntry> >::Construct(STableRow::FArguments().ShowSelection(false) , InOwnerTable);

		ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(20)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&BorderBrush)
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
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(FMargin(0, 0, 10, 0))
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString::Printf(TEXT("SLOTs %0d"), InItem->SlotNumber)))
						.ColorAndOpacity(FLinearColor(0, 1, 1))
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1)
					[
						SAssignNew(TextTitle, STextBlock)
						.Text(this, &SShooterScreenshotTileItem::GetTitle)
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
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							SAssignNew(this->ScreenshotPreviewWidget, SShooterScreenshotPreview)
								.Image(Item.Pin()->Image.Get());
							this->ScreenshotPreviewWidget->Show();
							return FReply::Handled();
						}))
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(&ButtonBackgrounBrush)
							]
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(FShooterStyle::Get().GetBrush("ShooterGame.ZoomOut"))
							]
						]
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
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							SAssignNew(this->ScreenshotEditWidget, SShooterScreenshotEdit)
								.Entry(Item.Pin().Get())
								.OnSave(SShooterScreenshotEdit::FOnSave::CreateLambda([&]() {
									TextTitle->SetText(FText::FromString(Item.Pin()->Title));
								}));
							this->ScreenshotEditWidget->Show();
							return FReply::Handled();
						}))
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(&ButtonBackgrounBrush)
							]
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(FShooterStyle::Get().GetBrush("ShooterGame.Edit"))
							]
						]
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
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							OnDeleteClick.ExecuteIfBound(Item.Pin()->SlotID);
							return FReply::Handled();
						}))
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(&ButtonBackgrounBrush)
							]
							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(FShooterStyle::Get().GetBrush("ShooterGame.Close"))
							]
						]
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
					SNew(SButton)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Resolve"))
					]
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
					SNew(SButton)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Retry"))
					]
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
		return !Item.Pin()->Image.IsValid() ? FShooterStyle::Get().GetBrush("ShooterGame.Image") : Item.Pin()->Image.Get();
    }

	const FSlateBrush* GetCloudImage() const
	{
		switch (Item.Pin()->State)
		{
		case DONE:
			return FShooterStyle::Get().GetBrush("ShooterGame.CloudDone");
		case DOWNLOADING:
			return FShooterStyle::Get().GetBrush("ShooterGame.CloudDownload");
		case UPLOADING:
			return FShooterStyle::Get().GetBrush("ShooterGame.CloudUpload");
		case ERROR:
		case ERROR_UPLOAD:
			return FShooterStyle::Get().GetBrush("ShooterGame.CloudOff");
		case CONFLICT:
			return FShooterStyle::Get().GetBrush("ShooterGame.SyncProblem");
		}

		return FShooterStyle::Get().GetBrush("ShooterGame.CloudOff");
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
const FSlateColorBrush SShooterScreenshotTileItem::SelectedBrush{ FLinearColor(0, 1, 1, 0.6) };
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

	const int32 TileWidth = 288;
	const int32 TileHeight = 200;
	const int32 TileColumn = 2;
	const int32 TileRow = 2;

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&BackgroundImage)
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
				.WidthOverride(400)
				.HeightOverride(TileHeight * TileRow + 4)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SImage)
						.Image(&GreyBackgroundBrush)
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
						SNew(SImage)
						.Image(&BlackBackgroundBrush)
					]
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

FString SShooterScreenshot::GetScreenshotsDir()
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

FString SShooterScreenshot::GetUserScreenshotsDir()
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

void SShooterScreenshot::SaveLocalScreenshotImage(int32 Index, const TArray<uint8>& Binary)
{
	FString ScreenshotsDir = GetUserScreenshotsDir();

	if (ScreenshotsDir.IsEmpty())
	{
		return;
	}

	FString ImageName = ScreenshotsDir / "Screenshot-" + FString::FromInt(Index) + ".png";

	FFileHelper::SaveArrayToFile(Binary, *ImageName);
}

void SShooterScreenshot::SaveScreenshotCloudImage(int32 Index, const TArray<uint8>& Binary)
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

bool SShooterScreenshot::LoadScreenshotImage(int32 Index, TArray<uint8>& Result)
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

void SShooterScreenshot::SaveToCloud(int32 Index)
{
	TArray<uint8> ImageData;
	LoadScreenshotImage(Index, ImageData);

	FString Label = SavedScreenshotList[Index]->Title;
	FString Tags = FString::Printf(TEXT("SaveIndex=%d"), Index);
	FString SlotId = LocalSlots[Index].SlotId;

	LocalSlots[Index].Status = STATUS_PENDING;
	LocalSlots[Index].Checksum = MD5HashArray(ImageData);

	SaveScreenshotMetadata();

	SavedScreenshotList[Index]->State = UPLOADING;

	auto OnSuccess = AccelByte::Api::CloudStorage::FCreateSlotSuccess::CreateLambda([&, Index](const FAccelByteModelsSlot& Output) {
		if (Output.Checksum == LocalSlots[Index].Checksum)
		{
			UE_LOG(LogTemp, Log, TEXT("File successfully saved, Index: %d, SlotID :%s"), Index, *Output.SlotId);
			SavedScreenshotList[Index]->State = DONE;
			SavedScreenshotList[Index]->Title = Output.Label;

			LocalSlots[Index].UserId = Output.UserId;
			LocalSlots[Index].SlotId = Output.SlotId;
			LocalSlots[Index].Label = Output.Label;
			LocalSlots[Index].MimeType = Output.MimeType;
			LocalSlots[Index].NamespaceId = Output.NamespaceId;
			LocalSlots[Index].OriginalName = Output.OriginalName;
			LocalSlots[Index].SlotId = Output.SlotId;
			LocalSlots[Index].Status = Output.Status;
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
		SavedScreenshotList[Index]->State = ERROR_UPLOAD;
		SavedScreenshotList[Index]->Title = TEXT("Upload failed");
		SavedScreenshotList[Index]->Image = nullptr;
	});

	if (SlotId.IsEmpty())
	{
		AccelByte::Api::CloudStorage::CreateSlot(ImageData, "Screenshot.png", Tags, Label,
			OnSuccess, OnProgress, OnError);
	}
	else
	{
		AccelByte::Api::CloudStorage::UpdateSlot(SlotId, ImageData, "Screenshot.png", Tags, Label,
			OnSuccess, OnProgress, OnError);
	}
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
				LocalSlots[Index].DateModified = FDateTime::UtcNow();
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
		for (int i = ScreenshotList.Num(); i < PlayerController->GetScreenshotList().Num(); i++)
		{
			TSharedPtr<FScreenShotSelectedEntry> Item = MakeShareable(new FScreenShotSelectedEntry());
			Item->Entry = MakeShareable(new FScreenshotEntry{ i, FString::Printf(TEXT("Screenshot %d"), i + 1), PlayerController->GetScreenshotList()[i] });
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

void SShooterScreenshot::LoadSingleSlot(FAccelByteModelsSlot Slot, int32 SlotIndex)
{
    SavedScreenshotList[SlotIndex]->State = DOWNLOADING;
    auto OnSuccess = AccelByte::Api::CloudStorage::FGetSlotSuccess::CreateSP(this, &SShooterScreenshot::OnReceiveSlotImage, Slot, SlotIndex);
    AccelByte::Api::CloudStorage::GetSlot(Slot.SlotId, OnSuccess,
        AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Error Load Slot. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
    }));
}

void SShooterScreenshot::OnReceiveSlotImage(const TArray<uint8>& Result, FAccelByteModelsSlot Slot, int32 SlotIndex)
{
    UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Load slot %d success, updating brush"), SlotIndex);
	auto ImageBrush = CreateBrush(TEXT("image/png"), FName(*Slot.Checksum), Result);

	if (LocalSlots[SlotIndex].Status == STATUS_PENDING)
	{
		SaveScreenshotCloudImage(SlotIndex, Result);
		ConflictImages.Add(SlotIndex, ImageBrush);
		SavedScreenshotList[SlotIndex]->State = CONFLICT;
		return;
	}
	
	SavedScreenshotList[SlotIndex]->Image = ImageBrush;
    SavedScreenshotList[SlotIndex]->Title = !Slot.Label.IsEmpty() ? Slot.Label : TEXT("No Label");
    SavedScreenshotList[SlotIndex]->State = DONE;
    SavedScreenshotList[SlotIndex]->SlotID = Slot.SlotId;
	SavedScreenshotList[SlotIndex]->Checksum = Slot.Checksum;

	TArray<uint8> Image;
	if (LoadScreenshotImage(SlotIndex, Image))
	{
		FString Checksum = MD5HashArray(Image);
		if (Checksum != Slot.Checksum)
		{
			SaveLocalScreenshotImage(SlotIndex, Result);
		}
	}
	else
	{
		SaveLocalScreenshotImage(SlotIndex, Result);
	}
}

void SShooterScreenshot::OnDeleteSlot(const FString& SlotID)
{
    UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Deleting slot:  %s"), *SlotID);

    AccelByte::Api::CloudStorage::DeleteSlot(SlotID, 
        AccelByte::Api::CloudStorage::FDeleteSlotSuccess::CreateLambda([&, SlotID]() {
            
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
				TArray<uint8> ImageData;
				LoadScreenshotImage(Index, ImageData);

				LocalSlots[Index].Status = STATUS_PENDING;
				LocalSlots[Index].Checksum = MD5HashArray(ImageData);

				SaveScreenshotMetadata();

				LocalSlots[Index].DateModified = FDateTime::UtcNow();

				SaveToCloud(Index);
			}
		}));
	Resolver->Show();
}

void SShooterScreenshot::RefreshFromCloud()
{
	if (!IsScreenshotMetadataExists())
	{
		for (int i = 0; i < SAVE_SLOT_SIZE; i++)
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
		if (!LocalSlot.SlotId.IsEmpty())
		{
			SavedScreenshotList[i]->Checksum = LocalSlot.Checksum;
			SavedScreenshotList[i]->SlotID = LocalSlot.SlotId;
			SavedScreenshotList[i]->Title = LocalSlot.Label;
			SavedScreenshotList[i]->State = NONE;
			TArray<uint8> ImageData;
			if (LoadScreenshotImage(i, ImageData))
			{
				SavedScreenshotList[i]->Image = CreateBrush(TEXT("png"), FName(*LocalSlot.SlotId), ImageData);
				if (SavedScreenshotList[i]->Image.IsValid())
				{
					SavedScreenshotList[i]->State = NONE;
				}
			}
		}
	}

    AccelByte::Api::CloudStorage::GetAllSlots(AccelByte::Api::CloudStorage::FGetAllSlotsSuccess::CreateLambda([&](const TArray<FAccelByteModelsSlot>& Result) {
        for (int i = 0; i < Result.Num(); i++)
        {
            FAccelByteModelsSlot Slot = Result[i];
            UE_LOG(LogTemp, Log, TEXT("[Accelbyte] Response from cloud. slot result: %s, Original:%s"), *Slot.SlotId, *Slot.OriginalName);
            if (i < 4)
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
							LocalSlots[j] = Result[j];
							LoadSingleSlot(Slot, j);
							break;
						}
					}
				}
				else
				{
					if (!LocalSlots[SlotIndex].SlotId.IsEmpty() && LocalSlots[SlotIndex].Checksum != Slot.Checksum
						&& LocalSlots[SlotIndex].Status == STATUS_PENDING
						)
					{
						ConflictSlots.Add(SlotIndex, Slot);
					}
					else
					{
						LocalSlots[SlotIndex] = Slot;
					}

					TSharedPtr<FScreenshotEntry> SavedSlot = SavedScreenshotList[SlotIndex];
					if (SavedSlot->Checksum != Slot.Checksum)
					{
						LoadSingleSlot(Slot, SlotIndex);
					}
				}
            }
        }

		SaveScreenshotMetadata();
    }),
        AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, FString ErrorString) {
        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] AccelByte::Api::CloudStorage::GetAllSlot Error. ErrorCode :%d. ErrorMessage:%s"), ErrorCode, *ErrorString);
    }));
}
