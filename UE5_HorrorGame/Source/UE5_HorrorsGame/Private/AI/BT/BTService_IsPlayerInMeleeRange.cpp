// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTService_IsPlayerInMeleeRange.h"
#include "AI/AI_Controller.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto const *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());

	auto const *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), NPC->GetDistanceTo(Player) <= MeleeRange);
}