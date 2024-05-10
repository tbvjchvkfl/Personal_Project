// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UWrapBox;
class APlayerCharacter;
class UInventorySlot;
struct FItemData;

UCLASS()
class UE5_HORRORSGAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox *WrapBox;

	UPROPERTY(EditAnywhere, Category = "ItemSlot")
	TSubclassOf<UUserWidget> InventoryClass;

	UInventorySlot *SlotWidget;

	TArray<FItemData*> InventoryItems;

	APlayerCharacter *Player;

	virtual void NativeConstruct()override;

	void AddItemToInventory();
};
