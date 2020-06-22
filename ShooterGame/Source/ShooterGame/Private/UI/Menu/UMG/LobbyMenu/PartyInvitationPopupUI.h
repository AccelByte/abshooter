// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "Blueprint/UserWidget.h"
#include "Models/AccelByteLobbyModels.h"
#include "PartyInvitationPopupInterface.h"
#include "PartyMemberEntryUI.h"
#include "PartyInvitationPopupUI.generated.h"

/**
 * Party invitation popup UI widget.
 */
UCLASS()
class UPartyInvitationPopupUI : public UUserWidget, public FTickableGameObject
{
	GENERATED_BODY()

public:
	/**
	* @brief Show party invitation popup UI widget.
	*
	* @param FriendId The friend's id who invites to the party.
	* @param InvitationInformation The information of the party invitation.
	*/
	void Show(FString DisplayName, FAccelByteModelsPartyGetInvitedNotice InvitationInformation);

	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IPartyInvitationPopupInterface* Interface);

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** TickableObject Functions */
	virtual void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	virtual TStatId GetStatId() const override;

	/** Reject party invitation. */
	UFUNCTION()
	void RejectPartyInvitation();

	/** Accept party invitation */
	UFUNCTION()
	void AcceptPartyInvitation();

	/** Reject button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* RejectButton;

	/** Accept button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AcceptButton;

	/** Party invitation message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;

	/** Reject button text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RejectText;

	/** The information of the party invitation. */
	FAccelByteModelsPartyGetInvitedNotice InvitationInfo;

	/** Party invitation counter. */
	float PartyInvitationCounter = PARTY_INVITATION_COUNTER;

	/** Party invitation popup interface. */
	IPartyInvitationPopupInterface* PartyInvitationPopupInterface;
};
