// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Item/ItemBase.h"

UItemBase::UItemBase()
{

}

UItemBase *UItemBase::CreateItemCopy()const
{
	auto ItemCopy = NewObject<UItemBase>(StaticClass());
	ItemCopy->ID = this->ID;
	ItemCopy->Amount = this->Amount;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->AssetData = this->AssetData;

	return ItemCopy;
}

void UItemBase::SetAmount(const int32 NewAmount)
{
	if (NewAmount != Amount)
	{
		Amount = FMath::Clamp(NewAmount, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);
	}
}

void UItemBase::Use(APlayerCharacter *Character)
{

}
