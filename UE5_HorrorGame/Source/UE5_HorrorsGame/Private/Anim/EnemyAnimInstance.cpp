// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/EnemyAnimInstance.h"
#include "Character/Enemy/EnemyCharacter.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (!PlayerPawn)
	{
		PlayerPawn = TryGetPawnOwner();
	}
	if (PlayerPawn)
	{
		EnemyCharacter = Cast<AEnemyCharacter>(PlayerPawn);
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


}
