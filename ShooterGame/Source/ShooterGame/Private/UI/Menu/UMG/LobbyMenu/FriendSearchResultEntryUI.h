// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FriendSearchResultEntryInterface.h"
#include "FriendSearchResultEntryUI.generated.h"

/**
 * Friend search result entry UI widget.
 */
UCLASS()
class UFriendSearchResultEntryUI : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IFriendSearchResultEntryInterface* Interface);

	/** The user id of the friend who is searched. */
	FString UserId;

	/** The display name of the friend who is searched. */
	FString DisplayName;

	/** The email address of the friend who is searched. */
	FString Email;

private:
	/** Initialize widget. */
	virtual bool Initialize();

	// NOTE:
	// Based on the https://docs.unrealengine.com/en-US/API/Runtime/UMG/Blueprint/IUserObjectListEntry/SetListItemObjectInternal/index.html
	// Function below will be deprecated on 4.23 version, and renamed into NativeOnListItemObjectSet.
	void SetListItemObjectInternal(UObject* InObject) override;

	/** Send a friend request. */
	UFUNCTION()
	void SendFriendRequest();

	/** Display name field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayNameField;

	/** Email address field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EmailField;

	/** Add friend button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AddFriendButton;

	/** Friend search result entry interface. */
	IFriendSearchResultEntryInterface* EntryInterface;
};
