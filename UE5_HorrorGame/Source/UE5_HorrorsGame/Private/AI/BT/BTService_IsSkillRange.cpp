// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTService_IsSkillRange.h"
#include "AI/BossEnemyController.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_IsSkillRange::UBTService_IsSkillRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is In Skill Range");
}

void UBTService_IsSkillRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto const *const Controller = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());

	auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn());

	auto *const Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), IsDoingSkill(Boss, Player));
}

bool UBTService_IsSkillRange::IsDoingSkill(ABossEnemyCharacter *BossEnemy, APlayerCharacter *Target)
{
	if (BossEnemy->GetDistanceTo(Target) >= SkillRange && BossEnemy->SkillCoolDown(SkillDelay))
	{
		return true;
	}
	return false;
}
