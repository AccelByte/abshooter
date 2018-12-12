#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

//class declare
class SShooterScreenshotEdit : public SCompoundWidget
{
public:
	DECLARE_DELEGATE(FOnSave)

	SLATE_BEGIN_ARGS(SShooterScreenshotEdit)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(struct FScreenshotEntry*, Entry)
	SLATE_ARGUMENT(FOnSave, OnSave)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	void Show();

private:
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	TSharedPtr<SWidget> OwnerWidget;
	struct FScreenshotEntry* Entry;

	TSharedPtr<SEditableText> TextTitle;
	FOnSave OnSave;
};