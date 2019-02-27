// Copyright (c) 2018-2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SShooterScreenshotPreview.h"
#include "ShooterStyle.h"
#include "GalleryStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "SShooterScreenshotPreview.h"

FSlateColorBrush SShooterScreenshotPreview_BackgroundImage(FLinearColor(0.5f, 0.5f, 0.5f));

void SShooterScreenshotPreview::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	Image = InArgs._Image;

	GalleryStyle = &FShooterStyle::Get().GetWidgetStyle<FGalleryStyle>("DefaultGalleryMenuStyle");

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
			.Image(&GalleryStyle->PreviewImageBackground)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Right)
		[
			SNew(SBox)
			.WidthOverride(48)
			.HeightOverride(48)
			[
				SNew(SButton) // close button
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
					GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
					return FReply::Handled();
				}))
				.ButtonStyle(&GalleryStyle->ClosePreviewButtonStyle)
			]
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(FMargin(32))
		[
			SNew(SScaleBox)
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Center)
			.Stretch(EStretch::ScaleToFit)
			[
				SNew(SImage)
				.Image(Image)
			]
		]
	];

}

void SShooterScreenshotPreview::Show()
{
	GEngine->GameViewport->AddViewportWidgetContent(AsShared());
}

