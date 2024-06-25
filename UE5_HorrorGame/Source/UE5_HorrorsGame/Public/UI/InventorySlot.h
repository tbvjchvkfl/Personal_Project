// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UTextBlock;
class UImage;
class UButton;
class APlayerCharacter;
class UInventory;
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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *UseButton;

	FItemData *ItemData;

	APlayerCharacter *MyPlayer;

	UInventory *MyInventory;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void SetItemSlot(FItemData* ItemSlot);

	UFUNCTION(BlueprintCallable)
	void UseItem();
	
	


protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	//float UseHealthPotion();
	virtual void NativeConstruct()override;
};
