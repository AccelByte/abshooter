#include "ShooterGame.h"
#include "SShooterInventoryItem.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SShooterInventoryItem"

/** item type conversion*/
FText GetItemTypeAsText(EItemType EnumValue) {
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemType"), true);
    if (!EnumPtr) return FText::FromString("Invalid");
    return EnumPtr->GetDisplayNameText((int64)EnumValue);
}

void SShooterInventoryItem::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FInventoryEntry> InItem)
{
    Item = InItem;
    PlayerOwner = InPlayerOwner;

    STableRow< TSharedPtr<FInventoryEntry> >::Construct(STableRow::FArguments().ShowSelection(false), InOwnerTable);

    if (Item.IsValid()) 
    {
        InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
        TSharedPtr<FInventoryEntry> item = Item.Pin();

        if (item->ImageURL.StartsWith("http")) 
        {
            // image placeholder
            ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/SoundCue_SpeakerIcon.png", FVector2D(144, 144)));

            // start download avatar
            TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
            ThumbRequest->SetVerb("GET");
            ThumbRequest->SetURL(item->ImageURL);
            ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SShooterInventoryItem::OnThumbImageReceived);
            ThumbRequest->ProcessRequest();
        }
        else
        {
            ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / item->ImageURL, FVector2D(144, 144)));
        }

        TSharedPtr<SVerticalBox> BottomVerticalBox;

        ChildSlot
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            SNew(SOverlay)
            + SOverlay::Slot()
            .VAlign(VAlign_Fill)
            .HAlign(HAlign_Fill) // Background
            [
                SNew(SImage)
                .Image(&InventoryStyle->BackgroundBrush)
                .ColorAndOpacity(this, &SShooterInventoryItem::GetButtonBgColor)
            ]
            + SOverlay::Slot()
            .VAlign(VAlign_Fill)
            .HAlign(HAlign_Fill)
            .Padding(10.0f)
            [
                SAssignNew(BottomVerticalBox, SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                .VAlign(VAlign_Fill)
                .HAlign(HAlign_Fill)
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Fill)
                    .HAlign(HAlign_Fill) // Top
                    .AutoWidth()
                    [
                        SNew(SOverlay)
                        + SOverlay::Slot()
                        .VAlign(VAlign_Fill)
                        .HAlign(HAlign_Fill) // Type background
                        [
                            SNew(SImage)
                            .Image(&InventoryStyle->TypeBackgroundBrush)
                        ]
                        + SOverlay::Slot()
                        .VAlign(VAlign_Center)
                        .HAlign(HAlign_Left)
                        [
                            SNew(STextBlock)
                            .Margin(FMargin(5, 0, 0, 0))
                            .TextStyle(&InventoryStyle->TypeTextStyle)
                            .Text(GetItemTypeAsText(item->Type))
                        ]
                    ]
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Center)
                    .HAlign(HAlign_Right) // Amount
                    .FillWidth(1)
                    [
                        SNew(STextBlock)
                        .TextStyle(&InventoryStyle->AmountTextStyle)
                        .Text(FText::AsNumber(item->Amount))
                        .Visibility(item->Consumable ? EVisibility::Visible : EVisibility::Collapsed)
                    ]
                ]
                + SVerticalBox::Slot()
                .VAlign(VAlign_Fill)
                .HAlign(HAlign_Fill)
                .FillHeight(1) // Content image
                [
                    SNew(SScaleBox)
                    .VAlign(VAlign_Fill)
                    .HAlign(HAlign_Center)
                    .Stretch(EStretch::ScaleToFit)
                    [
                        SNew(SImage)
                        .Image(this, &SShooterInventoryItem::GetImage)
                    ]
                ]
                + SVerticalBox::Slot()
                .VAlign(VAlign_Center)
                .HAlign(HAlign_Center) // Name
                .AutoHeight()
                [
                    SNew(STextBlock)
                    .TextStyle(&InventoryStyle->NameTextStyle)
                    .Text(FText::FromString(item->Name))
                ]
                + SVerticalBox::Slot()
                .VAlign(VAlign_Fill)
                .HAlign(HAlign_Fill) // Price
                .AutoHeight()
                [
                    GetBottomWidget(item.Get())
                ]
            ]
        ];
    }
}

TSharedRef<SWidget> SShooterInventoryItem::GetBottomWidget(const FInventoryEntry* item) const
{
    if (!item->Consumable && item->Owned)
    {
        return SNew(STextBlock)
            .TextStyle(&InventoryStyle->OwnedTextStyle)
            .Text(FText::FromString("YOU ALREADY OWN"));
    }
    else
    {
        return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        .AutoWidth()
        [
            SNew(SImage)
            .Image(&InventoryStyle->CoinImage)
        ]
        + SHorizontalBox::Slot()
        .VAlign(VAlign_Center)
        .HAlign(HAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .Margin(FMargin(5, 0))
            .TextStyle(&InventoryStyle->PriceTextStyle)
            .Text(FText::AsNumber(item->Price))
        ];
    }
}

const FSlateBrush* SShooterInventoryItem::GetImage() const
{
    return ImageBrush.Get();
}

void SShooterInventoryItem::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
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
            ImageBrush = CreateBrush(FName(*Request->GetURL()), ImageData, ImageFormat);
            ImageBrush->ImageSize = { 50, 50 };
        }

    }
}

TSharedPtr<FSlateDynamicImageBrush> SShooterInventoryItem::CreateBrush(FName ResourceName, TArray<uint8> ImageData, const EImageFormat InFormat)
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
        if (InFormat == EImageFormat::PNG)
        {
            RGBFormat = ERGBFormat::BGRA;
        }

        if (ImageWrapper->GetRaw(RGBFormat, 8, RawData))
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

FSlateColor SShooterInventoryItem::GetButtonBgColor() const
{
    const float MinAlpha = 0.1f;
    const float MaxAlpha = 1.f;
    const float AnimSpeedModifier = 1.5f;

    float AnimPercent = 0.f;
    ULocalPlayer* const Player = PlayerOwner.Get();
    if (Player)
    {
        // @fixme, need a world get delta time?
        UWorld* const World = Player->GetWorld();
        if (World)
        {
            const float GameTime = World->GetRealTimeSeconds();
            AnimPercent = FMath::Abs(FMath::Sin(GameTime*AnimSpeedModifier));
        }
    }

    const float BgAlpha = IsSelected() ? FMath::Lerp(MinAlpha, MaxAlpha, AnimPercent) : 0.2f;
    return FLinearColor(1.f, 1.f, 1.f, BgAlpha);
}