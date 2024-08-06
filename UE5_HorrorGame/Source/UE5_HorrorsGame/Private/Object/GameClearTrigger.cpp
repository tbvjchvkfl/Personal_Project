// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/GameClearTrigger.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/HorrorsHUD.h"

AGameClearTrigger::AGameClearTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	
}

void AGameClearTrigger::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGameClearTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGameClearTrigger::OnOverlapEnd);
}

void AGameClearTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameClearTrigger::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (auto *const Player = Cast<APlayerCharacter>(OtherActor))
	{
		FString GameClearString = FString::Printf(TEXT("GAME CLEAR"));
		HUD->ShowResult(GameClearString);
	}
}

void AGameClearTrigger::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
	this->Destroy();
}

