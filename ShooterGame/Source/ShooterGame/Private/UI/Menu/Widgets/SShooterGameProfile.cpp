// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGame.h"
#include "SShooterGameProfile.h"
#include "ShooterStyle.h"
#include "SShooterMenuWidget.h"
#include "ShooterMenuWidgetStyle.h"
#include "ShooterUIHelpers.h"
#include "SShooterInventoryItem.h"
#include "SShooterProfileItem.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteEntitlementApi.h"
#include "AccelByteError.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "ShooterInventoryWidgetStyle.h"
#include "GameProfileWidgetStyle.h"

using namespace AccelByte::Api;

SShooterGameProfile::SShooterGameProfile()
	: ConfirmationBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
	, TileWidth(320)
	, TileHeight(160)
	, TileColumn(4)
	, TileRow(2)
	, TileItemWidthRatio(0.1300f)
	, TileItemHeightRatio(0.1851f)
	, PaddingTopRatio(0.1244f)
	, PaddingLeftRatio(0.0844f)
	, PaddingRightRatio(0.1644f)
	, PaddingBottomRatio(0.0244f)
{
}

void SShooterGameProfile::Construct(const FArguments& InArgs)
{
	ThumbnailBrush.Reset();
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	bProfileUpdated = false;

	const FShooterInventoryStyle* InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
	const FGameProfileStyle* ProfileStyle = &FShooterStyle::Get().GetWidgetStyle<FGameProfileStyle>("GameProfileStyle");

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBox)
			.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
			{
				return FOptionalSize(GetScreenWidth());
			}))
				.HeightOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
			{
				return FOptionalSize(GetScreenHeight());
			}))
#pragma region Content
			[
				SNew(SHorizontalBox)
#pragma region ProfilePict
				+SHorizontalBox::Slot()
				.Padding(FMargin(GetScreenWidth() * PaddingLeftRatio, GetScreenHeight() * PaddingTopRatio, 10, 10))
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Right)
				.FillWidth(.2)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					[
						SNew(SBox)
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						.WidthOverride(GetScreenHeight()* 0.15f)
						.HeightOverride(GetScreenHeight()* 0.15f)
						[
							SNew(SImage)
							.Image(&ProfileStyle->AvatarBackgroundBrush)
						]
					]
					+SOverlay::Slot()
					[
						SNew(SBox)
						.VAlign(VAlign_Fill)
						.HAlign(HAlign_Fill)
						.Padding(25)
						[
							SNew(SImage)
							.Image(this, &SShooterGameProfile::GetProfileAvatar)
						]
					]
				]
#pragma endregion ProfilePict
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(.8)
				[
					SNew(SVerticalBox)
#pragma region ProfileName
					+SVerticalBox::Slot()
					.Padding(FMargin(10, GetScreenHeight() * PaddingTopRatio, GetScreenWidth()*PaddingRightRatio, 10))
					.FillHeight(.4)
					.AutoHeight()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SScaleBox)
							.Stretch(EStretch::ScaleToFitY)
							.HAlign(HAlign_Left)
							[
								SNew(SImage)
								.Image(&ProfileStyle->HeaderProfileName)
							]
						]
						+SVerticalBox::Slot()
						[
							SNew(STextBlock)
							.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileNameTextStyle")
							.Text(this, &SShooterGameProfile::GetProfileName)
						]
					]
#pragma endregion ProfileName
#pragma region Stats
					+SVerticalBox::Slot()
					.FillHeight(.6)
					.HAlign(HAlign_Fill)
					.AutoHeight()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.Padding(10, 0, GetScreenWidth()*PaddingRightRatio, 10)
						.HAlign(HAlign_Fill)
						.AutoHeight()
						[
							SNew(SScaleBox)
							.Stretch(EStretch::ScaleToFitY)
							.HAlign(HAlign_Left)
							[
								SNew(SImage)
								.Image(&ProfileStyle->HeaderStats)
							]
						]
						+SVerticalBox::Slot()
						.Padding(10, 0, GetScreenWidth()*PaddingRightRatio, 10)
						.HAlign(HAlign_Fill)
						.AutoHeight()
						[
							SNew(SHorizontalBox)
#pragma region MVP
							+SHorizontalBox::Slot()
							.FillWidth(.25)
							.HAlign(HAlign_Fill)
							.Padding(0,0,5,0)
							[
								SNew(SOverlay)
								+SOverlay::Slot()
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Fill)
								[
									SNew(SImage)
									.Image(&ProfileStyle->StatsBackgroundBrush)
								]
								+SOverlay::Slot()
								[
									SNew(SHorizontalBox)
									+SHorizontalBox::Slot()
									.FillWidth(.3)
									[
										SNew(SBox)
										.HAlign(HAlign_Fill)
										.WidthOverride(GetScreenWidth()* 0.012f)
										.HeightOverride(GetScreenWidth()* 0.012f)
										[
											SNew(SScaleBox)
											.Stretch(EStretch::ScaleToFitX)
											[
												SNew(SImage)
												.Image(&ProfileStyle->IconMVP)
											]
										]
									]
									+SHorizontalBox::Slot()
									.FillWidth(.7)
									.VAlign(VAlign_Center)
									[
										SNew(SVerticalBox)
										+SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										.AutoHeight()
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNameTextStyle")
												.Text(FText::FromString("MVP"))
											]
										]
										+SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNumTextStyle")
												.Text(this, &SShooterGameProfile::GetMVPScore)
											]
										]
									]
								]
							]
#pragma endregion MVP
#pragma region KILLS
							+ SHorizontalBox::Slot()
							.FillWidth(.25)
							.HAlign(HAlign_Fill)
							.Padding(5, 0, 5, 0)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Fill)
								[
									SNew(SImage)
									.Image(&ProfileStyle->StatsBackgroundBrush)
								]
								+ SOverlay::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.FillWidth(.3)
									[
										SNew(SBox)
										.HAlign(HAlign_Fill)
										.WidthOverride(GetScreenWidth()* 0.012f)
										.HeightOverride(GetScreenWidth()* 0.012f)
										[
											SNew(SScaleBox)
											.Stretch(EStretch::ScaleToFitX)
											[
												SNew(SImage)
												.Image(&ProfileStyle->IconKills)
											]
										]
									]
									+ SHorizontalBox::Slot()
									.FillWidth(.7)
									.VAlign(VAlign_Center)
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										.AutoHeight()
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNameTextStyle")
												.Text(FText::FromString("TOTAL KILLS"))
											]
										]
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNumTextStyle")
												.Text(this,&SShooterGameProfile::GetTotalKillsScore)
											]
										]
									]
								]
							]
#pragma endregion KILLS
#pragma region TOTAL_MATCH
							+ SHorizontalBox::Slot()
							.FillWidth(.25)
							.HAlign(HAlign_Fill)
							.Padding(5, 0, 5, 0)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Fill)
								[
									SNew(SImage)
									.Image(&ProfileStyle->StatsBackgroundBrush)
								]
								+ SOverlay::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.FillWidth(.3)
									[
										SNew(SBox)
										.HAlign(HAlign_Fill)
										.WidthOverride(GetScreenWidth()* 0.012f)
										.HeightOverride(GetScreenWidth()* 0.012f)
										[
											SNew(SScaleBox)
											.Stretch(EStretch::ScaleToFitX)
											[
												SNew(SImage)
												.Image(&ProfileStyle->IconMatchPlayed)
											]
										]
									]
									+ SHorizontalBox::Slot()
									.FillWidth(.7)
									.VAlign(VAlign_Center)
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										.AutoHeight()
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNameTextStyle")
												.Text(FText::FromString("TOTAL MATCH"))
											]
										]
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNumTextStyle")
												.Text(this, &SShooterGameProfile::GetTotalMatch)
											]
										]
									]
								]
							]
#pragma endregion TOTAL_MATCH
#pragma region DEATHS
							+ SHorizontalBox::Slot()
							.FillWidth(.25)
							.HAlign(HAlign_Fill)
							.Padding(5, 0, 0, 0)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Fill)
								[
									SNew(SImage)
									.Image(&ProfileStyle->StatsBackgroundBrush)
								]
								+ SOverlay::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.FillWidth(.3)
									[
										SNew(SBox)
										.HAlign(HAlign_Fill)
										.WidthOverride(GetScreenWidth()* 0.012f)
										.HeightOverride(GetScreenWidth()* 0.012f)
										[
											SNew(SScaleBox)
											.Stretch(EStretch::ScaleToFitX)
											[
												SNew(SImage)
												.Image(&ProfileStyle->IconDeaths)
											]
										]
									]
									+ SHorizontalBox::Slot()
									.FillWidth(.7)
									.VAlign(VAlign_Center)
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										.AutoHeight()
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNameTextStyle")
												.Text(FText::FromString("TOTAL DEATHS"))
											]
										]
										+ SVerticalBox::Slot()
										.HAlign(HAlign_Left)
										[
											SNew(SBox)
											[
												SNew(STextBlock)
												.TextStyle(FShooterStyle::Get(), "ShooterGame.ProfileStatNumTextStyle")
												.Text(this, &SShooterGameProfile::GetTotalDeathsScore)
											]
										]
									]
								]
							]
#pragma endregion DEATHS
						]
					]
#pragma endregion Stats
#pragma region PersonalAchievement
					+SVerticalBox::Slot()
					.FillHeight(.5)
					.AutoHeight()
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(10, 10, GetScreenWidth()*PaddingRightRatio, 0)
						[
							SNew(SScaleBox)
							.Stretch(EStretch::ScaleToFitY)
							.HAlign(HAlign_Left)
							[
								SNew(SImage)
								.Image(&ProfileStyle->HeaderAchievement)
							]
						]
						+SVerticalBox::Slot()
						.Padding(10, 10, GetScreenWidth()*PaddingRightRatio, 10)
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
								.FillWidth(1.0f)
								[
									SNew(SBox)
									.VAlign(VAlign_Fill)
									.HAlign(HAlign_Fill)
									.Padding(0)
									.HeightOverride(this, &SShooterGameProfile::GetTileViewHeight)
									.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
									{
										return GetTileViewWidth(AchievementList);
									}))
									[
										SAssignNew(AchievementListWidget, STileView< TSharedPtr<FAchievementEntry> >)
										.ItemWidth(this, &SShooterGameProfile::GetItemWidth)
										.ItemHeight(this, &SShooterGameProfile::GetItemHeight)
										.ListItemsSource(&AchievementList)
										.ExternalScrollbar(ItemsScrollBar)
										.OnSelectionChanged(this, &SShooterGameProfile::EntrySelectionChanged)
										.OnGenerateTile(this, &SShooterGameProfile::OnGenerateWidgetForTileView)
										.SelectionMode(ESelectionMode::Single)
									]
								]
								+ SHorizontalBox::Slot()	//Scroll bar
								.AutoWidth()
								[
									SNew(SBox)
									.VAlign(VAlign_Bottom)
									.Padding(FMargin(0, 0, 0, 0))
									[
										SAssignNew(ItemsScrollBar, SScrollBar)
										.IsEnabled(true)
										.Thickness(FVector2D(2.0f, 2.0f))
										.Orientation(EOrientation::Orient_Vertical)
										.Visibility(EVisibility::Visible)
										.Style(&InventoryStyle->ScrollBarStyle)
									]
								]
							]
							+SOverlay::Slot()
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Center)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Empty")))
								.Visibility(TAttribute<EVisibility>::Create([&]()
								{
									return AchievementList.Num() == 0 ? EVisibility::Visible : EVisibility::Collapsed;
								}))
							]
						]
					]
#pragma endregion PersonalAchevement
/*TODO: will be needed when we agreed to show entitlement on game profile
#pragma region Entitlement
					+SVerticalBox::Slot()
					.Padding(FMargin(10,10,GetScreenWidth()*PaddingRightRatio, GetScreenHeight()*PaddingBottomRatio))
					.FillHeight(.3)
					[
						SNew(SOverlay)
						+ SOverlay::Slot()
						.VAlign(VAlign_Bottom)
						.HAlign(HAlign_Right)
						.Padding(TAttribute<FMargin>::Create([&]() -> FMargin
						{
							return FMargin(10, 10, GetScreenWidth()*PaddingRightRatio, 10);
						}))
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.FillWidth(1.0f)
							[
								SNew(SBox)
								.VAlign(VAlign_Fill)
								.HAlign(HAlign_Fill)
								.Padding(0)
								.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
								{
									return GetTileViewWidth(InventoryList);
								}))
								.HeightOverride(this, &SShooterGameProfile::GetTileViewHeight)
								[
									SAssignNew(InventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
									.ItemWidth(this, &SShooterGameProfile::GetItemWidth)
									.ItemHeight(this, &SShooterGameProfile::GetItemHeight)
									.ListItemsSource(&InventoryList)
									.ExternalScrollbar(ItemsScrollBar)
									.OnGenerateTile(this, &SShooterGameProfile::OnGenerateWidgetForTileView)
									.SelectionMode(ESelectionMode::Single)
								]
							]
							+ SHorizontalBox::Slot()	//Scroll bar
							.AutoWidth()
							[
								SNew(SBox)
								.HAlign(HAlign_Right)
								.Padding(FMargin(0, 0, 0, 0))
								[
									SAssignNew(ItemsScrollBar, SScrollBar)
									.IsEnabled(true)
									.Thickness(FVector2D(2.0f, 2.0f))
									.Orientation(EOrientation::Orient_Vertical)
									.Visibility(EVisibility::Visible)
									.Style(&InventoryStyle->ScrollBarStyle)
								]
							]
						]
						+ SOverlay::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Empty")))
							.Visibility(TAttribute<EVisibility>::Create([&]()
							{
								return EVisibility::Visible;
							}))
						]
					]
#pragma endregion Entitlement*/
				]
			]
#pragma endregion Content		
		]
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Right)
		.Padding(0, 0, 200, GetScreenHeight()*PaddingBottomRatio)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.ButtonStyle(&MenuStyle->EscapeButton)
				.VAlign(VAlign_Bottom)
				.OnClicked(FOnClicked::CreateLambda([&]()
				{
					static_cast<SShooterMenuWidget*>(OwnerWidget.Get())->MenuGoBack();
					return FReply::Handled();
				}))
			]
			+ SHorizontalBox::Slot()
			.Padding(10, 0, 0, 0)
			.AutoWidth()
			[
				SNew(SImage)
				.Image(&MenuStyle->EscapeMainMenuInfo)
			]
		]
	];
}

FOptionalSize SShooterGameProfile::GetTileViewWidth(const TArray<TSharedPtr<FAchievementEntry>>& List) const
{
	return FOptionalSize(GetItemWidth() * TileColumn + (List.Num() > TileColumn * TileRow ? 16 : 0));
}

FOptionalSize SShooterGameProfile::GetTileViewHeight() const
{
	return FOptionalSize(GetItemHeight() * TileRow + 4);
}

float SShooterGameProfile::GetScreenWidth() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return Result.X;
}

float SShooterGameProfile::GetScreenHeight() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return Result.Y;
}

float SShooterGameProfile::GetItemWidth() const
{
	return FMath::Max(GetScreenWidth() * TileItemWidthRatio, 144.9f);
}

float SShooterGameProfile::GetItemHeight() const
{
	return FMath::Max(GetScreenHeight() * TileItemHeightRatio, 112.5f);
}

TSharedPtr<FSlateDynamicImageBrush> SShooterGameProfile::CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData)
{
	UE_LOG(LogTemp, Log, TEXT("SShooterGameProfile::CreateBrush : %s, Content Type: %s"), *ResourceName.ToString(), *ContentType);
	TSharedPtr<FSlateDynamicImageBrush> Brush;

	uint32 BytesPerPixel = 4;
	int32 Width = 0;
	int32 Height = 0;

	bool bSucceeded = false;
	TArray<uint8> DecodedImage;
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	int BitDepth = 8;
	//jpg
	EImageFormat ImageFormat = EImageFormat::JPEG;
	ERGBFormat RgbFormat = ERGBFormat::BGRA;
	//png
	if (ContentType.Contains(TEXT("png")))
	{
		ImageFormat = EImageFormat::PNG;
		RgbFormat = ERGBFormat::BGRA;
	}
	//bmp
	else if (ContentType.Contains(TEXT("bmp")))
	{
		ImageFormat = EImageFormat::BMP;
		RgbFormat = ERGBFormat::BGRA;
	}

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		Width = ImageWrapper->GetWidth();
		Height = ImageWrapper->GetHeight();

		const TArray<uint8>* RawData = NULL;

		if (ImageWrapper->GetRaw(RgbFormat, BitDepth, RawData))
		{
			DecodedImage = *RawData;
			bSucceeded = true;
		}
	}

	if (bSucceeded && FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), DecodedImage))
	{
		Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
	}

	return Brush;
}

void SShooterGameProfile::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TArray<uint8> ImageData = Response->GetContent();
		ThumbnailBrush = CreateBrush(Response->GetContentType(), FName(*Request->GetURL()), ImageData);
		bProfileUpdated = true;
	}
}

void SShooterGameProfile::BuildProfileItem()
{
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());

#if PLATFORM_WINDOWS
	FString Locale = FWindowsPlatformMisc::GetDefaultLocale();
#elif PLATFORM_MAC
	FString Locale = FMacPlatformMisc::GetDefaultLocale();
#elif PLATFORM_LINUX
	FString Locale = FLinuxPlatformMisc::GetDefaultLocale();
#endif

	if (!bRequestAchievementList)
	{
		bRequestAchievementList = true;
		AchievementList.Empty();
		AchievementList.Add(CreateProfileItem("MASTER SHOOTER","Slate/Images/icon-achievement-1.png"));
		AchievementList.Add(CreateProfileItem("COMMANDER EXPERT", "Slate/Images/icon-achievement-2.png"));
		AchievementList.Add(CreateProfileItem("THE BEAST KILLER", "Slate/Images/icon-achievement-3.png"));
		AchievementList.Add(CreateProfileItem("GOD OF WAR", "Slate/Images/icon-achievement-4.png"));
		AchievementList.Add(CreateProfileItem("ONE MAN ARMY", "Slate/Images/icon-achievement-2.png"));
		AchievementList.Add(CreateProfileItem("FORGOTTEN LEGEND", "Slate/Images/icon-achievement-2.png"));
		AchievementList.Add(CreateProfileItem("MAN WHO TOOK DOWN AN EMPIRE", "Slate/Images/icon-achievement-4.png"));
		AchievementList.Add(CreateProfileItem("SHARPSHOOTER", "Slate/Images/icon-achievement-1.png"));
		AchievementList.Add(CreateProfileItem("LIVING LEGEND", "Slate/Images/icon-achievement-3.png"));
		AchievementList.Add(CreateProfileItem("ONE HIT KILL", "Slate/Images/icon-achievement-3.png"));
		AchievementListWidget->RequestListRefresh();
		/*
			TODO: implement get profile achievement
			references: InventoryItem*/
	}
}

TSharedRef<ITableRow> SShooterGameProfile::OnGenerateWidgetForTileView(TSharedPtr<FAchievementEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterProfileItem, OwnerTable, PlayerOwner, Item);
}

void SShooterGameProfile::EntrySelectionChanged(TSharedPtr<FAchievementEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

/*TODO: will be needed when we want to show profile entitlement on game profile
void SShooterGameProfile::GetUserEntitlements() 
{
	Entitlement::QueryUserEntitlement("", "", 0, 100, AccelByte::THandler<FAccelByteModelsEntitlementPagingSlicedResult>::CreateLambda([&](const FAccelByteModelsEntitlementPagingSlicedResult& Result)
	{
		TMap<FString, int> Quantities;
		for (int i = 0; i < Result.Data.Num(); i++)
		{
            if (Result.Data[i].Type == EAccelByteEntitlementType::DURABLE)
            {
                Quantities[Result.Data[i].ItemId] = Quantities.FindOrAdd(Result.Data[i].ItemId) + 1;
            }
            else
            {
                Quantities[Result.Data[i].ItemId] = Quantities.FindOrAdd(Result.Data[i].ItemId) + Result.Data[i].UseCount;
            }			
		}

	}), AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message)
	{
		UE_LOG(LogTemp, Display, TEXT("Query entitlement failed: code: %d, message: %s"), Code, *Message)
	}), EAccelByteEntitlementClass::ENTITLEMENT, EAccelByteAppType::NONE);
}*/

const FSlateBrush* SShooterGameProfile::GetProfileAvatar() const
{
	return FShooterStyle::Get().GetBrush("ShooterGame.Avatar");
}

FText SShooterGameProfile::GetProfileName() const
{
	return ProfileName;
}

FString SShooterGameProfile::GetProfileId() const
{
	return ProfileId;
}

FText SShooterGameProfile::GetMVPScore() const
{
	return MVPScore;
}

FText SShooterGameProfile::GetTotalDeathsScore() const
{
	return TotalDeathsScore;
}

FText SShooterGameProfile::GetTotalMatch() const
{
	return TotalMatch;
}

FText SShooterGameProfile::GetTotalKillsScore() const
{
	return TotalKillsScore;
}

void SShooterGameProfile::SetProfileName(FText ProfileName)
{
	SShooterGameProfile::ProfileName = ProfileName;
}

void SShooterGameProfile::SetProfileId(FString ProfileId)
{
	SShooterGameProfile::ProfileId = ProfileId;
}

void SShooterGameProfile::SetMVPScore(FText MVPScore)
{
	SShooterGameProfile::MVPScore = MVPScore;
}

void SShooterGameProfile::SetTotalMatch(FText TotalMatch)
{
	SShooterGameProfile::TotalMatch = TotalMatch;
}

void SShooterGameProfile::SetTotalDeathsScore(FText TotalDeathsScore)
{
	SShooterGameProfile::TotalDeathsScore = TotalDeathsScore;
}

void SShooterGameProfile::SetTotalKillsScore(FText TotalKillsScore)
{
	SShooterGameProfile::TotalKillsScore = TotalKillsScore;
}

void SShooterGameProfile::SetCurrentProfileFromCache(FString ProfileId, FString UserId, FString DisplayName, FString AvatarPath)
{
	if (!bProfileUpdated)
	{
		ProfileName = FText::FromString(DisplayName);
		SShooterGameProfile::ProfileId = ProfileId;

		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *AvatarPath))
		{
			ThumbnailBrush = CreateBrush(FPaths::GetExtension(AvatarPath), FName(*AvatarPath), ImageData);
			bProfileUpdated = true;
		}
	}
}

void SShooterGameProfile::UpdateAvatar(FString Url)
{
	if (!bProfileUpdated)
	{
		// start download avatar
		TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
		ThumbRequest->SetVerb("GET");
		ThumbRequest->SetURL(Url);
		ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SShooterGameProfile::OnThumbImageReceived);
		ThumbRequest->ProcessRequest();
	}
}

void SShooterGameProfile::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if (LoadingDialogWidget.IsValid())
	{
		int DotCount = fmod(InCurrentTime, 5) * 2;
		FString Text = "..";
		for (int i = 0; i < DotCount; i++)
		{
			Text += ".";
		}
		LoadingDialogText->SetText(Text);
	}
}

void SShooterGameProfile::ShowLoadingDialog()
{
	SAssignNew(LoadingDialogWidget, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(&ConfirmationBackgroundBrush)
		]
	+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(LoadingDialogText, STextBlock)
			.TextStyle(FShooterStyle::Get(), "ShooterGame.MenuHeaderTextStyle")
		.Text(FText::FromString("..."))
		];

	GEngine->GameViewport->AddViewportWidgetContent(LoadingDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(LoadingDialogWidget);
}

void SShooterGameProfile::CloseLoadingDialog()
{
	if (LoadingDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(LoadingDialogWidget.ToSharedRef());
		LoadingDialogWidget.Reset();
	}
}

void SShooterGameProfile::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

TSharedRef< FAchievementEntry > SShooterGameProfile::CreateProfileItem(FString Name, FString Url /*TODO: change with Achievement model implementation*/)
{
	TSharedRef< FAchievementEntry > Achievement = MakeShareable(new FAchievementEntry());
	Achievement->AchievementId = "001";
	Achievement->Name = Name;
	Achievement->ImageURL = Url;
	Achievement->Achieved = true;
	/*TODO: to be changed after implementing profile achievement
	  references: InventoryItem
	*/
	return Achievement;
}