#include "Component/InventoryComponent.h"
#include "Object/Item/ItemBase.h"
#include "UI/InGameHUD.h"
#include "UI/HorrorsHUD.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CoinInventory = 0;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	CoinInventory = 0;
	UIComp = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(UItemBase *Item)
{
	if (Item->ItemType == EItemType::Coin)
	{
		CoinInventory += Item->Amount;
		UIComp->GetInGameHUDWidget()->SetCoinText(this);
		UIComp->GetInGameHUDWidget()->PlayCoinAnimation();
	}
	else
	{
		ItemInventory.Add(Item);
	}

	OnInventoryUpdated.Broadcast();
}

