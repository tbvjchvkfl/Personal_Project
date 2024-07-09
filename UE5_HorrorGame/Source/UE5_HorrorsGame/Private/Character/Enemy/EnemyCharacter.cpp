// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"
#include "Object/Item/PickUpItem.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
	HandCollisionBox->SetupAttachment(GetMesh(), "HandR_Socket");

	MaxHealth = 100.0f;
	CurHealth = MaxHealth;
}

UBehaviorTree *AEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}

UAnimMontage *AEnemyCharacter::GetScreamMontage() const
{
	return ScreamMontage;
}

UAnimMontage *AEnemyCharacter::GetAttackMontage() const
{
	return AttackMontage;
}

int AEnemyCharacter::MeleeAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
	return 0;
}

int AEnemyCharacter::ScreamAction_Implementation()
{
	if (ScreamMontage)
	{
		PlayAnimMontage(ScreamMontage);
	}
	return 0;
}

void AEnemyCharacter::AttackStart() const
{
	HandCollisionBox->SetCollisionProfileName("Fist");
	HandCollisionBox->SetNotifyRigidBodyCollision(true);
	HandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AEnemyCharacter::AttackEnd() const
{
	HandCollisionBox->SetCollisionProfileName("Fist");
	HandCollisionBox->SetNotifyRigidBodyCollision(false);
	HandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyCharacter::MeleeAttackWithSweepTrace()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * 200.0f;
	FCollisionQueryParams Params;

	if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.0f), Params))
	{
		if (HitResult.bBlockingHit)
		{
			if (auto TargetCharacter = Cast<APlayerCharacter>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(TargetCharacter, 30.0f, NULL, this, UDamageType::StaticClass());
			}
		}
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//HandCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackOverlapBegin);
	//HandCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackOverlapEnd);
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Target = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target->KillCount >= 3)
	{
		//HUD->ShowResult();
	}
}

void AEnemyCharacter::Die(float KillingDamage, FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)
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
	float DeathAnimDuration = PlayAnimMontage(DeathMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::DeathAnimationEnd, DeathAnimDuration, false);
	Target->KillCount++;
	
}

void AEnemyCharacter::DeathAnimationEnd()
{
	auto Loc = GetActorLocation() + FVector(0.0f, 0.0f, -80.0f);
	GetWorld()->SpawnActor<APickUpItem>(DropItemClass, Loc, GetActorRotation());
	this->Destroy();
}

void AEnemyCharacter::OnAttackOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto const Enemy = Cast<APlayerCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(Enemy, 30.0f, NULL, this, UDamageType::StaticClass());
	}
}

void AEnemyCharacter::OnAttackOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
}
