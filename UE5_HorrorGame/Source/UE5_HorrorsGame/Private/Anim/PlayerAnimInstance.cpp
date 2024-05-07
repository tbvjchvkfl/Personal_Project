// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PlayerAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
	if (PlayerPawn)
	{
		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
	if (PlayerPawn)
	{
		MovementSpeed = PlayerPawn->GetVelocity().Length();
		PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
		bIsAimming = PlayerCharacter->bAimming;
		bIsReload = PlayerCharacter->bReloading;
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
