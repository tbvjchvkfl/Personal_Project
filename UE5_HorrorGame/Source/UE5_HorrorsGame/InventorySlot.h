// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UTextBlock;
class UImage;
struct FItemData;

UCLASS()
class UE5_HORRORSGAME_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()


public:

	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(meta = (BindWidget))
	UTextBlock *ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UImage *ItemImage;

	FItemData *ItemData;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void SetItemSlot(FItemData* ItemSlot);

protected:
	virtual void NativeConstruct()override;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
