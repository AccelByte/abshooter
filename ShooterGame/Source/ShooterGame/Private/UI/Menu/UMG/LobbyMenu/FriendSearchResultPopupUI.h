// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "FriendSearchResultEntryUI.h"
#include "FriendSearchResultPopupUI.generated.h"

/**
 * Friend search result popup UI widget.
 */
UCLASS()
class UFriendSearchResultPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Show friend search result popup UI widget. */
	void Show();

	/**
	* @brief Update search result list.
	*
	* @param FriendSearchResultList An array of friend search results.
	*/
	void UpdateSearchResultList(TArray<UFriendSearchResultEntryUI*> FriendSearchResultList);

	/**
	* @brief Show user not found message.
	*
	* @param Username Friend's username who is searched.
	*/
	void ShowUserNotFound(FString Username);

	/** Close search result popup. */
	UFUNCTION()
	void ClosePopup();

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;
	
	/** Search result widget switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SearchResultWidgetSwitcher;

	/** Search result list view. */
	UPROPERTY(meta = (BindWidget))
	class UListView* SearchResultListView;

	/** User not found message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UserNotFoundText;
};
