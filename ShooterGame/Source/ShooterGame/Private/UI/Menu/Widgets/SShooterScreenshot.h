#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "Models/AccelByteCloudStorageModels.h"

typedef TSharedPtr<int> FScreenshotComboBoxType;

enum EScreenshotState
{
	NONE = 0,
	ERROR,
	ERROR_UPLOAD,
	CONFLICT,
	DONE,
	// loading bar would be showed (state > DONE)
	DOWNLOADING,
	UPLOADING
};

struct FScreenshotEntry
{
	int SlotNumber;
	FString Title;
	TSharedPtr< FSlateBrush > Image = nullptr;
	FString Path;
    FString SlotID;
	FString Checksum;
	EScreenshotState State = NONE;
};

struct FScreenshotComboBoxGroup
{
	TSharedPtr<TArray<FScreenshotComboBoxType>> AvailableOptions;
	TArray<TSharedPtr<class SScreenshotSlotComboBox>> ListComboBox;
};

//class declare
class SShooterScreenshot : public SCompoundWidget
{
public:
	SShooterScreenshot();

	SLATE_BEGIN_ARGS(SShooterScreenshot)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/** if we want to receive focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }

	/** Populates inventory item */
	void BuildScreenshotItem();

	/** creates single item widget, called for every list item */
	TSharedRef<ITableRow> OnGenerateWidgetForTileView(TSharedPtr<FScreenshotEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** creates single item widget, called for every list item */
	TSharedRef<ITableRow> OnGenerateWidgetForListView(TSharedPtr<struct FScreenShotSelectedEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void OnReleaseWidgetForListView(const TSharedRef<ITableRow>& TableRow);

	void EntrySelectionChanged(TSharedPtr<FScreenshotEntry> InItem, ESelectInfo::Type SelectInfo);

	void ToggleScreenshotWindow();

	bool IsShowing();

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

    void MainMenuMode() { bMainMenuMode = true; }

    TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FString ContentType, FName ResourceName, const TArray<uint8>& ImageData);

    void LoadSingleSlot(const FAccelByteModelsSlot& Slot, int32 SlotIndex);

    void RefreshFromCloud();

    void OnReceiveSlotImage(const TArray<uint8>& Result, const FAccelByteModelsSlot& Slot, int32 SlotIndex);
    void OnDeleteSlot(const FString& SlotID);
	void OnResolveSlot(int32 SlotIndex);


protected:
	/** if menu is currently opened*/
	bool bIsMenuUp;

	/** action bindings array */
	TArray< TSharedPtr<FScreenshotEntry> > SavedScreenshotList;

	/** action bindings list slate widget */
	TSharedPtr < STileView< TSharedPtr<FScreenshotEntry> > > SavedScreenshotListWidget;

	/** action bindings array */
	TArray< TSharedPtr<struct FScreenShotSelectedEntry> > ScreenshotList;

	/** action bindings list slate widget */
	TSharedPtr < SListView< TSharedPtr<FScreenShotSelectedEntry> > > ScreenshotListWidget;

	/** currently selected list item */
	TSharedPtr<FScreenshotEntry> SelectedItem;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	/** pointer to our parent widget */
	TSharedPtr<class SWidget> OwnerWidget;

	void OnFocusLost(const FFocusEvent& InFocusEvent);
	FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent);

	void UpdateCurrentScreenshotList();

	FString GetScreenshotsDir();
	FString GetUserScreenshotsDir();
	bool IsScreenshotMetadataExists();
	void SaveScreenshotMetadata();
	void LoadScreenshotMetadata();
	void SaveLocalScreenshotImage(int32 Index, const TArray<uint8>& Binary);
	// Temporary save cloud image to disk, would be used to resolve conflict
	void SaveScreenshotCloudImage(int32 Index, const TArray<uint8>& Binary);
	// Resolve screenshot: remove local, replace image from cloud
	void ResolveUseCloudScreenshot(int32 Index);
	void ResolveUseLocalScreenshot(int32 Index);
	bool LoadScreenshotImage(int32 Index, TArray<uint8>& Result);
	void DeleteScreenshotImage(int32 Index);

	void SaveToCloud(int32 Index);

	TArray<FScreenshotEntry> PreviousSelectedScreenshot;

	TSharedPtr<FScreenshotComboBoxGroup> ComboBoxGroup;

    bool bMainMenuMode;

	TArray<FAccelByteModelsSlot> LocalSlots;

	// temporary store cloud slot when conflict
	TMap<uint8, FAccelByteModelsSlot> ConflictSlots;
	TMap<uint8, TSharedPtr<FSlateBrush>> ConflictImages;
};


