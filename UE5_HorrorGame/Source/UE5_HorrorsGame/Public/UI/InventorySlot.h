// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UTextBlock;
class UImage;
class UButton;
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

	UPROPERTY(meta = (BindWidget))
	UButton *UseButton;

	FItemData *ItemData;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void SetItemSlot(FItemData* ItemSlot);

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	virtual void NativeConstruct()override;
};
