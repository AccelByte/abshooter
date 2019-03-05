// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateWidgetStyleContainerBase.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "GalleryStyle.generated.h"

USTRUCT()
struct FGalleryStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FGalleryStyle();
	virtual ~FGalleryStyle();

	// FSlateWidgetStyle
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };

	static const FGalleryStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateBrush GalleryBackground;
	UPROPERTY(EditAnywhere, Category = Common)
	FSlateBrush GalleryListViewBackground;

	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FButtonStyle Close;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FSlateBrush CloudOff;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FSlateBrush CloudDone;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FSlateBrush CloudDownload;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FSlateBrush CloudUpload;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FButtonStyle Edit;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FButtonStyle ZoomOut;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FSlateBrush SyncProblem;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FButtonStyle Resolve;
	UPROPERTY(EditAnywhere, Category = GalleryButton)
	FButtonStyle Retry;

	UPROPERTY(EditAnywhere, Category = GallerySlot)
	FSlateBrush SlotEmptyBackground;
	UPROPERTY(EditAnywhere, Category = GallerySlot)
	FSlateBrush SlotBackground;
	UPROPERTY(EditAnywhere, Category = GallerySlot)
	FSlateBrush SlotTextImage;
	UPROPERTY(EditAnywhere, Category = GallerySlot)
	FTextBlockStyle SlotNumberStyle;
	UPROPERTY(EditAnywhere, Category = GallerySlot)
	FTextBlockStyle SlotTitleStyle;

	UPROPERTY(EditAnywhere, Category = GalleryPreviewZoomIn)
	FButtonStyle ClosePreviewButtonStyle;
	UPROPERTY(EditAnywhere, Category = GalleryPreviewZoomIn)
	FSlateBrush PreviewImageBackground;

	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FTextBlockStyle EditCaptionTextStyle;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FButtonStyle EditCaptionCloseButtonStyle;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FButtonStyle EditCaptionSaveButtonStyle;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FEditableTextStyle EditCaptionInputFieldStyle;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FSlateBrush EditCaptionInputFieldBackground;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FSlateBrush EditCaptionBackground;
	UPROPERTY(EditAnywhere, Category = GalleryEdit)
	FSlateBrush EditCaptionInnerBackground;
};


UCLASS(hidecategories=Object, MinimalAPI)
class UGalleryStyleWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FGalleryStyle MenuStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &MenuStyle );
	}
};