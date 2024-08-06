// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Data/ItemStruct.h"
#include "PickUpItem.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class APlayerCharacter;
class UDataTable;
class UItemBase;
class AHorrorsHUD;

UCLASS()
class UE5_HORRORSGAME_API APickUpItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	AHorrorsHUD *HUD;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APickUpItem();
	FORCEINLINE UItemBase *GetItemData() { return ItemReference; }

	

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

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;
	virtual void Interaction(APlayerCharacter *Player)override;
	
	void InitializePickUp(const TSubclassOf<UItemBase> BaseClass);
	void TakePickUp(APlayerCharacter *Taker);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);


#if WITH_EDITOR
	// 에디터에서 마지막으로 조정한 항목에 대한 참조를 저장
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif
};
