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
    auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    auto *const Controller = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());

    auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn());

    auto *const Target = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    //공격 함수 호출
    AttackSkill(Boss, Controller, Target);

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

void UBTTask_Skill::AttackSkill(ABossEnemyCharacter *const Boss, ABossEnemyController* const BossController, APlayerCharacter *Player)
{
    auto BossEnemyAnimInstance = Cast<UBossEnemyAnimInstance>(Boss->GetMesh()->GetAnimInstance());

    if (Boss->SkillCoolDown(CoolDown) && Boss->GetDistanceTo(Player) > AttackRange)
    {
        BossController->StopMovement();
        BossEnemyAnimInstance->DoSkill();
    }
}