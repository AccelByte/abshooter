#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

//class declare
class SShooterScreenshotPreview : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SShooterScreenshotPreview)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(const FSlateBrush*, Image)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	void Show();

private:
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	TSharedPtr<SWidget> OwnerWidget;
	const FSlateBrush* Image;

	FMargin WidgetOffset;
	FLinearColor WidgetColor;
};