// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/NotifyState/AttackAnimNotify.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UAttackAnimNotify::OnAnimNotifyCreatedInEditor(FAnimNotifyEvent &ContainingAnimNotifyEvent)
{
	// This Function is Initialize for this Notify
	// ���⼭ �ش� ��Ƽ���̸� �ʱ�ȭ
}

void UAttackAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (auto *NPC = Cast<AEnemyCharacter>(MeshComp->GetOwner()))
		{
			NPC->MeleeAttackWithSweepTrace();
		}

		if (auto *const Boss = Cast<ABossEnemyCharacter>(MeshComp->GetOwner()))
		{
			Boss->MeleeAttackWithSweepTrace();
		}
	}
}

//void UAttackAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
//{
//	//�� �Լ��� Ȯ����
//}
