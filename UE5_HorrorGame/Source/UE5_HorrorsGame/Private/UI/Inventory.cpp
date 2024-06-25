// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Component/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/InventorySlot.h"

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
	/*Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));*/
	//CoinText->SetText(FText::AsNumber(Player->GetPlayerCoin()));
}

void UInventory::RefreshInventory()
{
	if(InventoryComp && InventorySlotClass)
	{
		for (auto const& InventoryItem : InventoryComp->GetItemInventory())
		{
			auto ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
			//ItemSlot->SetItemReference(InventoryComp);

			WrapBox->AddChildToWrapBox(ItemSlot);
		}
	}
}

//void UInventory::AddItemToInventory()
//{
//	if (Player)
//	{
//		InventoryItems = Player->GetInventoryItem();
//		for (int i = 0; i < InventoryItems.Num(); i++)
//		{
//			if (InventoryClass)
//			{
//				SlotWidget = Cast<UInventorySlot>(CreateWidget(GetWorld(), InventoryClass));
//				if (SlotWidget)
//				{
//					SlotWidget->SetItemSlot(InventoryItems[i]);
//					WrapBox->AddChild(SlotWidget);
//				}
//			}
//		}
//	}
//}

//void UInventory::RemoveItem()
//{
//	for (int i = 0; i < InventoryItems.Num(); i++)
//	{
//		if (InventoryItems[i]->Amount < 1)
//		{
//			WrapBox->RemoveChild(SlotWidget);
//		}
//	}
//}