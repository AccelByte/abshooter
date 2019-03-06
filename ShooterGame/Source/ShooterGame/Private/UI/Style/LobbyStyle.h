#pragma once

#include "SlateWidgetStyleContainerBase.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "RichTextLayoutMarshaller.h"
#include "LobbyStyle.generated.h"

USTRUCT()
struct FLobbyStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FLobbyStyle();
	virtual ~FLobbyStyle();

	// FSlateWidgetStyle
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };

	static const FLobbyStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Background)
	FSlateBrush LobbyBackground;
	UPROPERTY(EditAnywhere, Category = Background)
	UMaterialInterface* LobbyMaterial;
	UPROPERTY(EditAnywhere, Category = Background)
	UMaterialInterface* MainMenuMaterial;

	UPROPERTY(EditAnywhere, Category = FriendList)
	FSlateBrush FriendListBackground;

	UPROPERTY(EditAnywhere, Category = FriendList)
	FSlateBrush SearchBarBackground;

	UPROPERTY(EditAnywhere, Category = FriendList)
	FEditableTextBoxStyle SearchBarStyle;
	FLobbyStyle& SetSearchBarStyle(const FEditableTextBoxStyle& InSearchBarStyle) { SearchBarStyle = InSearchBarStyle; return *this; }

	UPROPERTY(EditAnywhere, Category = FriendList)
	FHeaderRowStyle HeaderRowStyle;
	FLobbyStyle& SetHeaderRowStyle(const FHeaderRowStyle& InHeaderRowStyle) { HeaderRowStyle = InHeaderRowStyle; return *this; }

	UPROPERTY(EditAnywhere, Category = FriendList)
	FScrollBarStyle ScrollBarStyle;
	FLobbyStyle& SetScrollBarStyle(const FScrollBarStyle& InScrollBarStyle) { ScrollBarStyle = InScrollBarStyle; return *this; }

	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FTextBlockStyle UserNameTextStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FTextBlockStyle PresenceTextStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FTextBlockStyle InviteButtonTextStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FSlateBrush FriendAvatarBorderBrush;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FButtonStyle InviteButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FButtonStyle ChatButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FButtonStyle UnfriendButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendList)
	FButtonStyle AddFriendButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendList)
	FButtonStyle AcceptRequestFriendButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendList)
	FButtonStyle RejectRequestFriendButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendList)
	FButtonStyle CancelRequestFriendButtonStyle;
	UPROPERTY(EditAnywhere, Category = FriendEntry)
	FTableRowStyle FriendRowStyle;

	UPROPERTY(EditAnywhere, Category = Chat)
	FSlateBrush ChatAreaBackground;
	UPROPERTY(EditAnywhere, Category = Chat)
	FButtonStyle ChatTabLeftButtonStyle;
	UPROPERTY(EditAnywhere, Category = Chat)
	FButtonStyle ChatTabRightButtonStyle;
	UPROPERTY(EditAnywhere, Category = Chat)
	FButtonStyle ChatTabButtonStyle;
	UPROPERTY(EditAnywhere, Category = Chat)
	FTextBlockStyle ChatTabTextStyle;
	UPROPERTY(EditAnywhere, Category = Chat)
	FTextBlockStyle ChatTabTextDisabledStyle;
	
	UPROPERTY(EditAnywhere, Category = Conversation)
	FTextBlockStyle ChatStatStyle;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FScrollBoxStyle ConversationScrollBoxStyle;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FScrollBarStyle ConversationScrollBarStyle;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FTextBlockStyle ConversationTextStyle;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FSlateBrush ConversationInputBackgroundBrush;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FEditableTextBoxStyle ConversationInputTextStyle;
	UPROPERTY(EditAnywhere, Category = Conversation)
	FButtonStyle ConversationInputSendButtonStyle;
	
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush PartyLeaderIcon; //Leader badge
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush UnoccupiedPartySlot;
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush MemberBoxPartySlot;
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush LeaderBoxPartySlot;
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush PartyInvitationBackground;
	UPROPERTY(EditAnywhere, Category = Party)
	FButtonStyle KickPartyMemberButton;
	UPROPERTY(EditAnywhere, Category = Party)
	FButtonStyle LeavePartyMemberButton;
	UPROPERTY(EditAnywhere, Category = Party)
	FButtonStyle CreatePartyMemberButton;
	UPROPERTY(EditAnywhere, Category = Party)
	FButtonStyle StartMatchButton;
	UPROPERTY(EditAnywhere, Category = Party)
	FSlateBrush WarningMatchImage;
	UPROPERTY(EditAnywhere, Category = Party)
	FTextBlockStyle FindingMatchTextStyle;
	UPROPERTY(EditAnywhere, Category = Party)
	FButtonStyle CancelMatchButton;

};


UCLASS(hidecategories=Object, MinimalAPI)
class ULobbyWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FLobbyStyle MenuStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &MenuStyle );
	}
};