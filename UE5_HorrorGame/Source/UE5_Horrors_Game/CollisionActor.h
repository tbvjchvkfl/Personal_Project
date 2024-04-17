// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "CollisionActor.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API ACollisionActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	ACollisionActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	float mDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "MyItem")
	UParticleSystem* ParticleFX;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
