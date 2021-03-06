// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IncomingFriendRequestPopupInterface.h"
#include "IncomingFriendRequestPopupUI.generated.h"

/**
 * Incoming friend request popup UI widget.
 */
UCLASS()
class UIncomingFriendRequestPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Show incoming friend request popup UI widget.
	*
	* @param FriendId The friend's id who send the request friend.
	* @param DisplayName The friend's display who send the request friend.
	*/
	void Show(FString FriendId, FString DisplayName);

	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IIncomingFriendRequstPopupInterface* Interface);

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** Ignore incoming friend request. */
	UFUNCTION()
	void IgnoreRequest();

	/** Reject incoming friend request. */
	UFUNCTION()
	void RejectRequest();

	/** Accept incoming friend request. */
	UFUNCTION()
	void AcceptRequest();

	/** Ignore button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* IgnoreButton;

	/** Reject button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* RejectButton;

	/** Accept button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AcceptButton;

	/** Incoming friend request message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;

	/** The friend's id who send the request friend. */
	FString UserId;

	/** Incoming friend request popup interface. */
	IIncomingFriendRequstPopupInterface* IncomingFriendRequstPopupInterface;
};
