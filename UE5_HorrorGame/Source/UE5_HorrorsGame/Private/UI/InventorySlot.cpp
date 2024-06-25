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


void UInventorySlot::NativeConstruct()
{
	/*Super::NativeConstruct();
	ItemNameText->SetText(FText::FromString(ItemData->TextData.Name));
	ItemImage->SetBrushFromTexture(ItemData->AssetData.Icon);
	UseButton->OnClicked.AddDynamic(this, &UInventorySlot::UseItem);
	MyPlayer = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));*/
}

void UInventorySlot::SetItemSlot(FItemData *ItemSlot)
{
	/*ItemData = ItemSlot;*/
}

void UInventorySlot::UseItem()
{
	/*switch (ItemData->ItemType)
	{
		case EItemType::Consumable:
			UseHealthPotion();
			
			break;

		default:
			break;
	}*/
}

//float UInventorySlot::UseHealthPotion()
//{
//	auto Health = MyPlayer->GetCurHealth() + 20.0f;
//	if (Health > 100.0f)
//	{
//		Health = 100.0f;
//	}
//	//ItemData->Amount -= 1;
//	return MyPlayer->SetCurHealth(Health);
//}


