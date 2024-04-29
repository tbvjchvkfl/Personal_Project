// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "PlayableCharacter.h"
#include "PistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API APistolWeapon : public AWeaponActor
{
	GENERATED_BODY()
	
public:
	APistolWeapon();
	virtual void StartShoot(TWeakObjectPtr<APlayableCharacter>owner)override;
	virtual void EndShoot()override;
	virtual void Reloading()override;

	void FireWithLineTrace(TWeakObjectPtr<APlayableCharacter>owner);

private:
	FTimerHandle FireTimerHandle;
};
