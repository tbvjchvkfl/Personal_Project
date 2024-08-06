// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BossEnemyCharacter.generated.h"

class UBehaviorTree;
class UBossHealthBar;
class UBoxComponent;
class APlayerCharacter;
class AHorrorsHUD;
class AProjectile;
class UBossEnemyAnimInstance;

UCLASS()
class UE5_HORRORSGAME_API ABossEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UBossEnemyAnimInstance *BossAnim;

	APlayerCharacter *PlayerCharacter;

	bool BossIsDead;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	ABossEnemyCharacter();
	
	void PlayAttackAnim();
	void PlayHitAnim();
	
	void MeleeAttackWithSweepTrace();

	void DoSkillAction();

	void AttackStart();
	void AttackEnd();

	FORCEINLINE UBehaviorTree *GetBehaviorTree() const { return Tree; }
	FORCEINLINE UAnimMontage *GetAttackAnimation() const { return AttackMontage; }
	FORCEINLINE UAnimMontage *GetSkillAnimation() const { return SkillMontage; }
	FORCEINLINE UAnimMontage *GetDeathAnimation() const { return DeathMontage; }
	FORCEINLINE UAnimMontage *GetHitAnimation() const { return HitMontage; }

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowAbstract = "true"))
	UBehaviorTree *Tree;

	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *CollisionBox;

	class AHorrorsHUD *HUD;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> ShootProjectile;

	TSubclassOf<UBossHealthBar> HealthBarUI;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser);

	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)override;

	void DeathAnimationEnd();
private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *SkillMontage;

	FTimerHandle KillTimer;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);

};
