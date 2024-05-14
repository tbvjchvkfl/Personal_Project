// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UWrapBox;
class UTextBlock;
class APlayerCharacter;
class APickUpItem;
class UInventorySlot;
struct FItemData;

UCLASS()
class UE5_HORRORSGAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox *WrapBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *CoinText;

	FItemData *ItemReference;

	UPROPERTY(EditAnywhere, Category = "ItemSlot")
	TSubclassOf<UUserWidget> InventoryClass;

	UInventorySlot *SlotWidget;

	TArray<FItemData*> InventoryItems;

	APlayerCharacter *Player;

	APickUpItem *Items;

	bool JustSetCoinData;

	virtual void NativeConstruct()override;

	void AddItemToInventory();

	void BindingCoinText();

	UFUNCTION(BlueprintCallable)
	void RemoveItem();
	
};
