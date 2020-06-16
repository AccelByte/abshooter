// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "FriendSearchResultPopupUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

FCriticalSection FriendSearchResultPopupUIMutex;

bool UFriendSearchResultPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UFriendSearchResultPopupUI::ClosePopup);

	if (!ensure(SearchResultWidgetSwitcher != nullptr)) return false;
	if (!ensure(SearchResultListView != nullptr)) return false;
	if (!ensure(UserNotFoundText != nullptr)) return false;

	return true;
}

void UFriendSearchResultPopupUI::Show()
{
	this->AddToPlayerScreen();
}

void UFriendSearchResultPopupUI::UpdateSearchResultList(TArray<UFriendSearchResultEntryUI*> FriendSearchResultList)
{
	if (this == NULL) return;

	FScopeLock Lock(&FriendSearchResultPopupUIMutex);

	SearchResultListView->SetListItems(FriendSearchResultList);
	SearchResultListView->RegenerateAllEntries();
	SearchResultWidgetSwitcher->SetActiveWidget(SearchResultListView);
}

void UFriendSearchResultPopupUI::ShowUserNotFound(FString Username)
{
	FString Message = FString::Printf(TEXT("User [%s] is not found."), *Username);
	UserNotFoundText->SetText(FText::FromString(Message));
	SearchResultWidgetSwitcher->SetActiveWidget(UserNotFoundText);
}

#pragma region Button Callback
void UFriendSearchResultPopupUI::ClosePopup()
{
	this->RemoveFromViewport();
}
#pragma endregion Button Callback
