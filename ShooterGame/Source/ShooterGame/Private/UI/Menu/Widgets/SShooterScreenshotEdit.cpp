// Copyright (c) 2018-2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SShooterScreenshotEdit.h"
#include "ShooterStyle.h"
#include "GalleryStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "SShooterScreenshotEdit.h"
#include "UI/Menu/Widgets/SShooterScreenshot.h"

FSlateColorBrush SShooterScreenshotEdit_BackgroundImage(FLinearColor(0, 0, 0, 0.9f));

void SShooterScreenshotEdit::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	Entry = InArgs._Entry;
	OnSave = InArgs._OnSave;

	GalleryStyle = &FShooterStyle::Get().GetWidgetStyle<FGalleryStyle>("DefaultGalleryMenuStyle");

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&GalleryStyle->EditCaptionBackground)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&GalleryStyle->EditCaptionInnerBackground)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(10))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.Text(FText::FromString("EDIT CAPTION"))
						.TextStyle(&GalleryStyle->EditCaptionTextStyle)
					]
					+ SVerticalBox::Slot()
					[
						SNew(SOverlay)
						+SOverlay::Slot()
						[
							SNew(SImage)
							.Image(&GalleryStyle->EditCaptionInputFieldBackground)
						]
						+SOverlay::Slot()
						[
							SAssignNew(TextTitle, SEditableText)
							.Text(FText::FromString(InArgs._Entry->Title))
							.Style(&GalleryStyle->EditCaptionInputFieldStyle)
						]
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
							return FReply::Handled();
						}))
						.ButtonStyle(&GalleryStyle->EditCaptionCloseButtonStyle)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
							Entry->Title = TextTitle->GetText().ToString();
							OnSave.ExecuteIfBound();
							GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
							return FReply::Handled();
						}))
						.ButtonStyle(&GalleryStyle->EditCaptionSaveButtonStyle)
					]
				]
			]
		]
	];

}

void SShooterScreenshotEdit::Show()
{
	GEngine->GameViewport->AddViewportWidgetContent(AsShared());
}

