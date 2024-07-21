// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor/Projectile.h"
#include "Components/SphereComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->InitSphereRadius(200.0f);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(Target);
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovetoTarget(DeltaTime);
}

void AProjectile::MovetoTarget(float Power)
{
	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * ProjectileSpeed + Power));
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (auto* const PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(PlayerCharacter, DamageRate, NULL, this, UDamageType::StaticClass());
	}
	this->Destroy();
}

void AProjectile::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{

}

