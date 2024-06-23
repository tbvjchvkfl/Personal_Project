// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Item/PickUpItem.h"
#include "Components/SphereComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Object/Item/ItemBase.h"

APickUpItem::APickUpItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(200.0f);
	CollisionSphere->SetupAttachment(RootComponent);
	
	// 데이터 테이블 바인딩
	/*ConstructorHelpers::FObjectFinder<UDataTable>DataTable(TEXT("DataTable'/Game/HorrorsGame/Data/ItemDataTable.ItemDataTable'"));
	
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
		ItemRowHandle.DataTable = ItemDataTable;
	}*/
}

void APickUpItem::BeginPlay()
{
	Super::BeginPlay();

	InitializePickUp(UItemBase::StaticClass(), ItemAmount);
	// 데이터 테이블 바인딩
	//ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
}

void APickUpItem::InitializePickUp(const TSubclassOf<UItemBase> BaseClass, const int32 InAmount)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData *ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);
		
		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;

		InAmount <= 0 ? ItemReference->SetAmount(1) : ItemReference->SetAmount(InAmount);

		ItemMesh->SetStaticMesh(ItemData->AssetData.Mesh);

		UpdateInteractableData();
	}
}

void APickUpItem::UpdateInteractableData()
{
	InstanceInteractable.InteractionType = EInteractionType::Pickup;
	InstanceInteractable.Name = ItemReference->TextData.Name;
	InstanceInteractable.Amount = ItemReference->Amount;
	InteractableData = InstanceInteractable;
}

void APickUpItem::BeginFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void APickUpItem::EndFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(false);
	}
}

void APickUpItem::Interaction(class APlayerCharacter *Player)
{
	if (Player)
	{
		TakePickUp(Player);
	}
}

void APickUpItem::TakePickUp(APlayerCharacter *Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			/*if (UInventory *PlayerInventory = Taker->GetInventory())
			{
				
			}*/
		}
	}
}

void APickUpItem::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickUpItem, DesiredItemID))
	{
		if (ItemDataTable)
		{
			const FString ContextString{ DesiredItemID.ToString() };

			if (const FItemData *ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				ItemMesh->SetStaticMesh(ItemData->AssetData.Mesh);
			}
		}
	}
}


void APickUpItem::BeginInteraction()
{

}

void APickUpItem::EndInteraction()
{

}

//void APickUpItem::Interact(APlayerCharacter* player)
//{
//	
//	if (player)
//	{
//		if (ItemRow)
//		{
//			player->AddItem(ItemRow);
//		}
//	}
//
//	this->Destroy();
//}