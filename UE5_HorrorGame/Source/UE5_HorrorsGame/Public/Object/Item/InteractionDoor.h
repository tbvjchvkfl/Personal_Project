// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "InteractionDoor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UBoxComponent;

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
