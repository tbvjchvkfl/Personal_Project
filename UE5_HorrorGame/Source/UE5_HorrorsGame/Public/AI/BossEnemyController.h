// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossEnemyController.generated.h"

class UBehaviorTreeComponent;
class UAISenseConfig_Sight;
class ABossEnemyCharacter;

UCLASS()
class UE5_HORRORSGAME_API ABossEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	
	UPROPERTY()
	ABossEnemyCharacter *BossCharacter;

	UPROPERTY()
	APlayerCharacter *TargetCharacter;

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

	UPROPERTY(EditAnywhere, Category = "OwnerCharacter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABossEnemyCharacter> OwnerCharacter;

	UPROPERTY(EditAnywhere, Category = "OwnerCharacter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerCharacter> Target;

	UPROPERTY(EditAnywhere, Category = "OwnerCharacter", meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(VisibleAnywhere, Category = "OwnerCharacter", meta = (AllowPrivateAccess = "true"))
	AHorrorsHUD *HUD;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	
	UFUNCTION()
	void OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus);

	virtual void OnPossess(APawn *InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
