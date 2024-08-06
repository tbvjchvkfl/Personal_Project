// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/InteractionDoorSingle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AInteractionDoorSingle::AInteractionDoorSingle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(CollisionBox);
}


void AInteractionDoorSingle::Interaction(APlayerCharacter *Player)
{
	GetWorldTimerManager().SetTimer(Timerhandle, this, &AInteractionDoorSingle::OpenDoor, 0.01f, true);
}

void AInteractionDoorSingle::OpenDoor()
{
	if (RotRate >= 90.0f)
	{
		GetWorldTimerManager().PauseTimer(Timerhandle);
		GetWorldTimerManager().ClearTimer(Timerhandle);
	}
	else
	{
		RotRate += 2.0f;
		Door->SetRelativeRotation(FRotator(0.0f, RotRate, 0.0f));
	}
}

void AInteractionDoorSingle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractionDoorSingle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

