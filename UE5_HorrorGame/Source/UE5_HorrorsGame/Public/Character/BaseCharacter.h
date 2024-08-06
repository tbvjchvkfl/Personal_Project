// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UE5_HORRORSGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	float GetCurHealth() { return CurHealth; }

	UFUNCTION(BlueprintCallable)
	float SetCurHealth(float value) { return CurHealth = value; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() { return MaxHealth; }



protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	
	UPROPERTY(BlueprintReadOnly)
	float CurHealth;

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *DeathMontage;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
