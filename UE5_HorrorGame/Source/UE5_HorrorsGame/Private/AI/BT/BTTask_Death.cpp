// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_Death.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/AI_Controller.h"

UBTTask_Death::UBTTask_Death()
{
	NodeName = TEXT("Death");
}

EBTNodeResult::Type UBTTask_Death::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto *const Controller = OwnerComp.GetAIOwner();

	auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());
	if (auto *const iCombat = Cast<IEnemyCombatInterface>(NPC))
	{
		if (MontageHasFinished(NPC))
		{
			iCombat->Execute_DeathAnim(NPC);
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Death::MontageHasFinished(AEnemyCharacter *const NPC)
{
	return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetAttackMontage());
}
