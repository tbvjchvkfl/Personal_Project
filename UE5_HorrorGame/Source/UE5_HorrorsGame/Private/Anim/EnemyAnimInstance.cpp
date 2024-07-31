// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/EnemyAnimInstance.h"
#include "Character/Enemy/EnemyCharacter.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (EnemyCharacter == nullptr)
	{
		EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
	}
	if (EnemyCharacter)
	{
		MoveSpeed = EnemyCharacter->GetVelocity().Length();
	}
	
}

void UEnemyAnimInstance::HitAnim()
{
	if (Montage_GetIsStopped(HitAnimation))
	{
		Montage_Play(HitAnimation);
	}
}

void UEnemyAnimInstance::CheckHitAnim()
{
	if (!Montage_GetIsStopped(HitAnimation))
	{
		Montage_Stop(0.1f, HitAnimation);
	}
}
