// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_Screaming.h"
#include "AI/AI_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"


UBTTask_Screaming::UBTTask_Screaming()
{
	NodeName = TEXT("Screaming");
}

EBTNodeResult::Type UBTTask_Screaming::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());

	if (auto *const InterfaceCombat = Cast<IEnemyCombatInterface>(NPC))
	{
		if (MontageHasFinished(NPC))
		{
			InterfaceCombat->Execute_ScreamAction(NPC);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Screaming::MontageHasFinished(AEnemyCharacter *const NPC)
{
	return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetScreamMontage());
}
