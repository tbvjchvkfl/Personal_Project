// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BossEnemyCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class UE5_HORRORSGAME_API ABossEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	UBehaviorTree *GetBehaviorTree() const { return Tree; }

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowAbstract = "true"))
	UBehaviorTree *Tree;

	class AHorrorsHUD *HUD;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser) override;

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
