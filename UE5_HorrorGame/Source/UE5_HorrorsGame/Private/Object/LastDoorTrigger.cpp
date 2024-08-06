// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LastDoorTrigger.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "UI/GameQuestUI.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ALastDoorTrigger::ALastDoorTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
}

void ALastDoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	EnableDoorInteraction = true;
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALastDoorTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALastDoorTrigger::OnOverlapEnd);
}

void ALastDoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player)
	{
		if (Player->bIsBossKill && Player->KillCount >= 3)
		{
			EnableDoorInteraction = true;
		}
	}
}

void ALastDoorTrigger::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (auto *const Ch = Cast<APlayerCharacter>(OtherActor))
	{
		EnableDoorInteraction = false;
	}
}

void ALastDoorTrigger::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
}

