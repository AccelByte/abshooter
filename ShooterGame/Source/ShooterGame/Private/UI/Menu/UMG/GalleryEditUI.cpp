// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GalleryEditUI.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

#define MAX_CHARACTERS 30

bool UGalleryEditUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UGalleryEditUI::CloseBox);

	if (!ensure(SaveButton != nullptr)) return false;
	SaveButton->OnClicked.AddDynamic(this, &UGalleryEditUI::SaveLabel);

	if (!ensure(LabelField != nullptr)) return false;

	LabelField->OnTextChanged.AddDynamic(this, &UGalleryEditUI::CheckMaxLabelCharacters);
	
	FString ErrorMessage = FString::Printf(TEXT("Please only use max %d characters."), MAX_CHARACTERS);
	ErrorText->SetText(FText::FromString(ErrorMessage));

	RedColor = FLinearColor(1, 0, 0, 1);
	WhiteColor = FLinearColor(1, 1, 1, 1);

	return true;
}

void UGalleryEditUI::Show(FString SlotId, FString Label)
{
	ImageSlotId = SlotId;
	LabelField->SetText(FText::FromString(Label));
	this->AddToPlayerScreen();
}

void UGalleryEditUI::SetInterface(IGalleryEditInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEditUI] Interface is null"));
		return;
	}
	GalleryEditInterface = Interface;
}

void UGalleryEditUI::CheckMaxLabelCharacters(const FText& Text)
{
	FString Label = Text.ToString();
	int32 Length = Label.Len();

	if (Length > MAX_CHARACTERS)
	{
		CharacterCount->SetColorAndOpacity(RedColor);
		ErrorText->SetVisibility(ESlateVisibility::Visible);
		bIsCharactersOverLimit = true;
	}
	else
	{
		CharacterCount->SetColorAndOpacity(WhiteColor);
		ErrorText->SetVisibility(ESlateVisibility::Collapsed);
		bIsCharactersOverLimit = false;
	}

	FString LengthDisplay = FString::Printf(TEXT("%d / %d"), Length, MAX_CHARACTERS);
	CharacterCount->SetText(FText::FromString(LengthDisplay));
}

#pragma region Button callback
void UGalleryEditUI::CloseBox()
{
	this->RemoveFromViewport();
}

void UGalleryEditUI::SaveLabel()
{
	if (GalleryEditInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEditUI] Interface is null"));
		return;
	}

	if (bIsCharactersOverLimit) return;

	FString Label = LabelField->GetText().ToString();
	GalleryEditInterface->SaveCaption(ImageSlotId, Label);
	CloseBox();
}
#pragma endregion Button callback
