// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APlayerCharacter;

DECLARE_MULTICAST_DELEGATE(FDeli_Multi);


UENUM()
enum class EFireType : uint8
{
	EF_LineTrace UMETA(DisplayName = "Line Trace"),
	EF_Projectile UMETA(DisplayName = "Projectile")
};


UCLASS(Abstract)
class UE5_HORRORSGAME_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	FDeli_Multi ShowUIDelegate;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	AWeaponBase();

	inline int GetCurAmmo() { return CurAmmoCount; }
	inline int GetMaxAmmo() { return MaxAmmoCount; }
	inline float GetReloadDelayTime() { return ReloadingDelayTime; }

	void DecreaseAmmoCount();
	void ResetAmmoCount();

	virtual void StartShoot(TWeakObjectPtr<APlayerCharacter> owner);
	virtual void EndShoot();
	virtual void Reload();


protected:
	
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditAnywhere, Category = "WeaponMesh")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	int CurAmmoCount;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	int MaxAmmoCount;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	float ReloadingDelayTime;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	float TraceDistance;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	EFireType FireType = EFireType::EF_LineTrace;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================


};
