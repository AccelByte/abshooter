
#include "ShooterGame.h"
#include "SShooterScreenshot.h"
#include "SShooterScreenshotPreview.h"
#include "SShooterScreenshotEdit.h"
#include "ShooterStyle.h"
#include "ShooterUIHelpers.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteError.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "Runtime/ImageWriteQueue/Public/ImagePixelData.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Engine/Public/ImageUtils.h"

using namespace AccelByte::Api;
const int SAVE_SLOT_SIZE = 4;

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

TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FName ResourceName, TArray<uint8> ImageData, const EImageFormat InFormat)
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

		if (ImageWrapper->GetRaw(InFormat == EImageFormat::PNG ? ERGBFormat::BGRA : ERGBFormat::RGBA, 8, RawData))
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
						.Image(InItem->Entry->Image == nullptr ? FShooterStyle::Get().GetBrush("ShooterGame.Image") : InItem->Entry->Image)
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
	DECLARE_DELEGATE(FOnDeleteClick)

	SLATE_BEGIN_ARGS(SShooterScreenshotTileItem) {}
	SLATE_EVENT(FOnDeleteClick, OnDeleteClick)
	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FScreenshotEntry> InItem)
	{
		Item = InItem;
		PlayerOwner = InPlayerOwner;
		OnDeleteClick = InArgs._OnDeleteClick;

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
					.VAlign(VAlign_Fill)
					[
						SNew(SSafeZone)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.Padding(10.0f)
						.IsTitleSafe(true)
						[
							SAssignNew(LoadingBar, SThrobber)
						]
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SScaleBox)
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Center)
						.Stretch(EStretch::ScaleToFit)
						[
							SNew(SImage)
							.Image(InItem->Image == nullptr ? FShooterStyle::Get().GetBrush("ShooterGame.Image") : InItem->Image)
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
						.Text(FText::FromString(InItem->Title))
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
								.Image(Item.Pin()->Image);
							this->ScreenshotPreviewWidget->Show();
							return FReply::Handled();
						}))
						[
							SNew(SImage)
							.Image(&ButtonBackgrounBrush)
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
							SNew(SImage)
							.Image(&ButtonBackgrounBrush)
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
							//TEST
							TSharedPtr<TImagePixelData<FColor>> PixelData = FSlateBrushToPixelData(Item.Pin()->Image);
							if (PixelData.IsValid())
							{
								GetBase64Thumbnail(PixelData, EImageFormat::JPEG);
							}
							OnDeleteClick.ExecuteIfBound();
							return FReply::Handled();
						}))
						[
							SNew(SImage)
							.Image(&ButtonBackgrounBrush)
						]
					]
				]
			]
		];
	}

	void SetLoadingBarVisible(bool Visible)
	{
		if (Visible)
		{
			LoadingBar->SetVisibility(EVisibility::Visible);
		}
		else
		{
			LoadingBar->SetVisibility(EVisibility::Collapsed);
		}
	}

	EVisibility GetSelectedVisibility() const {
		return IsSelected() && Item.IsValid() && Item.Pin()->Image != nullptr ? EVisibility::Visible : EVisibility::Collapsed;
	}

private:
	FSlateColorBrush BorderBrush{ FLinearColor(0, 0, 0) };
	FSlateColorBrush ImageBrush{ FLinearColor(1, 1, 1) };
	FSlateColorBrush SelectedBrush{ FLinearColor(0, 1, 1, 0.6) };
	FSlateColorBrush ButtonBackgrounBrush{ FLinearColor(0.5, 0.5, 0.5) };

	TSharedPtr< class SShooterScreenshotPreview > ScreenshotPreviewWidget;
	TSharedPtr< class SShooterScreenshotEdit > ScreenshotEditWidget;
	TSharedPtr<SWidget> SelectedWidget;
	FTableRowStyle Style;

	TSharedPtr<SThrobber> LoadingBar;

	TSharedPtr<STextBlock> TextTitle;

	FOnDeleteClick OnDeleteClick;

	/** pointer to Item */
	TWeakPtr<FScreenshotEntry> Item;

	/** pointer to our owner PC */
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
};

SShooterScreenshot::SShooterScreenshot()
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

void SShooterScreenshot::BuildScreenshotItem()
{
	Brushes.Add(MakeShareable(new FSlateColorBrush(FLinearColor(1, 0, 0))));
	Brushes.Add(MakeShareable(new FSlateColorBrush(FLinearColor(1, 1, 0))));
	Brushes.Add(MakeShareable(new FSlateColorBrush(FLinearColor(1, 0, 1))));

	// TODO load screenshot from cloudstorage

	//dummy data
	SavedScreenshotList.Empty();
	SavedScreenshotList.Add(MakeShareable(new FScreenshotEntry{ 1, "Title aaaa", Brushes[0].Get() }));
	SavedScreenshotList.Add(MakeShareable(new FScreenshotEntry{ 2, "bbbbbbbb", Brushes[1].Get() }));
	SavedScreenshotList.Add(MakeShareable(new FScreenshotEntry{ 3, "Title cccc", Brushes[2].Get() }));
	SavedScreenshotList.Add(MakeShareable(new FScreenshotEntry{ 4, "ddddddd", nullptr }));
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
				SavedScreenshotListWidget->RebuildList();
			}
			
			if (PreviousIndex >= 0)
			{
				SavedScreenshotList[PreviousIndex]->Image = PreviousSelectedScreenshot[PreviousIndex].Image;
				PreviousSelectedScreenshot[PreviousIndex].Image = nullptr;
				PreviousSelectedScreenshot[PreviousIndex].Title = "";
				SavedScreenshotListWidget->RebuildList();
			}
			//TODO upload to cloudstorage
			//TODO show loading bar
			
		});
}

TSharedRef<ITableRow> SShooterScreenshot::OnGenerateWidgetForTileView(TSharedPtr<FScreenshotEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{	
	return SNew(SShooterScreenshotTileItem, OwnerTable, PlayerOwner, Item);
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
			Item->Entry = MakeShareable(new FScreenshotEntry{ i, FString::Printf(TEXT("Screenshot %d"), i + 1), PlayerController->GetScreenshotList()[i].Get() });
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
	if (Key == EKeys::Escape || Key == EKeys::Virtual_Back || Key == EKeys::Gamepad_Special_Left)
	{
		ToggleScreenshotWindow();
		Result = FReply::Handled();
	}
	return Result;
}
