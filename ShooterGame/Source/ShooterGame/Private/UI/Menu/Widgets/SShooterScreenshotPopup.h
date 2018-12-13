#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

//class declare
class SShooterScreenshotPopup : public SCompoundWidget
{
public:
	DECLARE_DELEGATE(FPopupClosed)

	SLATE_BEGIN_ARGS(SShooterScreenshotPopup)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(TSharedPtr<FSlateBrush>, Image)
	SLATE_EVENT(FPopupClosed, OnPopupClosed)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void Show();

protected:
	void SetupAnimations();

private:
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	TSharedPtr<SWidget> OwnerWidget;
	TSharedPtr<FSlateBrush> Image;

	bool bShowing;

	FCurveSequence WidgetAnimation;
	FCurveHandle FadeInCurve;
	FCurveHandle FadeOutCurve;

	FMargin WidgetOffset;
	FLinearColor WidgetColor;
	FPopupClosed OnPopupClosed;

	FMargin GetWidgetOffset() const;
};