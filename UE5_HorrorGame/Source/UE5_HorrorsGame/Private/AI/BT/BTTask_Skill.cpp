// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_Skill.h"
#include "AI/BossEnemyController.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Anim/BossEnemyAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_Skill::UBTTask_Skill()
{
}

EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto *const Controller = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());

    auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn());

    auto *const BossEnemyAnimInstance = Cast<UBossEnemyAnimInstance>(Boss->GetMesh()->GetAnimInstance());

    auto *const Target = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (!CheckSkill(OwnerComp, Boss, Target, BossEnemyAnimInstance))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }
    else
    {
        AttackSkill(Controller, BossEnemyAnimInstance);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
}

void UBTTask_Skill::AttackSkill(ABossEnemyController* const BossController, UBossEnemyAnimInstance* const BossAnim)
{
    BossController->StopMovement();
    BossAnim->DoSkill(SkillDelay);
}

bool UBTTask_Skill::CheckSkill(UBehaviorTreeComponent &TreeComp, ABossEnemyCharacter *const Boss, APlayerCharacter *Player, UBossEnemyAnimInstance *const BossAnimInstance)
{
    if (Boss->GetDistanceTo(Player) >= SkillRange && !BossAnimInstance->GetCoolTime())
    {
        TreeComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        return true;
    }
    else
    {
        TreeComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        return false;
    }
    
}
