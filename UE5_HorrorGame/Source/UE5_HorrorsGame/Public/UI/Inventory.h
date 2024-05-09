// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UWrapBox;
class APlayerCharacter;
class UItemBase;
class UInventorySlot;

UCLASS()
class UE5_HORRORSGAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox *WrapBox;

	TSubclassOf<UInventorySlot> InventoryClass;

	UInventorySlot *SlotWidget;

	TArray<UItemBase *> InventoryItems;

	virtual void NativeConstruct()override;

private:
	APlayerCharacter *Player;
};
