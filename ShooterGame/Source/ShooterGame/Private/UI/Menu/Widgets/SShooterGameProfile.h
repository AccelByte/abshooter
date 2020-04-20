// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "Models/ShooterInventory.h"
#include "Models/ShooterGameProfile.h"
#include "Models/AccelByteEcommerceModels.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"

//class declare
class SShooterGameProfile : public SCompoundWidget
{
public:
	SShooterGameProfile();

	SLATE_BEGIN_ARGS(SShooterGameProfile)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer >, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	//SLATE_ARGUMENT(FOnClicked, OnClicked)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/** if we want to receive focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }

	/** Populates profile item */
	void BuildProfileItem();

	/** creates single item widget, called for every list item */
	TSharedRef<ITableRow> OnGenerateWidgetForTileView(TSharedPtr<FAchievementEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FAchievementEntry> InItem, ESelectInfo::Type SelectInfo);

	const FSlateBrush* GetProfileAvatar() const;

	FText GetProfileName() const;

	void SetProfileName(FText ProfileName);

	void SetMVPScore(FText MVPScore);

	void SetTotalMatch(FText TotalMatch);

	void SetTotalDeathsScore(FText TotalDeathsScore);

	void SetTotalKillsScore(FText TotalKillsScore);

	void SetCurrentProfileFromCache(FString UserId, FString DisplayName, FString AvatarPath);

	void UpdateAvatar(FString Url);

protected:

	/** action bindings array */
	TArray< TSharedPtr<FAchievementEntry> > AchievementList;

	/** action bindings list slate widget */
	TSharedPtr < STileView< TSharedPtr<FAchievementEntry> > > AchievementListWidget;

	/** currently selected list item */
	TSharedPtr<FAchievementEntry> SelectedItem;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	/** pointer to our parent widget */
	TSharedPtr<class SWidget> OwnerWidget;

	FSlateColorBrush ConfirmationBackgroundBrush;

	TSharedPtr<SWidget> DialogWidget;

	TSharedPtr<SWidget> LoadingDialogWidget;
	TSharedPtr<STextBlock> LoadingDialogText;

	TSharedPtr<SWidget> MessageDialogWidget;

	bool bRequestAchievementList = false;

	//void GetUserEntitlements();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void ShowLoadingDialog();
	void CloseLoadingDialog();

	void OnFocusLost(const FFocusEvent& InFocusEvent);

	TSharedRef<FAchievementEntry> CreateProfileItem(FString Name, FString Url);

	FOptionalSize GetTileViewWidth(const TArray<TSharedPtr<FAchievementEntry>>&) const;
	FOptionalSize GetTileViewHeight() const;

	float GetScreenWidth() const;
	float GetScreenHeight() const;

	float GetItemWidth() const;
	float GetItemHeight() const;

	// padding for both sides
	const float TileItemWidthRatio;
	const float TileItemHeightRatio;
	
	int32 TileWidth;
	int32 TileHeight;
	const int32 TileColumn;
	const int32 TileRow;

	const float PaddingTopRatio;
	const float PaddingRightRatio;
	const float PaddingLeftRatio;
	const float PaddingBottomRatio;

	TSharedPtr<SScrollBar> ItemsScrollBar;

	TSharedPtr<FSlateDynamicImageBrush> ThumbnailBrush;

	FText GetMVPScore() const;

	FText GetTotalKillsScore() const;

	FText GetTotalDeathsScore() const;

	FText GetTotalMatch() const;

private:

	TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData);

	void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	bool bProfileUpdated;
	
	FText ProfileName;

	FText MVPScore;

	FText TotalKillsScore;

	FText TotalDeathsScore;

	FText TotalMatch;
};


