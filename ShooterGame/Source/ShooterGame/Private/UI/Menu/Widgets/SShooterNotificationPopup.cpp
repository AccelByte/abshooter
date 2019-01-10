#include "SShooterNotificationPopup.h"
#include "ShooterStyle.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

SShooterNotificationPopup::SShooterNotificationPopup()
    :ColorGrey(FLinearColor(0.5f, 0.5f, 0.5f)),
    ColorBlack(FLinearColor(0, 0, 0))
{

}

void SShooterNotificationPopup::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	NotificationMessage = InArgs._NotificationMessage;
    AvatarImage = InArgs._AvatarImage;
	OnPopupClosed = InArgs._OnPopupClosed;
	bShowing = false;

	WidgetOffset = FMargin(0, 0, 0, 100.0f);
	WidgetColor = FLinearColor(1.0f, 1.0f, 1.0f);

	ChildSlot
	.VAlign(VAlign_Bottom)
	.HAlign(HAlign_Right)
	.Padding(TAttribute<FMargin>(this, &SShooterNotificationPopup::GetWidgetOffset))
	[
		SNew(SBox)
		.Padding(FMargin(20.0f))
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&ColorGrey)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(90)
					.HeightOverride(90)
					[
						SNew(SOverlay)
						+ SOverlay::Slot()
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						[
							SNew(SImage)
							.Image(&ColorBlack)
						]

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
                                .Image(AvatarImage)
                            ]
                        ]
					]
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(SBox)
					.Padding(FMargin(10.0f))
					[
						SNew(STextBlock)
						.Text(this, &SShooterNotificationPopup::GetNotificationText)
						.ColorAndOpacity(FLinearColor(0, 0, 0))
					]
				]
			]
		]
	];

	SetupAnimations();
}

void SShooterNotificationPopup::Show()
{
	GEngine->GameViewport->AddViewportWidgetContent(AsShared());
	bShowing = true;
	WidgetAnimation.Play(AsShared());
}

FText SShooterNotificationPopup::GetNotificationText() const 
{
	return FText::FromString(NotificationMessage); 
}

void SShooterNotificationPopup::SetupAnimations()
{
	const float FadeInDuration = 2.0f;
	const float ShowDuration = 2.0f;
	const float FadeOutDuration = 2.0f;

	WidgetAnimation = FCurveSequence();
	FadeInCurve = WidgetAnimation.AddCurve(0, 0.5f, ECurveEaseFunction::QuadInOut);
	FadeOutCurve = WidgetAnimation.AddCurveRelative(ShowDuration, FadeOutDuration, ECurveEaseFunction::QuadInOut);
}

void SShooterNotificationPopup::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	auto ScreenPosition = AllottedGeometry.LocalToAbsolute(FVector2D(0, 0));

	if (bShowing)
	{
		WidgetOffset.Right = -200 * (1.0f - FadeInCurve.GetLerp());
		WidgetColor.A = 1.0f - FadeOutCurve.GetLerp();
		SetColorAndOpacity(WidgetColor);
		if (WidgetAnimation.IsAtEnd())
		{
			bShowing = false;
			GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
			OnPopupClosed.ExecuteIfBound();
		}
	}
}

FMargin SShooterNotificationPopup::GetWidgetOffset() const
{
	return WidgetOffset;
}