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

	void AttackStart()const;
	void AttackEnd()const;
protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowAbstract = "true"))
	UBehaviorTree *Tree;

	

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *ScreamMontage;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *HandCollisionBox;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);
};