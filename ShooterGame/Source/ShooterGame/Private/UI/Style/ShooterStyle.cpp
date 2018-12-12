// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterStyle.h"
#include "SlateGameResources.h"

TSharedPtr< FSlateStyleSet > FShooterStyle::ShooterStyleInstance = NULL;

void FShooterStyle::Initialize()
{
	if ( !ShooterStyleInstance.IsValid() )
	{
		ShooterStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle( *ShooterStyleInstance );
	}
}

void FShooterStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle( *ShooterStyleInstance );
	ensure( ShooterStyleInstance.IsUnique() );
	ShooterStyleInstance.Reset();
}

FName FShooterStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ShooterStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

PRAGMA_DISABLE_OPTIMIZATION
TSharedRef< FSlateStyleSet > FShooterStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FShooterStyle::GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");
	FSlateStyleSet& Style = StyleRef.Get();

	// Load the speaker icon to be used for displaying when a user is talking
	Style.Set("ShooterGame.Speaker", new IMAGE_BRUSH("Images/SoundCue_SpeakerIcon", FVector2D(32, 32)));

	// Load the coins icon
	Style.Set("ShooterGame.Coins", new IMAGE_BRUSH("Images/CoinsIcon", FVector2D(32, 32)));

	// Load the image icon to be used for displaying when a image loading
	Style.Set("ShooterGame.Image", new IMAGE_BRUSH("Images/ImageIcon", FVector2D(32, 32)));
	Style.Set("ShooterGame.CornerBorder", new BOX_BRUSH("Images/ProfileBorder", FMargin(0.1f)));

	// Load inventory icons
	Style.Set("ShooterGame.LaserBeam", new IMAGE_BRUSH("Images/LaserBeam", FVector2D(96, 96)));
	Style.Set("ShooterGame.Bullet", new IMAGE_BRUSH("Images/Bullet", FVector2D(96, 96)));
	Style.Set("ShooterGame.Phaser", new IMAGE_BRUSH("Images/Phaser", FVector2D(96, 96)));
	Style.Set("ShooterGame.SubmachineGun", new IMAGE_BRUSH("Images/SubmachineGun", FVector2D(96, 96)));
    //Style.Set("ShooterGame.SubmachineGun", new IMAGE_BRUSH("Images/SubmachineGun", FVector2D(96, 96)));


	// The border image used to draw the replay timeline bar
	Style.Set("ShooterGame.ReplayTimelineBorder", new BOX_BRUSH("Images/ReplayTimeline", FMargin(3.0f / 8.0f)));

	// The border image used to draw the replay timeline bar
	Style.Set("ShooterGame.ReplayTimelineIndicator", new IMAGE_BRUSH("Images/ReplayTimelineIndicator", FVector2D(4.0f, 26.0f)));

	// The image used to draw the replay pause button
	Style.Set("ShooterGame.ReplayPauseIcon", new IMAGE_BRUSH("Images/ReplayPause", FVector2D(32.0f, 32.0f)));

	Style.Set("ShooterGame.ProfileBorder", new IMAGE_BRUSH("Images/ProfileBorder", FVector2D(84.0f, 84.0f)));

	// Fonts still need to be specified in code for now
	Style.Set("ShooterGame.MenuServerListTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 14))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.ScoreboardListTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 14))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.MenuProfileNameStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 18))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.UsernameTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Medium", 15))
		.SetColorAndOpacity(FLinearColor(FColor(142, 246, 255)))
		//.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("ShooterGame.UserIDTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Regular", 11))
		.SetColorAndOpacity(FLinearColor(FColor(24, 105, 112) ))
		//.SetShadowOffset(FIntPoint(-1, 1))
	);


	Style.Set("ShooterGame.MenuTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 24))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.MenuHeaderTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 26))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.WelcomeScreen.WelcomeTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Regular", 32))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.DefaultScoreboard.Row.HeaderTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 24))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(0,1))
		);

	Style.Set("ShooterGame.DefaultScoreboard.Row.StatTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Regular", 18))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(0,1))
		);

	Style.Set("ShooterGame.SplitScreenLobby.StartMatchTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Regular", 16))
		.SetColorAndOpacity(FLinearColor::Green)
		.SetShadowOffset(FVector2D(0,1))
		);

	Style.Set("ShooterGame.DemoListCheckboxTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/ChakraPetch-Bold", 12))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1,1))
		);

	Style.Set("ShooterGame.Switch.Left", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonLeft", FVector2D(32, 32)))
		);

	Style.Set("ShooterGame.Switch.Right", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonRight", FVector2D(32, 32)))
		);

	Style.Set("ShooterGame.Switch.Up", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonUp", FVector2D(32, 32)))
		);

	Style.Set("ShooterGame.Switch.Down", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonDown", FVector2D(32, 32)))
		);

	return StyleRef;
}
PRAGMA_ENABLE_OPTIMIZATION

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FShooterStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FShooterStyle::Get()
{
	return *ShooterStyleInstance;
}
