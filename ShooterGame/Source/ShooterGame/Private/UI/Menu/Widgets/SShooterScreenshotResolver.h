#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "Api/AccelByteCloudStorageApi.h"

enum EScreenshotResolveResult
{
	RESULT_LOCAL,
	RESULT_CLOUD
};

struct FScreenshotResolveEntry
{
	FString Checksum;
	FString Title;
	TSharedPtr<FSlateBrush> Image;
	FDateTime DateModified;

	FScreenshotResolveEntry(const FAccelByteModelsSlot& Slot, TSharedPtr<FSlateBrush> Image)
	{
		this->Checksum = Slot.Checksum;
		this->Title = Slot.Label;
		this->Image = Image;
		this->DateModified = Slot.DateModified;
	}
};

//class declare
class SShooterScreenshotResolver : public SCompoundWidget
{
public:
	DECLARE_DELEGATE_OneParam(FOnResolve, EScreenshotResolveResult)

	SLATE_BEGIN_ARGS(SShooterScreenshotResolver)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(TSharedPtr<FScreenshotResolveEntry>, LocalEntry)
	SLATE_ARGUMENT(TSharedPtr<FScreenshotResolveEntry>, CloudEntry)
	SLATE_EVENT(FOnResolve, OnResolve)

	SLATE_END_ARGS()

	/** if we want to receive focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	void Show();
	void Close();

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	void OnFocusLost(const FFocusEvent& InFocusEvent);
	FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent);

private:
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	TSharedPtr<SWidget> OwnerWidget;
	TSharedPtr<FScreenshotResolveEntry> LocalEntry;
	TSharedPtr<FScreenshotResolveEntry> CloudEntry;
	FOnResolve OnResolve;

	static const FSlateColorBrush BackgroundColor;
	static const FSlateColorBrush BackgroundItem;
};