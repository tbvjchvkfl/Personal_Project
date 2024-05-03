// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "TestActor.generated.h"

UCLASS()
class UE5_HORRORS_GAME_API ATestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Test Actor")
	class UStaticMeshComponent *Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus()override;
	virtual void EndFocus()override;
	virtual void BeginInteract()override;
	virtual void EndInteract()override;
	virtual void Interact(APlayableCharacter *PlayableCharacter)override;

};
