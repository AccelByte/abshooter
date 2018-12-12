#include "SShooterScreenshotEdit.h"
#include "ShooterStyle.h"
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

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&SShooterScreenshotEdit_BackgroundImage)
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
				.Image(FShooterStyle::Get().GetBrush("ShooterGame.CornerBorder"))
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
						.Text(FText::FromString("Edit Caption"))
					]
					+ SVerticalBox::Slot()
					[
						SAssignNew(TextTitle, SEditableText)
						.Text(FText::FromString(InArgs._Entry->Title))
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
						[
							SNew(STextBlock)
							.Text(FText::FromString("CANCEL"))
						]
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
						[
							SNew(STextBlock)
							.Text(FText::FromString("SAVE"))
						]
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

