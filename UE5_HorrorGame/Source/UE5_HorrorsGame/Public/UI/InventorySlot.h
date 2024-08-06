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
class UItemBase;

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

	UItemBase *ItemRef;

	APlayerCharacter *MyPlayer;

	UInventory *MyInventory;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; };
	FORCEINLINE void SetItemReference(UItemBase *ItemIn) { ItemReference = ItemIn; };
	
	UFUNCTION()
	void UseItem();

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(VisibleAnywhere, Category = "InventorySlot")
	UItemBase *ItemReference;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void NativeConstruct()override;
	virtual void NativeOnInitialized() override;
	//virtual FReply NativeOnMouseButtonUp(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)override;
	virtual void NativeOnMouseLeave(const FPointerEvent &InMouseEvent)override;
	float UseHealthPotion();
};
