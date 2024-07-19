// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BossEnemyCharacter.generated.h"

class UBehaviorTree;
class APlayerCharacter;
class AHorrorsHUD;

UCLASS()
class UE5_HORRORSGAME_API ABossEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	ABossEnemyCharacter();
	
	void PlayAttackAnim();
	void PlaySkillAnim();
	void PlayDeathAnim();
	void PlayHitAnim();

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

	class AHorrorsHUD *HUD;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser) override;

	void MeleeAttackWithSweepTrace();

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *SkillMontage;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
