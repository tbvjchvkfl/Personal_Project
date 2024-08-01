// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Armor/WeaponBase.h"
#include "Weapon_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API AWeapon_Pistol : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem *Impact;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AWeapon_Pistol();

	virtual void StartShoot(TWeakObjectPtr<APlayerCharacter>owner)override;
	virtual void Reload()override;

	void FireWithLineTrace(TWeakObjectPtr<APlayerCharacter>owner);

	void SpawnEffect();
};
