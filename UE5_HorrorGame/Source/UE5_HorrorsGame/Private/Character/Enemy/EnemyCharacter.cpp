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