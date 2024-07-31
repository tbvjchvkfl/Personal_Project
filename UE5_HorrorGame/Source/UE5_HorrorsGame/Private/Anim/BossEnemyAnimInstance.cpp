// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/BossEnemyAnimInstance.h"
#include "Character/Enemy/BossEnemyCharacter.h"


void UBossEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BossCharacter = Cast<ABossEnemyCharacter>(TryGetPawnOwner());
	bIsCoolTime = false;
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

void UBossEnemyAnimInstance::AttackCoolDown(float CoolTime)
{
	if (!bIsCoolTime)
	{
		bIsCoolTime = true;
		GetWorld()->GetTimerManager().SetTimer
		(TimerHandle,
		[this]()
			{
				bIsCoolTime = false;
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			},
		CoolTime,
		false
		);
	}
}

void UBossEnemyAnimInstance::DoSkill(float CoolDown)
{
	if (Montage_GetIsStopped(Skill))
	{
		Montage_Play(Skill);
		AttackCoolDown(CoolDown);
	}
}

void UBossEnemyAnimInstance::CheckHitAnim()
{
	if (!Montage_GetIsStopped(HitAnimation))
	{
		Montage_Stop(0.1f, HitAnimation);
	}
}

void UBossEnemyAnimInstance::HitAnim()
{
	if (Montage_GetIsStopped(HitAnimation))
	{
		Montage_Play(HitAnimation);
	}
}
