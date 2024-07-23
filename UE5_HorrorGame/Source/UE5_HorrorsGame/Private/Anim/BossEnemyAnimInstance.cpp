// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/BossEnemyAnimInstance.h"
#include "Character/Enemy/BossEnemyCharacter.h"

void UBossEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BossCharacter = Cast<ABossEnemyCharacter>(TryGetPawnOwner());
}

void UBossEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!BossCharacter)
	{
		BossCharacter = Cast<ABossEnemyCharacter>(TryGetPawnOwner());
	}
	if (BossCharacter)
	{
		MoveSpeed = BossCharacter->GetVelocity().Length();
	}
}

void UBossEnemyAnimInstance::DoSkill()
{
	if (Montage_GetIsStopped(Skill))
	{
		Montage_Play(Skill);
	}
}
