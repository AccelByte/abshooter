#include "ShooterGame.h"
#include "SShooterCoinsWidget.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SShooterCoinsWidget"

void SShooterCoinsWidget::Construct(const FArguments& InArgs)
{
    CoinsIcon = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/SoundCue_SpeakerIcon.png", FVector2D(144, 144)));

    ChildSlot
    .HAlign(HAlign_Right)
    .VAlign(VAlign_Top)
    .Padding(0, 53, 0, 0)
    [
        SNew(SBox)
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        .HeightOverride(84.0f)
        .WidthOverride(560.0f)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .HAlign(HAlign_Left)
            .VAlign(VAlign_Fill)
            [
                SNew(SBox)
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                .WidthOverride(84.0f)
                .HeightOverride(84.0f)
                [
                    SNew(SOverlay)
                    + SOverlay::Slot()
                    .HAlign(HAlign_Fill)
                    .VAlign(VAlign_Fill)
                    [
                        SNew(SBox)
                        .HAlign(HAlign_Fill)
                        .VAlign(VAlign_Fill)
                        [
                            SNew(SImage)
                            .Image(FShooterStyle::Get().GetBrush("ShooterGame.ProfileBorder"))
                        ]
                    ]
                    + SOverlay::Slot()
                    .HAlign(HAlign_Center)
                    .VAlign(VAlign_Center)
                    [
                        SNew(SBox) // box kiri, buat gambar profile		
                        .HAlign(HAlign_Fill)
                        .VAlign(VAlign_Fill)
                        .WidthOverride(56.0f)
                        .HeightOverride(56.0f)
                        [
                            SNew(SImage) // gambar avatar, klo bisa dari URL	
                            .Image(CoinsIcon.Get())
                        ]
                    ]
                ]
            ]
            + SHorizontalBox::Slot()
            .AutoWidth()
            .HAlign(HAlign_Left)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Margin(FMargin(-10.0f, 0, 0, 0))
                .TextStyle(FShooterStyle::Get(), "ShooterGame.UsernameTextStyle")
                .Text(FText::FromString("9000"))
            ]
        ]
    ];
}

//FMargin SShooterCoinsWidget::GetMenuOffset() const
//{
//    //const float WidgetWidth = 100; //LeftBox->GetDesiredSize().X;// +RightBox->GetDesiredSize().X;
//    //const float WidgetHeight = 50;// LeftBox->GetDesiredSize().Y + MenuHeaderHeight;
//    const float OffsetX = (ScreenRes.X - MenuProfileWidth - 200); // 84 avatar width	
//    FMargin Result = FMargin(OffsetX, 53.0f, 0, 0);
//    return Result;
//}

void SShooterCoinsWidget::BuildAndShowMenu()
{
}