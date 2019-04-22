#include "SWebBrowser.h"
#include "ShooterGame.h"
#include "ShooterStyle.h"
#include "SShooterPaymentDialog.h"
#include "ShooterGameInstance.h"
#include "PopupStyle.h"
#include "ShooterMenuWidgetStyle.h"

void SShooterPaymentDialog::Construct( const FArguments& InArgs )
{	
	PlayerOwner = InArgs._PlayerOwner;
	OnCloseClicked = InArgs._OnCloseClicked;
	OnCallbackUrlLoaded = InArgs._OnCallbackUrlLoaded;
	CallBackUrl = InArgs._CallBackUrl;

	const FPopupStyle* PopupStyle = &FShooterStyle::Get().GetWidgetStyle<FPopupStyle>("DefaultPopupStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		
		+SOverlay::Slot()
		.Padding(FMargin(50, 30))
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(1) [ SNew(SBox) ]
			+ SHorizontalBox::Slot().FillWidth(2)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().FillHeight(1) [ SNew(SBox) ]
				+ SVerticalBox::Slot().FillHeight(2)
				[
					SAssignNew(WebBrowserWidget, SWebBrowser)
					.InitialURL(InArgs._PaymentUrl)
					.ShowControls(false)
					.SupportsTransparency(true)
					.OnUrlChanged(FOnTextChanged::CreateLambda([&](const FText& LatestUrl)
					{
						if (LatestUrl.ToString().Contains(CallBackUrl))
						{
							WebBrowserWidget->StopLoad();
							OnCallbackUrlLoaded.ExecuteIfBound();
						}
					}))
				]
				+ SVerticalBox::Slot().FillHeight(1) [ SNew(SBox) ]
			]
			+ SHorizontalBox::Slot().FillWidth(1) [ SNew(SBox) ]
		]
		
		+SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center)
		.Padding(FMargin(0, 0, 0, 50))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(CloseButton, SButton)
				.ButtonStyle(&MenuStyle->EscapeButton)
				.VAlign(VAlign_Bottom)
				.OnClicked(FOnClicked::CreateLambda([&]()
				{
					OnCloseClicked.Execute();
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

FVector2D SShooterPaymentDialog::GetScreenSize() const
{
	FVector2D ViewPortSize = FVector2D(1, 1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	return ViewPortSize;
}

bool SShooterPaymentDialog::SupportsKeyboardFocus() const
{
	return true;
}

FReply SShooterPaymentDialog::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
}

FReply SShooterPaymentDialog::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	const FKey Key = KeyEvent.GetKey();
	const int32 UserIndex = KeyEvent.GetUserIndex();

	if (Key == EKeys::Escape || Key == EKeys::Virtual_Back)
	{
		if(OnCloseClicked.IsBound())
		{
			return OnCloseClicked.Execute();
		}
	}

	return FReply::Unhandled();
}
