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

	virtual void BeginPlay() override;
	//virtual void OnPossess(APawn* Pawn)override;
	virtual void Tick(float DeltaSeconds)override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
	void OnPawnDetected(TArray<AActor*> DetectedPawns);

	float AISightRadius = 500.0f;
	float AISightAge = 5.0f;
	float AILoseSightRadius = AISightRadius + 50.0f;
	float AIFieldOfView = 90.0f;

	class UAISenseConfig_Sight* SightConfig;

private:
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;
};
