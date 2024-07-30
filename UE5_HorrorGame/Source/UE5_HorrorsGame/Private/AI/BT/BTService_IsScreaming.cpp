// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTService_IsScreaming.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI_Controller.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsScreaming::UBTService_IsScreaming()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Screaming");
}

void UBTService_IsScreaming::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto const *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());
	auto const *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Count >= Controller->DetectCount);
}
