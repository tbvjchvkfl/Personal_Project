// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "PlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCharacterAnimInstance::StartReloading()
{
	bIsReload = true;
}

void UCharacterAnimInstance::EndReloading()
{
	bIsReload = false;

	if (PlayableCharacter)
	{
		PlayableCharacter->EndReload();
	}
}

void UCharacterAnimInstance::StartAimming()
{
	bIsAimming = true;
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
	if (PlayerPawn)
	{
		MovementSpeed = PlayerPawn->GetVelocity().Length();
		PlayableCharacter = Cast<APlayableCharacter>(PlayerPawn);
		bIsAimming = PlayableCharacter->bAimming;
		bIsReload = PlayableCharacter->bReloading;
	}
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
	if (PlayerPawn)
	{
		PlayableCharacter = Cast<APlayableCharacter>(PlayerPawn);
	}
}
