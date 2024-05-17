// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/EnemyCombatInterface.h"
#include "Animation/AnimMontage.h"
#include "EnemyCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class UE5_HORRORSGAME_API AEnemyCharacter : public ABaseCharacter, public IEnemyCombatInterface
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

	UAnimMontage *GetScreamMontage() const;

	UAnimMontage *GetAttackMontage() const;

	int MeleeAttack_Implementation() override;

	int ScreamAction_Implementation() override;
protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowAbstract = "true"))
	UBehaviorTree *Tree;




	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *ScreamMontage;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================


};
