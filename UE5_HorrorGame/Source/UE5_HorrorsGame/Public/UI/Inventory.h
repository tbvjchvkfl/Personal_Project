// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UWrapBox;
class UTextBlock;
//class APlayerCharacter;
//class APickUpItem;
class UInventorySlot;
class UInventoryComponent;

UCLASS()
class UE5_HORRORSGAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(meta = (BindWidget))
	UWrapBox *WrapBox;

	/*UPROPERTY(EditAnywhere, Category = "ItemSlot")
	TSubclassOf<UUserWidget> InventoryClass;*/

	UPROPERTY()
	UInventoryComponent *InventoryComp;

	UPROPERTY()
	APlayerCharacter *Player;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlot> InventorySlotClass;
	
	//FItemData *ItemReference;

	//TArray<FItemData*> InventoryItems;

	//APickUpItem *Items;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void NativeConstruct()override;

	UFUNCTION(Category = "Add to Item")
	void RefreshInventory();

	//UFUNCTION(BlueprintCallable)
	//void RemoveItem();
	
protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;
};
