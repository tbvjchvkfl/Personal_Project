// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Interface/PickUpInterface.h"
#include "Interface/InteractionInterface.h"
#include "Data/ItemStruct.h"
#include "PickUpItem.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class APlayerCharacter;
class UDataTable;
class UItemBase;

UCLASS()
class UE5_HORRORSGAME_API APickUpItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	
	/*UPROPERTY(EditAnywhere, Category = "PickupItem")
	FDataTableRowHandle ItemRowHandle;

	FItemData* ItemRow;*/

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APickUpItem();

	void InitializePickUp(const TSubclassOf<UItemBase> BaseClass, const int32 InAmount);

	FORCEINLINE UItemBase *GetItemData() { return ItemReference; }

	virtual void BeginFocus()override;
	virtual void EndFocus()override;
	
	/*UFUNCTION(BlueprintCallable)
	virtual void Interact(APlayerCharacter* player) override;*/

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, Category = "ItemComp")
	UStaticMeshComponent *ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "ItemComp")
	USphereComponent *CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "ItemComp")
	UDataTable *ItemDataTable;

	UPROPERTY(EditAnywhere, Category = "ItemComp")
	FName DesiredItemID;

	UPROPERTY(VisibleAnywhere, Category = "ItemComp")
	UItemBase *ItemReference;

	UPROPERTY(EditAnywhere, Category = "ItemComp")
	int32 ItemAmount;

	UPROPERTY(VisibleAnywhere, Category = "ItemComp")
	FInteractableData InstanceInteractable;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;

	virtual void BeginInteraction()override;
	virtual void EndInteraction()override;
	virtual void Interaction(APlayerCharacter *Player)override;
	
	void UpdateInteractableData();

	void TakePickUp(APlayerCharacter *Taker);


#if WITH_EDITOR
	// 에디터에서 마지막으로 조정한 항목에 대한 참조를 저장
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif
};
