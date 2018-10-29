#include "ShooterGame.h"
#include "LobbyStyle.h"

FLobbyStyle::FLobbyStyle()
{
}

FLobbyStyle::~FLobbyStyle()
{
}

const FName FLobbyStyle::TypeName(TEXT("FLobbyStyle"));

const FLobbyStyle& FLobbyStyle::GetDefault()
{
	static FLobbyStyle Default;
	return Default;
}

ULobbyWidgetStyle::ULobbyWidgetStyle( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	
}
