// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::BeginFocus()
{
	if(Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void ATestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void ATestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on Interface test Actor"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, FString::Printf(TEXT("Interaing")), true);
}

void ATestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on Interface test Actor"));
}

void ATestActor::Interact(APlayableCharacter *PlayableCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on Interface test Actor"));
}

