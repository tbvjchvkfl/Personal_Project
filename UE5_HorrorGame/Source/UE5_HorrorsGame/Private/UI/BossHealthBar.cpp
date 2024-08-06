// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossHealthBar.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Components/ProgressBar.h"

void UBossHealthBar::InitializeHealthbar(ABossEnemyCharacter *BossEnemy)
{
	if (BossEnemy)
	{
		ProgressBar->SetPercent(BossEnemy->GetCurHealth() / BossEnemy->GetMaxHealth());
		if (ProgressBar->GetPercent() <= 0.0f)
		{
			ProgressBar->SetPercent(0.0f);
		}
	}
}