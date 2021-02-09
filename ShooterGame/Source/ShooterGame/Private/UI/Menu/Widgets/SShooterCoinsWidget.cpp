#include "SShooterCoinsWidget.h"
#include "ShooterGame.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

void SShooterCoinsWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Fill)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(0.063f)
		+ SVerticalBox::Slot()
		.FillHeight(0.937f)
		.VAlign(VAlign_Top)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.HeightOverride(56.0f)
			.WidthOverride(560.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Fill)
				[
					SNew(SBox)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.WidthOverride(56.0f)
					.HeightOverride(56.0f)
					[
						SNew(SImage) // Coins Icon	
						.Image(FShooterStyle::Get().GetBrush("ShooterGame.VirtualCoin"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Margin(FMargin(8.0f, 0, 0, 0))
					.TextStyle(FShooterStyle::Get(), "ShooterGame.UsernameTextStyle")
					.Text(this, &SShooterCoinsWidget::GetBalanceText)
				]
			]
		]
	];
}

void SShooterCoinsWidget::BuildAndShowMenu()
{
}

FText SShooterCoinsWidget::GetBalanceText() const
{
	return (Balance >= 0) ? FText::FromString(FString::FromInt(Balance)) : FText::FromString(TEXT("_"));
}
