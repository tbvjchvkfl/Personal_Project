// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Data/ItemStruct.h"
#include "Character/Player/PlayerCharacter.h"

void UInventorySlot::SetItemSlot(FItemData *ItemSlot)
{
	ItemData = ItemSlot;
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	ItemNameText->SetText(FText::FromString(ItemData->TextData.Name));
	ItemImage->SetBrushFromTexture(ItemData->AssetData.Icon);
}
