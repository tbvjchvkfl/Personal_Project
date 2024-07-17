// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossEnemyController.generated.h"

class UBehaviorTreeComponent;
class UAISenseConfig_Sight;

UCLASS()
class UE5_HORRORSGAME_API ABossEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	ABossEnemyController();
	virtual FRotator GetControlRotation() const override;

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(Transient)
	UBehaviorTreeComponent *BehaviorComp;

	UAISenseConfig_Sight *BossSightConfig;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	
	UFUNCTION()
	void OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus);

	virtual void OnPossess(APawn *InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
