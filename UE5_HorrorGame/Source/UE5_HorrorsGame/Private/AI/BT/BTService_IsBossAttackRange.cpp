// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTService_IsBossAttackRange.h"
#include "AI/BossEnemyController.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsBossAttackRange::UBTService_IsBossAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is In Boss's Attack Range");
}

void UBTService_IsBossAttackRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto *const BossController = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());
	auto *const Boss = Cast<ABossEnemyCharacter>(BossController->GetPawn());

	auto const *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Boss->GetDistanceTo(Player) <= AttackRange);
}
