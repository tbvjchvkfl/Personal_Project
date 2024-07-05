// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/InteractionInterface.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInGameHUD;
class UInventoryComponent;
class USphereComponent;
class UItemBase;
class AWeapon_Pistol;
class AWeapon_ShotGun;
class AWeaponBase;

UCLASS()
class UE5_HORRORSGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent *CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent *FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent *CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent *PisotlMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent *ShotGunMesh;

	UItemBase *ItemBase;

	FVector2D CameraInput;
	float ZoomFactor;
	bool bRunning;
	bool bAimming;
	bool bPistolWeapon;
	bool bShotGunWeapon;
	bool bReloading;
	bool bPistolReloading;
	bool bShotGunReloading;

	int KillCount;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APlayerCharacter();
	void StartReload();
	void EndReload();
	void ShowInventory();

	FORCEINLINE UInventoryComponent *GetInventory()const { return PlayerInventory; }

	AWeaponBase *GetCurrentWeapon()const { return CurrentWeapon; }

	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)override;

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	class AHorrorsHUD *HUD;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> InteractableInterface;

	class UAIPerceptionStimuliSourceComponent *StimulusSource;

	float InteractionCheckDistance;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	UInventoryComponent *PlayerInventory;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf<AWeaponBase>> WeaponTypes;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<AWeaponBase *> WeaponInventory;

	UPROPERTY()
	AWeaponBase *CurrentWeapon;

	UPROPERTY()
	AWeaponBase *LastWeapon;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage *ShootPistolAnim;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage *ShootShotGunAnim;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage *GunChangeAnim;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void SwitchingGun(int WeaponIndex);
	void AddWeapon(TSubclassOf<AWeaponBase> WeaponType);

	UFUNCTION(BlueprintCallable, Category = "WeaponChange")
	void UpdateCurrentWeaponVisibility();

	void WeaponChangePistol();
	void WeaponChangeShotGun();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartAimming();
	void EndAimming();
	void StartRunning();
	void EndRunning();
	void StartShoot();
	void Interaction();
	
	void DoSubAction();
	
	void SetupStimulusSource();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
