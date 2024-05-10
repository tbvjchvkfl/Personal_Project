// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/InventorySlot.h"
#include "Components/WrapBox.h"

// Add to Viewport 할 때 불리는 함수
void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UInventory::AddItemToInventory()
{
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		InventoryItems = Player->GetInventoryItem();

		for (int i = 0; i < InventoryItems.Num(); i++)
		{
			if (InventoryClass)
			{
				SlotWidget = Cast<UInventorySlot>(CreateWidget(GetWorld(), InventoryClass));
				if (SlotWidget)
				{
					SlotWidget->SetItemSlot(InventoryItems[i]);
					if (Player->EnableAddItem)
					{
						WrapBox->AddChild(SlotWidget);
					}
				}
			}
		}
	}
}

void UInventory::AddToSlot()
{
	if (InventoryClass)
	{
		if (SlotWidget)
		{
			WrapBox->AddChild(SlotWidget);
		}
	}
}
