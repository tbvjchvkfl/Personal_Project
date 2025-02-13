// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "InteractionDoor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UBoxComponent;
class ALastDoorTrigger;
class AHorrorsHUD;

UCLASS()
class UE5_HORRORSGAME_API AInteractionDoor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent *LeftDoor;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent *RightDoor;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	TSubclassOf<ALastDoorTrigger> DoorTriggerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsInteract;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AInteractionDoor();

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, Category = "ItemComp")
	UBoxComponent *CollisionBox;

	ALastDoorTrigger *DoorTrigger;

	AHorrorsHUD *HUD;

	FTimerHandle Timerhandle;
	float LeftRotRate;
	float RightRotRate;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void Interaction(class APlayerCharacter *Player);
	void OpenDoor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
