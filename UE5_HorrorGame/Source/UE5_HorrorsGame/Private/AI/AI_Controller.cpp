// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/Enemy/EnemyCharacter.h"

AAI_Controller::AAI_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AAI_Controller::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
{
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

	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("All Systems Set!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Component"));
	}
}

void AAI_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
