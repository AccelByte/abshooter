#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "SShooterMenuWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "LobbyStyle.h"

struct FFriendEntry
{
	FString UserId;
	FString Name;
	FString Presence; //ONLINE, INGAME, IDLE, OFFLINE
	FString AvatarSmallUrl;
};

//class declare
class SLobbyFriendList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLobbyFriendList)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	void OnTextSearchChanged(const FText& Text);

	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo);

	void InputReceived();

	void UpdateSearchStatus();

	void BeginFriendSearch();
	void OnFriendSearchFinished();
	void UpdateFriendList();

	void MoveSelection(int32 MoveBy);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

protected:

	bool bSearchingForFriends;

	double LastSearchTime;

	double MinTimeBetweenSearches;

	TArray< TSharedPtr<FFriendEntry> > FriendList;
	TArray< TSharedPtr<FFriendEntry> > CompleteFriendList;

	TSharedPtr< SListView< TSharedPtr<FFriendEntry> > > FriendListWidget;

	TSharedPtr<FFriendEntry> SelectedItem;

	FText GetBottomText() const;

	FText StatusText;

	FString MapFilterName;

	int32 BoxWidth;

	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	TSharedPtr<class SWidget> OwnerWidget;

	TSharedPtr<SScrollBar> FriendScrollBar;
};


