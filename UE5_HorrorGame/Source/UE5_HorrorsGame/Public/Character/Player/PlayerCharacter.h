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
class UPlayerAnimInstance;

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

	UPROPERTY(BlueprintReadOnly)
	int KillCount;

	UPROPERTY(BlueprintReadOnly)
	bool bIsBossKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FogSeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DevilSeal;

	FTimerHandle DeathTimer;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APlayerCharacter();
	void StartReload();
	void EndReload();
	void ShowInventory();

	FORCEINLINE UInventoryComponent *GetInventory()const { return PlayerInventory; }

	AWeaponBase *GetCurrentWeapon()const { return CurrentWeapon; }

	

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

	UPROPERTY()
	UPlayerAnimInstance *PlayerAnim;

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

	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser);

	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)override;

	void DeathAnimationEnd();

private:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
};
