// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class UE5_HORRORSGAME_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AEnemyCharacter();
	UBehaviorTree *GetBehaviorTree() const;

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowAbstract = "true"))
	UBehaviorTree *Tree;




	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
