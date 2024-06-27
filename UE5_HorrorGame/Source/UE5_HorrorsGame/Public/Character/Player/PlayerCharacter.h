// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/InteractionInterface.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AWeapon_Pistol;
class UInGameHUD;
class UInventoryComponent;

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
	class USphereComponent *CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon_Pistol> PistolWeapon;

	AWeapon_Pistol *Pistol;

	FVector2D CameraInput;
	float ZoomFactor;
	bool bRunning;
	bool bAimming;
	bool bReloading;

	int KillCount;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APlayerCharacter();

	void AttachWeapon(TSubclassOf<AWeapon_Pistol> WeaponClass);
	void StartReload();
	void EndReload();
	void ShowInventory();

	FORCEINLINE UInventoryComponent *GetInventory()const { return PlayerInventory; }

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

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartAimming();
	void EndAimming();
	void StartRunning();
	void EndRunning();
	void StartShoot();
	void EndShoot();
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
