// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossEnemyAnimInstance.generated.h"

class ABossEnemyCharacter;

UCLASS()
class UE5_HORRORSGAME_API UBossEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	void DoSkill();
private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsScreaming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABossEnemyCharacter *BossCharacter;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *Skill;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
