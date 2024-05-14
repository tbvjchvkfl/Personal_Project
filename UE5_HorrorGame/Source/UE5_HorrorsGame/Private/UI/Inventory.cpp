// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/InventorySlot.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "UI/HorrorsHUD.h"
#include "Data/ItemStruct.h"
#include "Object/Item/PickUpItem.h"
#include "Components/Button.h"


// Add to Viewport 할 때 불리는 함수`
void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	JustSetCoinData = true;
	CoinText->SetText(FText::AsNumber(Player->GetPlayerCoin()));
}

void UInventory::AddItemToInventory()
{
	if (Player)
	{
		InventoryItems = Player->GetInventoryItem();
		BindingCoinText();
		for (int i = 0; i < InventoryItems.Num(); i++)
		{
			if (InventoryClass)
			{
				SlotWidget = Cast<UInventorySlot>(CreateWidget(GetWorld(), InventoryClass));
				if (SlotWidget)
				{
					SlotWidget->SetItemSlot(InventoryItems[i]);
					WrapBox->AddChild(SlotWidget);
				}
			}
		}
	}
}

void UInventory::RemoveItem()
{
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i]->Amount < 1)
		{
			WrapBox->RemoveChild(SlotWidget);
		}
	}
}

void UInventory::BindingCoinText()
{
	FString CoinString = FString::Printf(TEXT("%d"), Player->GetPlayerCoin());
	CoinText->SetText(FText::FromString(CoinString));
}



