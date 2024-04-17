// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
#include "Engine.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

ACollisionActor::ACollisionActor()
{
	mDamage = 0.5f;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obj"));
	RootComponent = mStaticMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(100.0f);
	CollisionSphere->SetupAttachment(RootComponent);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACollisionActor::OnOverlapBegin);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	ParticleFX = ParticleAsset.Object;
}

void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollisionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{
	if (OtherActor->IsA(APlayableCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Collision Touch!!"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX, GetActorLocation());
		Destroy();
	}
}
