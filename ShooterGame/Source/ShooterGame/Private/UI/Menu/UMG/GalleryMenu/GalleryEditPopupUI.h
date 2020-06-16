// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GalleryEditPopupInterface.h"
#include "GalleryEditPopupUI.generated.h"

/**
 * Gallery edit UI widget.
 */
UCLASS()
class UGalleryEditPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Show edit box.
	*
	* @param SlotId Gallery image's slot id.
	* @param Label Gallery image's label.
	*/
	void Show(FString SlotId, FString Label);

	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IGalleryEditPopupInterface* Interface);

protected:
	/** Initialize widget. */
	virtual bool Initialize();

private:
	/** Close edit box. */
	UFUNCTION()
	void CloseBox();

	/** Save label. */
	UFUNCTION()
	void SaveLabel();

	/** Check maximum label characters. */
	UFUNCTION()
	void CheckMaxLabelCharacters(const FText& Text);

	/** Caption edit field. */
	UPROPERTY(meta = (BindWidget))
	class UEditableText* LabelField;

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	/** Save button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveButton;

	/** Max label characters error message. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ErrorText;

	/** Character count field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterCount;

	/** Gallery edit interface. */
	IGalleryEditPopupInterface* GalleryEditPopupInterface;

	/** Image slot id.*/
	FString ImageSlotId;

	/** Character over-limit flag. */
	bool bIsCharactersOverLimit = false;

	/** Red color. */
	FLinearColor RedColor;

	/** White color. */
	FLinearColor WhiteColor;
};
