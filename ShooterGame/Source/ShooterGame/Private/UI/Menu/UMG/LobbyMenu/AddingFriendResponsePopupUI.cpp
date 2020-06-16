// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AddingFriendResponsePopupUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UAddingFriendResponsePopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UAddingFriendResponsePopupUI::ClosePopup);

	return true;
}

void UAddingFriendResponsePopupUI::Show()
{
	this->AddToPlayerScreen();
}

#pragma region Button Callback
void UAddingFriendResponsePopupUI::ClosePopup()
{
	this->RemoveFromViewport();
}
#pragma endregion Button Callback
