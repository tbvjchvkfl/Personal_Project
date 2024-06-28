// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE5_HORRORSGAME_API IEnemyCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int MeleeAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SubAction")
	int ScreamAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SubAction")
	void DeathAnim();
};
