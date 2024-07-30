// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "BTTask_Death.generated.h"


UCLASS()
class UE5_HORRORSGAME_API UBTTask_Death : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTTask_Death();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)override;

private:
	bool MontageHasFinished(AEnemyCharacter *const NPC);

};
