// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_MeleeAttack.h"
#include "Interface/EnemyCombatInterface.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/AI_Controller.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    auto const *const Controller = OwnerComp.GetAIOwner();
    if (auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn()))
    {
        if (auto *const iCombat = Cast<IEnemyCombatInterface>(NPC))
        {
            if (MontageHasFinished(NPC))
            {
                iCombat->Execute_MeleeAttack(NPC);
            }
        }
    }
    if (auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn()))
    {
        if (BossMontageHasFinished(Boss))
        {
            Boss->PlayAttackAnim();
        }
    }
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

//EBTNodeResult::Type UBTTask_MeleeAttack::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
//{
//    auto const *const Controller = OwnerComp.GetAIOwner();
//    auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn());
//    if (BossMontageHasFinished(Boss))
//    {
//        return EBTNodeResult::Succeeded;
//    }
//}

bool UBTTask_MeleeAttack::MontageHasFinished(AEnemyCharacter *const NPC)
{
    return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetAttackMontage());
}

bool UBTTask_MeleeAttack::BossMontageHasFinished(ABossEnemyCharacter *const Boss)
{
    return Boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Boss->GetAttackAnimation());
}
