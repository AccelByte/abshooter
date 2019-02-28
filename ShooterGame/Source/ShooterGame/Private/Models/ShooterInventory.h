#pragma once

/** item type*/
UENUM()
enum class EInventoryItemType : uint8
{
	WEAPON UMETA(DisplayName = "Weapon"),
	AMMO UMETA(DisplayName = "Ammo"),
	COIN UMETA(DisplayName = "Coin")
};

/** inventory display information */
struct FInventoryEntry
{
	/** item id*/
	FString ItemId;

	/** item name*/
	FString Name;

	/** item image URL*/
	FString ImageURL;

	/** currency code*/
	FString CurrencyCode;

	/** currency type*/
	FString CurrencyType;

	/** item price*/
	int32 Price;

	/** item price*/
	int32 DiscountedPrice;

	/** item consumable flag*/
	bool Purchasable;

	/** item owned flag*/
	bool Owned = false;

	/** item type*/
	EInventoryItemType Type;

	/** item quantity*/
	int32 Quantity = 1;
};

/** item type conversion*/
inline FText GetItemTypeAsText(EInventoryItemType EnumValue) {
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EInventoryItemType"), true);
	if (!EnumPtr) return FText::FromString("Invalid");

	return FText::FromString(EnumPtr->GetNameStringByValue((int64)EnumValue));
}
