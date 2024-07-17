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
	UBehaviorTree *GetBehaviorTree() const { return Tree; }

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
	UPROPERTY(EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage *SkillMontage;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
