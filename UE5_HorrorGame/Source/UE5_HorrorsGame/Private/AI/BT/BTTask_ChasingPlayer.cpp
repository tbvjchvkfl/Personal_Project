// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_ChasingPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI_Controller.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasingPlayer::UBTTask_ChasingPlayer()
{
	NodeName = "ChasingPlayer";
}

EBTNodeResult::Type UBTTask_ChasingPlayer::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	if(auto *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
