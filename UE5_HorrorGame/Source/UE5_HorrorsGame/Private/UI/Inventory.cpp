// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Component/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/InventorySlot.h"
#include "Object/Item/ItemBase.h"

void UInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Player = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		InventoryComp = Player->GetInventory();

		if (InventoryComp)
		{
			InventoryComp->OnInventoryUpdated.AddUObject(this, &UInventory::RefreshInventory);
		}
	}
}

bool UInventory::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	return false;
}

// Add to Viewport 할 때 불리는 함수`
void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventory::RefreshInventory()
{
	if(InventoryComp && InventorySlotClass)
	{
		WrapBox->ClearChildren();

		for (auto const& InventoryItem : InventoryComp->GetItemInventory())
		{
			auto ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			WrapBox->AddChildToWrapBox(ItemSlot);
			if (InventoryItem->Amount <= 0)
			{
				WrapBox->RemoveChild(ItemSlot);
			}
		}
	}
}