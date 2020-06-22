// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GalleryEditPopupUI.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

#define MAX_CHARACTERS 30

bool UGalleryEditPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UGalleryEditPopupUI::CloseBox);

	if (!ensure(SaveButton != nullptr)) return false;
	SaveButton->OnClicked.AddDynamic(this, &UGalleryEditPopupUI::SaveLabel);

	if (!ensure(LabelField != nullptr)) return false;

	LabelField->OnTextChanged.AddDynamic(this, &UGalleryEditPopupUI::CheckMaxLabelCharacters);
	
	FString ErrorMessage = FString::Printf(TEXT("Please only use max %d characters."), MAX_CHARACTERS);
	ErrorText->SetText(FText::FromString(ErrorMessage));

	return true;
}

void UGalleryEditPopupUI::Show(FString SlotId, FString Label)
{
	ImageSlotId = SlotId;
	LabelField->SetText(FText::FromString(Label));
	this->AddToPlayerScreen();
}

void UGalleryEditPopupUI::SetInterface(IGalleryEditPopupInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEditPopupUI] Interface is null"));
		return;
	}
	GalleryEditPopupInterface = Interface;
}

void UGalleryEditPopupUI::CheckMaxLabelCharacters(const FText& Text)
{
	FString Label = Text.ToString();
	int32 Length = Label.Len();

	if (Length > MAX_CHARACTERS)
	{
		CharacterCount->SetColorAndOpacity(FLinearColor::Red);
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		bIsCharactersOverLimit = true;
	}
	else
	{
		CharacterCount->SetColorAndOpacity(FLinearColor::White);
		ErrorText->SetVisibility(ESlateVisibility::Collapsed);
		bIsCharactersOverLimit = false;
	}

	FString LengthDisplay = FString::Printf(TEXT("%d / %d"), Length, MAX_CHARACTERS);
	CharacterCount->SetText(FText::FromString(LengthDisplay));
}

#pragma region Button Callback
void UGalleryEditPopupUI::CloseBox()
{
	this->RemoveFromViewport();
}

void UGalleryEditPopupUI::SaveLabel()
{
	if (GalleryEditPopupInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEditPopupUI] Interface is null"));
		return;
	}

	if (bIsCharactersOverLimit) return;

	FString Label = LabelField->GetText().ToString();
	GalleryEditPopupInterface->SaveCaption(ImageSlotId, Label);
	CloseBox();
}
#pragma endregion Button Callback
