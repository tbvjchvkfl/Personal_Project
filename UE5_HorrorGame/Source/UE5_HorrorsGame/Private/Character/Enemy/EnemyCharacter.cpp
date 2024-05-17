// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyCharacter::AEnemyCharacter()
{
}

UBehaviorTree *AEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}

UAnimMontage *AEnemyCharacter::GetScreamMontage() const
{
	return ScreamMontage;
}

UAnimMontage *AEnemyCharacter::GetAttackMontage() const
{
	return AttackMontage;
}

int AEnemyCharacter::MeleeAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
	return 0;
}

int AEnemyCharacter::ScreamAction_Implementation()
{
	if (ScreamMontage)
	{
		PlayAnimMontage(ScreamMontage);
	}
	return 0;
}
