// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BossEnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossEnemyController::ABossEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
	BossSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	if (BossSightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		BossSightConfig->SightRadius = 1500.0f;
		BossSightConfig->LoseSightRadius = BossSightConfig->SightRadius + 25.0f;
		BossSightConfig->PeripheralVisionAngleDegrees = 90.0f;
		BossSightConfig->SetMaxAge(5.0f);
		BossSightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;

		BossSightConfig->DetectionByAffiliation.bDetectEnemies = true;
		BossSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		BossSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*BossSightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABossEnemyController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*BossSightConfig);
	}
}

FRotator ABossEnemyController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void ABossEnemyController::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
{
	if (auto *const ch = Cast<APlayerCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("IsSearch", Stimulus.WasSuccessfullySensed());
	}
}

void ABossEnemyController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	if (ABossEnemyCharacter *const Boss = Cast<ABossEnemyCharacter>(InPawn))
	{
		if (UBehaviorTree *const Tree = Boss->GetBehaviorTree())
		{
			UBlackboardComponent *BlackBoard;
			UseBlackboard(Tree->BlackboardAsset, BlackBoard);
			Blackboard = BlackBoard;
			RunBehaviorTree(Tree);
		}
	}
}

void ABossEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void ABossEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
