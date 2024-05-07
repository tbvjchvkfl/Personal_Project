// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI_Controller.h"
#include "Character/Enemy/EnemyCharacter.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const &ObjectInitializer)
{
	NodeName = "Find Random Location In NavMeesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	if (AAI_Controller *const Controll = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto *const NPC = Controll->GetPawn())
		{
			FVector const Origin = NPC->GetActorLocation();
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
	
}
