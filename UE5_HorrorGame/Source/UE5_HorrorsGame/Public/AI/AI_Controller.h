// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;

UCLASS()
class UE5_HORRORSGAME_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AAI_Controller();
	virtual FRotator GetControlRotation() const override;
	

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(Transient)
	UBlackboardComponent *BlackboardComp;

	UPROPERTY(Transient)
	UBehaviorTreeComponent *BehaviorComp;

	UAISenseConfig_Sight *SightConfig;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus);

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void OnPossess(APawn *InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


};
