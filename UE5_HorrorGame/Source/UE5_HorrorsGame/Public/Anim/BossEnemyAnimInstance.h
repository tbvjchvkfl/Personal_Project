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

	FORCEINLINE bool GetCoolTime()const { return bIsCoolTime; }
	void AttackCoolDown(float CoolTime);
	void DoSkill(float CoolDown);
	void CheckHitAnim();
	void HitAnim();
private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsScreaming;

	UPROPERTY(VisibleAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bIsCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABossEnemyCharacter *BossCharacter;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *Skill;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *HitAnimation;

	FTimerHandle TimerHandle;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
