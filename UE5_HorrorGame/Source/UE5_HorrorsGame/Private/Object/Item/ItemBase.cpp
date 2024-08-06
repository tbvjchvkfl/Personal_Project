// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Item/ItemBase.h"
#include "Component/InventoryComponent.h"


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
	ItemCopy->AssetData = this->AssetData;

	return ItemCopy;
}

void UItemBase::Use(APlayerCharacter *Character)
{

}
