// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AAI_Controller::AAI_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupPerceptionSystem();
}

void AAI_Controller::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		SightConfig->SightRadius = 500.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AAI_Controller::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
{
	if (auto *const ch = Cast<APlayerCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}

FRotator AAI_Controller::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.f, 0.f, 0.f);
	}
	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAI_Controller::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemyCharacter *const Enemy = Cast<AEnemyCharacter>(InPawn))
	{
		if (UBehaviorTree *const tree = Enemy->GetBehaviorTree())
		{
			UBlackboardComponent *BlackBoard;
			UseBlackboard(tree->BlackboardAsset, BlackBoard);
			Blackboard = BlackBoard;
			RunBehaviorTree(tree);
		}
	}
}

void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AAI_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
