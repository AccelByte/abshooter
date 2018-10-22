#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SShooterInventory.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"

//class declare
class SShooterInventoryItem : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SShooterInventoryItem)
    {}

    SLATE_ARGUMENT(TWeakPtr<FInventoryEntry>, Item)
    SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer >, PlayerOwner)

    /** end of slate attributes definition */
    SLATE_END_ARGS()

    /** needed for every widget */
    void Construct(const FArguments& InArgs);

protected:

private:
    /** pointer to our parent PC */
    TWeakPtr<struct FInventoryEntry> Item;

    /** pointer to our owner PC */
    TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

    TSharedPtr<FSlateBrush> DefaultBrush;

    TSharedPtr<FSlateBrush> ImageBrush;

    /** style for the menu item */
    const struct FShooterMenuItemStyle *MenuItemStyle;

    TSharedRef<SWidget> GetBottomWidget(const FInventoryEntry * item) const;

    /** get content image*/
    const FSlateBrush* GetImage() const;

    /** getter for active flag */
    bool IsActive() const;

    /** image received callback */
    void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    /** create brush from raw data */
    TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FName ResourceName, TArray<uint8> ImageData);

    /** getter for tile item background color */
    FSlateColor GetButtonBgColor() const;
};
