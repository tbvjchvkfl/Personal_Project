// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "UI/Inventory.h"
#include "Data/ItemStruct.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Object/Item/ItemBase.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	ItemNameText->SetText(FText::FromString(ItemReference->TextData.Name));
	ItemImage->SetBrushFromTexture(ItemReference->AssetData.Icon);
	UseButton->OnClicked.AddDynamic(this, &UInventorySlot::UseItem);
	MyPlayer = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UInventorySlot::NativeOnInitialized()
{
	
}

//FReply UInventorySlot::NativeOnMouseButtonUp(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
//{
//	return FReply();
//}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent &InMouseEvent)
{
	
}

void UInventorySlot::UseItem()
{
	switch (ItemReference->ItemType)
	{
		case EItemType::Consumable:
			UseHealthPotion();
			break;
		default:
			break;
	}
}

float UInventorySlot::UseHealthPotion()
{
	auto Health = MyPlayer->GetCurHealth() + 20.0f;
	if (Health > 100.0f)
	{
		Health = 100.0f;
	}
	ItemReference->Amount -= 1;
	return MyPlayer->SetCurHealth(Health);
}
