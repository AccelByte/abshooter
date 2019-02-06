#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SShooterInventory.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"

//class declare
class SShooterCoinsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SShooterCoinsWidget){}
	/** end of slate attributes definition */
	SLATE_END_ARGS()

	int32 Balance = -1;

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/** call to rebuild widget */
	void BuildAndShowMenu();

private:
	/** screen resolution */
	FIntPoint ScreenRes;

	TSharedPtr<FSlateBrush> CoinsIcon;

	FText GetBalanceText() const;
};
