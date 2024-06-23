// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemStruct.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	int32 Amount;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	EItemType ItemType;

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
	FORCEINLINE bool GetItemStackSize() const { return Amount == NumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetAmount(const int32 NewAmount);

	UFUNCTION(Category = "Item")
	virtual void Use(class APlayerCharacter *Character);

protected:
	bool operator== (const FName &OtherID)
	{
		return this->ID == OtherID;
	}
};
