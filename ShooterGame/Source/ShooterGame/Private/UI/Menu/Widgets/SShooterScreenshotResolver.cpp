#include "SShooterScreenshotResolver.h"
#include "ShooterStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "SShooterScreenshotEdit.h"
#include "UI/Menu/Widgets/SShooterScreenshot.h"

const FSlateColorBrush SShooterScreenshotResolver::BackgroundColor{FLinearColor(0, 0, 0, 0.8f)};
const FSlateColorBrush SShooterScreenshotResolver::BackgroundItem{FLinearColor(0.2f, 0.2f, 0.2f, 0.9f)};

void SShooterScreenshotResolver::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	LocalEntry = InArgs._LocalEntry;
	CloudEntry = InArgs._CloudEntry;
	OnResolve = InArgs._OnResolve;

	FMargin VerticalMargin(0, 10);
	FMargin ItemMargin(10, 10);

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SImage)
			.Image(&BackgroundColor)
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Your local screenshot conflict the ones stored in the cloudstorage"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(VerticalMargin)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SImage)
					.Image(&BackgroundItem)
				]
				+ SOverlay::Slot()
				.Padding(ItemMargin)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString("Cloud Screenshot"))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBox)
							.HeightOverride(240)
							[
								SNew(SScaleBox)
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Left)
								.Stretch(EStretch::ScaleToFit)
								[
									SNew(SImage)
									.Image(CloudEntry->Image.Get())
								]
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(CloudEntry->Title))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(FString::Printf(TEXT("Last modified time: %s"), *CloudEntry->DateModified.ToString())))
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SBox)
						.WidthOverride(200)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SButton)
							[
								SNew(STextBlock)
								.Text(FText::FromString("Download to\nthis machine"))
							]
							.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
								OnResolve.ExecuteIfBound(RESULT_CLOUD);
								Close();
								return FReply::Handled();
							}))
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(VerticalMargin)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SImage)
					.Image(&BackgroundItem)
				]
				+ SOverlay::Slot()
				.Padding(ItemMargin)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString("Local Screenshot"))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBox)
							.HeightOverride(240)
							[
								SNew(SScaleBox)
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Left)
								.Stretch(EStretch::ScaleToFit)
								[
									SNew(SImage)
									.Image(LocalEntry->Image.Get())
								]
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(LocalEntry->Title))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(FString::Printf(TEXT("Last modified time: %s"), *LocalEntry->DateModified.ToString())))
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SBox)
						.WidthOverride(200)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SButton)
							[
								SNew(STextBlock)
								.Text(FText::FromString("Upload to\ncloudstorage"))
							]
							.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
								OnResolve.ExecuteIfBound(RESULT_LOCAL);
								Close();
								return FReply::Handled();
							}))
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			[
				SNew(SButton)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Cancel"))
				]
				.OnClicked(FOnClicked::CreateLambda([&]() -> FReply {
					Close();
					return FReply::Handled();
				}))
			]
		]
	];
}

void SShooterScreenshotResolver::Show()
{
	FSlateApplication::Get().SetKeyboardFocus(AsShared());
	PlayerOwner->GetPlayerController(0)->bShowMouseCursor = true;
	GEngine->GameViewport->AddViewportWidgetContent(AsShared());
}

void SShooterScreenshotResolver::Close()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
}

void SShooterScreenshotResolver::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SShooterScreenshotResolver::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(AsShared(), EFocusCause::SetDirectly);
}

FReply SShooterScreenshotResolver::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Escape || Key == EKeys::Virtual_Back || Key == EKeys::Gamepad_Special_Left)
	{
		Close();
		Result = FReply::Handled();
	}
	return Result;
}