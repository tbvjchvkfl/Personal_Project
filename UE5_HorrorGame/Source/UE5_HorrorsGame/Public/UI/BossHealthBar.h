// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHealthBar.generated.h"

class UProgressBar;
class ABossEnemyCharacter;

UCLASS()
class UE5_HORRORSGAME_API UBossHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar *ProgressBar;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void InitializeHealthbar(ABossEnemyCharacter* BossEnemy);
};
