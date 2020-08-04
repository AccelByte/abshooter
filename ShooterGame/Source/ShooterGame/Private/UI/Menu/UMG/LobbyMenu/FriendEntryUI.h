// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShooterLobbyModels.h"
#include "FriendEntryInterface.h"
#include "FriendEntryUI.generated.h"

/**
 * Friend entry UI widget.
 */
UCLASS()
class UFriendEntryUI : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IFriendEntryInterface* Interface);

	/** Friend profile data. */
	FFriendEntry Data;

private:
	/** Initialize widget. */
	virtual bool Initialize();

	// NOTE:
	// Based on the https://docs.unrealengine.com/en-US/API/Runtime/UMG/Blueprint/IUserObjectListEntry/SetListItemObjectInternal/index.html
	// Function below will be deprecated on 4.23 version, and renamed into NativeOnListItemObjectSet.
	void SetListItemObjectInternal(UObject* InObject) override;

	/** Send chat friend request. */
	UFUNCTION()
	void SendChatRequest();

	/** Send invitation match request. */
	UFUNCTION()
	void SendPartyInvitationRequest();

	/** Send unfriend request. */
	UFUNCTION()
	void SendUnfriendRequest();

	/** Send accepting friend request. */
	UFUNCTION()
	void SendAcceptRequest();

	/** Send rejection friend request. */
	UFUNCTION()
	void SendRejectRequest();

	/** Send cancel friend request. */
	UFUNCTION()
	void SendCancelRequest();

	/** Display name field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayNameField;

	/** Presence field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PresenceField;

	/** Chat button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* ChatButton;
	
	/** Invite button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* InviteButton;
	
	/** Unfriend button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* UnfriendButton;
	
	/** Accept friend request button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AcceptButton;

	/** Reject friend request button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* RejectButton;

	/** Cancel friend request button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton; 

	/** Friend button switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* FriendButtonSwitcher;

	/** Request button box. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* RequestBox;

	/** Online button box. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* OnlineBox;

	/** Friend's avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/** Friend entry interface. */
	IFriendEntryInterface* EntryInterface;

	/** Default avatar image. */
	FSlateBrush DefaultAvatar;
};
