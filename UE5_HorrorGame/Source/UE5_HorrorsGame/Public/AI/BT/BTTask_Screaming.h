// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Screaming.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UBTTask_Screaming : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_Screaming();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)override;

private:
	bool MontageHasFinished(AEnemyCharacter *const NPC);
};
