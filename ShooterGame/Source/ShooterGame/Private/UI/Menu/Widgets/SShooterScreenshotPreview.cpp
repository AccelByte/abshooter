#include "SShooterScreenshotPreview.h"
#include "ShooterStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "SShooterScreenshotPreview.h"

FSlateColorBrush SShooterScreenshotPreview_BackgroundImage(FLinearColor(0.5f, 0.5f, 0.5f));

void SShooterScreenshotPreview::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	Image = InArgs._Image;

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
			.Image(&SShooterScreenshotPreview_BackgroundImage)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Right)
		[
			SNew(SBox)
			.WidthOverride(32)
			.HeightOverride(32)
			[
				SNew(SButton) // close button
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
					GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
					return FReply::Handled();
				}))
				[
					SNew(SImage)
					.Image(FShooterStyle::Get().GetBrush("ShooterGame.Image"))
				]
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

