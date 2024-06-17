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
		bIsAimming = PlayerCharacter->bAimming;
		bIsReload = PlayerCharacter->bReloading;
		Direction = CalculateDirection(PlayerCharacter->GetVelocity(), PlayerCharacter->GetActorRotation());
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
	bIsAimming = true;
}
