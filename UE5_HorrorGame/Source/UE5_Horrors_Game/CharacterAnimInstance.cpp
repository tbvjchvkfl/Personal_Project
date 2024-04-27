// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "PlayableCharacter.h"

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

void UCharacterAnimInstance::UpdateProperties()
{
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateProperties();
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
	if (PlayableCharacter)
	{
		PlayableCharacter->FDele_Start_Reload.AddDynamic(this, &UCharacterAnimInstance::StartReloading);
	}
}
