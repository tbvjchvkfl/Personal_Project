// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/NotifyState/ShootProjectile.h"
#include "Character/Enemy/BossEnemyCharacter.h"

void UShootProjectile::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (auto *const Boss = Cast<ABossEnemyCharacter>(MeshComp->GetOwner()))
		{
			Boss->DoSkillAction();
		}
	}
}
