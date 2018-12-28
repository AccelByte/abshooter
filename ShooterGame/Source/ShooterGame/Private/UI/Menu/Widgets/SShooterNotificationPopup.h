#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

//class declare
class SShooterNotificationPopup : public SCompoundWidget
{
public:
    SShooterNotificationPopup();

	DECLARE_DELEGATE(FPopupClosed)

	SLATE_BEGIN_ARGS(SShooterNotificationPopup)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(FString, NotificationMessage)
	SLATE_EVENT(FPopupClosed, OnPopupClosed)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	void Show();
	FText GetNotificationText() const;

protected:
	void SetupAnimations();

private:
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	TSharedPtr<SWidget> OwnerWidget;
	TSharedPtr<FSlateBrush> Image;
	FString NotificationMessage;

	bool bShowing;

	FCurveSequence WidgetAnimation;
	FCurveHandle FadeInCurve;
	FCurveHandle FadeOutCurve;

	FMargin WidgetOffset;
	FLinearColor WidgetColor;
	FPopupClosed OnPopupClosed;

	FMargin GetWidgetOffset() const;

    FSlateColorBrush ColorGrey;
    FSlateColorBrush ColorBlack;

};