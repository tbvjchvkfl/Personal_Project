// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_Skill.h"
#include "AI/BossEnemyController.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_Skill::UBTTask_Skill()
{
}

EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    auto *const Controller = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());

    if (auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn()))
    {
        if (BossMontageHasFinished(Boss))
        {
            Boss->PlaySkillAnim();
        }
    }
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

bool UBTTask_Skill::BossMontageHasFinished(ABossEnemyCharacter *const Boss)
{
    return Boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Boss->GetSkillAnimation());
}
