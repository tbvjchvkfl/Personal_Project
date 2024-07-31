// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PlayerAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	}
	if (PlayerCharacter)
	{
		MovementSpeed = PlayerCharacter->GetVelocity().Length();
		bIsPistolWeapon = PlayerCharacter->bPistolWeapon;
		bIsShotGunWeapon = PlayerCharacter->bShotGunWeapon;
		bIsReload = PlayerCharacter->bReloading;
		bIsPistolReload = PlayerCharacter->bPistolReloading;
		bIsShotGunReload = PlayerCharacter->bShotGunReloading;
		Direction = UAnimInstance::CalculateDirection(PlayerCharacter->GetVelocity(), PlayerCharacter->GetActorRotation());
	}
}

void UPlayerAnimInstance::StartReloading()
{
	bIsReload = true;
}

void UPlayerAnimInstance::EndReloading()
{
	bIsReload = false;
	if (PlayerCharacter)
	{
		PlayerCharacter->EndReload();
	}
}

void UPlayerAnimInstance::StartAimming()
{
}

void UPlayerAnimInstance::HitAnim()
{
	if (Montage_GetIsStopped(HitAnimation))
	{
		Montage_Play(HitAnimation);
	}
}

void UPlayerAnimInstance::CheckHitAnim()
{
	if (!Montage_GetIsStopped(HitAnimation))
	{
		Montage_Stop(0.1f, HitAnimation);
	}
}
