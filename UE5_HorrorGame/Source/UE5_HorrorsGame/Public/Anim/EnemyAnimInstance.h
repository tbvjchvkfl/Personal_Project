// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UEnemyAnimInstance : public UAnimInstance
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

	void HitAnim();
	void CheckHitAnim();
private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AEnemyCharacter *EnemyCharacter;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *HitAnimation;

};
