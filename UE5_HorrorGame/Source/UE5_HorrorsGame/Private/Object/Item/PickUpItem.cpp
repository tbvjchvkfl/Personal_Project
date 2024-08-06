// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Item/PickUpItem.h"
#include "Components/SphereComponent.h"
#include "Component/InventoryComponent.h"
#include "Object/Item/ItemBase.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"

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

	InitializePickUp(UItemBase::StaticClass());
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OnOverlapBegin);

	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APickUpItem::OnOverlapEnd);
	// 데이터 테이블 바인딩
	//ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
}

void APickUpItem::InitializePickUp(const TSubclassOf<UItemBase> BaseClass)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData *ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);
		
		ItemReference->ID = ItemData->ID;
		ItemReference->Amount = ItemData->Amount;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;

		ItemMesh->SetStaticMesh(ItemData->AssetData.Mesh);
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
			if (UInventoryComponent *PlayerInventory = Taker->GetInventory())
			{
				PlayerInventory->AddItem(ItemReference);
				Destroy();
			}
		}
	}
}

void APickUpItem::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto Character = Cast<APlayerCharacter>(OtherActor))
	{
		HUD->GetInGameHUDWidget()->ShowInteractUI();
	}
}

void APickUpItem::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto Character = Cast<APlayerCharacter>(OtherActor))
	{
		HUD->GetInGameHUDWidget()->HideInteractUI();
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

