#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "../Menu/Widgets/SShooterStore.h"
#include "ShooterTypes.h"

DECLARE_DELEGATE_OneParam(FOnUrlChanged, const FText&);

class SShooterPaymentDialog : public SCompoundWidget
{
public:
	/** The player that owns the dialog.*/
	TWeakObjectPtr<ULocalPlayer> PlayerOwner;
	
	/** Delegate that called when a page's URL contain a callback URL.*/
	FSimpleDelegate OnCallbackUrlLoaded;

	/** A URL that indicates a payment already finished.*/
	FString CallBackUrl;

	SLATE_BEGIN_ARGS(SShooterPaymentDialog)
	{}

	/** The player that owns the dialog.*/
	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	/** Paywall URL that will be opened immediately.*/
	SLATE_ARGUMENT(FString, PaymentUrl)
	/** A URL that indicates a payment already finished.*/
	SLATE_ARGUMENT(FString, CallBackUrl)
	/** Delegate that called when a page's URL contain a callback URL.*/
	SLATE_ARGUMENT(FSimpleDelegate, OnCallbackUrlLoaded)
	/** Delegate that called when a ESC button clicked.*/
	SLATE_ARGUMENT(FOnClicked, OnCloseClicked)

	SLATE_END_ARGS()	

	void Construct(const FArguments& InArgs);

	FVector2D GetScreenSize() const;
	virtual bool SupportsKeyboardFocus() const override;
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;
	TSharedPtr<class SWebBrowser> WebBrowserWidget;
	TSharedPtr<SButton> CloseButton;
	FOnClicked OnCloseClicked;

private:
	FReply ExecuteConfirm(const int32 UserIndex);

};
