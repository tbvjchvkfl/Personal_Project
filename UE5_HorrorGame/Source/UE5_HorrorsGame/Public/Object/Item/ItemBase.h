// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ItemStruct.h"
#include "ItemBase.generated.h"

class APlayerCharacter;

UCLASS()
class UE5_HORRORSGAME_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	/*UPROPERTY()
	UInventoryComponent *OwningInventory;*/

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemAssetData AssetData;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	UItemBase();

	UItemBase *CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.maxStackSize; }

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(APlayerCharacter *Character);

protected:
	bool operator==(const FName &OtherID) const
	{
		return ID == OtherID;
	}
};
