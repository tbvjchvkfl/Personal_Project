// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_MeleeAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)override;

	//EBTNodeResult::Type TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;


private:
	UPROPERTY(EditAnywhere, Category = "MeleeAttack", meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	bool MontageHasFinished(AEnemyCharacter *const NPC);
	bool BossMontageHasFinished(ABossEnemyCharacter *const Boss);
};
