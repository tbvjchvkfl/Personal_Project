// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/NotifyState/AttackAnimNotifyState.h"
#include "Character/Enemy/EnemyCharacter.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (AEnemyCharacter *const Character = Cast<AEnemyCharacter>(MeshComp->GetOwner()))
		{
			Character->AttackStart();
		}
	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (AEnemyCharacter *const character = Cast<AEnemyCharacter>(MeshComp->GetOwner()))
		{
			character->AttackEnd();
		}
	}
}
