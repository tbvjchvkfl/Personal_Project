// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{
	MaxHealth = 200.0f;
	CurHealth = MaxHealth;
}

void ABossEnemyCharacter::BeginPlay()
{
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ABossEnemyCharacter::Tick(float DeltaTime)
{
}

void ABossEnemyCharacter::Die(float KillingDamage, FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)
{
}

void ABossEnemyCharacter::MeleeAttackWithSweepTrace()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * 200.0f;
	FCollisionQueryParams Params;

	if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.0f), Params))
	{
		if (HitResult.bBlockingHit)
		{
			if (auto Target = Cast<APlayerCharacter>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(Target, 30.0f, NULL, this, UDamageType::StaticClass());
			}
		}
	}
}
