// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"

/**
 * 
 */


class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class UE5_HORRORS_GAME_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
public:

	AAI_Controller();
	
	float AISightRadius = 500.0f;
	float AISightAge = 5.0f;
	float AILoseSightRadius = AISightRadius + 25.0f;
	float AIFieldOfView = 90.0f;

	class UAISenseConfig_Sight* SightConfig;

private:
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
	virtual FRotator GetControlRotation() const override;
};
