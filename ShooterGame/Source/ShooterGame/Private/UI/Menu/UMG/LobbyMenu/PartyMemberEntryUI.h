// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShooterLobbyModels.h"
#include "PartyMemberEntryInterface.h"
#include "PartyMemberEntryUI.generated.h"

// TODO: Set value in the game config.
/** in seconds. */
#define PARTY_INVITATION_COUNTER 30

/**
 * Party member entry UI widget.
 */
UCLASS()
class UPartyMemberEntryUI : public UUserWidget, public IUserObjectListEntry, public FTickableGameObject
{
	GENERATED_BODY()

public:
	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IPartyMemberEntryInterface* Interface);

	/** Party member data. */
	FPartyMemberEntry Data;

	void SetKickButtonState(ESlateVisibility InVisibility);

	/** Party invitation counter. */
	float PartyInvitationCounter = PARTY_INVITATION_COUNTER;

private:
	/** Initialize widget. */
	virtual bool Initialize();

	// NOTE:
	// Based on the https://docs.unrealengine.com/en-US/API/Runtime/UMG/Blueprint/IUserObjectListEntry/SetListItemObjectInternal/index.html
	// Function below will be deprecated on 4.23 version, and renamed into NativeOnListItemObjectSet.
	void SetListItemObjectInternal(UObject* InObject) override;

	/** TickableObject Functions */
	virtual void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	virtual TStatId GetStatId() const override;

	/** Leave party. */
	UFUNCTION()
	void LeaveParty();

	/** Kick party member. */
	UFUNCTION()
	void KickPartyMember();

	/** Party leader icon. */
	UPROPERTY(meta = (BindWidget))
	class UImage* PartyLeaderIcon;

	/** User avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/** Display name field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayNameField;

	/** Waiting response text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaitingResponseText;

	/** Party button switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* PartyButtonSwitcher;

	/** Leave member button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* LeaveButton;;

	/** Kick party member button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* KickButton;;

	/** Entry data panel. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* EntryDataBox;

	/** Party member entry interface. */
	IPartyMemberEntryInterface* EntryInterface;

	/** Default avatar image. */
	FSlateBrush DefaultAvatar;
};
