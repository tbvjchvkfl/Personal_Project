// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 200.0f;
	CurHealth = MaxHealth;
}

void ABossEnemyCharacter::PlayAttackAnim()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}

void ABossEnemyCharacter::PlaySkillAnim()
{
	if (SkillMontage)
	{
		PlayAnimMontage(SkillMontage);
	}
}

void ABossEnemyCharacter::PlayDeathAnim()
{
	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
}

void ABossEnemyCharacter::PlayHitAnim()
{
	if (HitMontage)
	{
		PlayAnimMontage(HitMontage);
	}
}

bool ABossEnemyCharacter::SkillCoolDown(float CoolTime)
{
	if (!bIsCoolTime)
	{
		bIsCoolTime = true;
		GetWorldTimerManager().SetTimer(Timer, this, &ABossEnemyCharacter::ResetCoolDown, 5.0f, false);
		return true;
	}
	
	return false;
}

void ABossEnemyCharacter::ResetCoolDown()
{
	bIsCoolTime = false;
	GetWorldTimerManager().ClearTimer(Timer);
}

void ABossEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ABossEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossEnemyCharacter::Die(float KillingDamage, FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)
{
	CurHealth = FMath::Min(0, CurHealth);
	this->Destroy();
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
