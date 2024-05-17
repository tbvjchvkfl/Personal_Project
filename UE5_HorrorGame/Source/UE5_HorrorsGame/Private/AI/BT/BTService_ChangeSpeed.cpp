// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTService_ChangeSpeed.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "AI/AI_Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (auto const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn()))
		{
			NPC->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}
}
