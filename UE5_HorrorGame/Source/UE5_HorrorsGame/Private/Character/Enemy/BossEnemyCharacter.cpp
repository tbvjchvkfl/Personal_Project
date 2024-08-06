// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BossEnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "UI/BossHealthBar.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Anim/BossEnemyAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AI/BossEnemyController.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 200.0f;
	CurHealth = MaxHealth;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
	CollisionBox->SetupAttachment(GetMesh(), "AttackHand");
	CollisionBox->InitBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	BossIsDead = false;
}

void ABossEnemyCharacter::PlayAttackAnim()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}

void ABossEnemyCharacter::PlayHitAnim()
{
	if (HitMontage)
	{
		PlayAnimMontage(HitMontage);
	}
}

void ABossEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	BossAnim = Cast<UBossEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemyCharacter::OnAttackOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABossEnemyCharacter::OnAttackOverlapEnd);
}

void ABossEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HUD->GetInGameHUDWidget()->SetBossHealthBar(this);
}

void ABossEnemyCharacter::Die(float KillingDamage, FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)
{
	CurHealth = FMath::Min(0, CurHealth);
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}
	if (Controller)
	{
		Controller->UnPossess();
	}
	PlayAnimMontage(DeathMontage);
	GetWorldTimerManager().SetTimer(KillTimer, this, &ABossEnemyCharacter::DeathAnimationEnd, PlayAnimMontage(DeathMontage), false);

	PlayerCharacter->bIsBossKill = true;
	BossIsDead = true;
}

void ABossEnemyCharacter::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	HUD->GetInGameHUDWidget()->HideBossHealthBar();
	this->Destroy();
}

float ABossEnemyCharacter::TakeDamage(float Damage, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	const float CurrentDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurHealth -= CurrentDamage;
	if (CurHealth <= 0)
	{
		BossAnim->CheckHitAnim();
		Die(CurrentDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		BossAnim->HitAnim();
	}

	return CurrentDamage;
}

void ABossEnemyCharacter::OnAttackOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto const Target = Cast<APlayerCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(Target, 60.0f, NULL, this, UDamageType::StaticClass());
	}
}

void ABossEnemyCharacter::OnAttackOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto const Target = Cast<APlayerCharacter>(OtherActor))
	{

	}
}

void ABossEnemyCharacter::MeleeAttackWithSweepTrace()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * 200.0f;
	FCollisionQueryParams Params;

	if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(200.0f), Params))
	{
		if (HitResult.bBlockingHit)
		{
			if (auto Target = Cast<APlayerCharacter>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(Target, 50.0f, NULL, this, UDamageType::StaticClass());
			}
		}
	}
}

void ABossEnemyCharacter::DoSkillAction()
{
	if (ShootProjectile)
	{
		if (GetWorld())
		{
			auto StartLocation = GetActorLocation() + FVector(0.0f, 0.0f, 80.0f);
			auto StartRotation = GetControlRotation();
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<AProjectile>(ShootProjectile, StartLocation, StartRotation, SpawnParams);
		}
	}
}

void ABossEnemyCharacter::AttackStart()
{
	CollisionBox->SetCollisionProfileName("Fist");
	CollisionBox->SetNotifyRigidBodyCollision(true);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABossEnemyCharacter::AttackEnd()
{
	CollisionBox->SetCollisionProfileName("Fist");
	CollisionBox->SetNotifyRigidBodyCollision(false);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
