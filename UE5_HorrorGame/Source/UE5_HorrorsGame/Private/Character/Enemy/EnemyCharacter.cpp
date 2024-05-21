// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
	HandCollisionBox->SetupAttachment(GetMesh(), "HandR_Socket");
	
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

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HandCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackOverlapBegin);
	HandCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackOverlapEnd);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Enemy Is Attack")), true);
	}
}

void AEnemyCharacter::OnAttackOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{

}
