#include "ShooterGame.h"
#include "SShooterCoinsWidget.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

void SShooterCoinsWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Top)
	.Padding(0, 53, 0, 0)
	[
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.HeightOverride(84.0f)
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
				.WidthOverride(84.0f)
				.HeightOverride(84.0f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SImage)
							.Image(FShooterStyle::Get().GetBrush("ShooterGame.ProfileBorder"))
						]
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.WidthOverride(56.0f)
						.HeightOverride(56.0f)
						[
							SNew(SImage) // Coins Icon	
							.Image(FShooterStyle::Get().GetBrush("ShooterGame.Coins"))
						]
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Margin(FMargin(-8.0f, 0, 0, 0))
				.TextStyle(FShooterStyle::Get(), "ShooterGame.UsernameTextStyle")
				.Text(FText::FromString("9000"))
			]
		]
	];
}

void SShooterCoinsWidget::BuildAndShowMenu()
{
}