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
struct FItemData;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr)
	{
	};
	UPROPERTY()
	AActor *CurrentInteractable;

	UPROPERTY()
	UPrimitiveComponent *CurrentComp;

	UPROPERTY()
	float LastInteractionCheckTimer;
};

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

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeapon_ShotGun> ShotGunWeapon;

	AWeapon_Pistol *Pistol;

	AWeapon_ShotGun *ShotGun;

	/*UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UInGameHUD> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UInGameHUD *HUDWidget;*/

	FVector2D CameraInput;
	float ZoomFactor;
	bool bRunning;
	bool bAimming;
	bool bReloading;
	bool bEnableInteraction;

	int KillCount;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APlayerCharacter();

	
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void AttachWeapon(TSubclassOf<AWeapon_Pistol> WeaponClass);
	//void AttachShotGun(TSubclassOf<AWeapon_ShotGun> WeaponShotGunClass);
	void StartReload();
	void EndReload();
	
	//void CreateHUD();
	void BindingAmmoChangedDelegate() const;
	void ShowInventory();

	//TArray<AWeaponBase> GetSubInventory() { return SubInventory; }

	void AddItem(FItemData *Item);

	TArray<FItemData*> GetInventoryItem();
	int32 GetPlayerCoin();

	bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

	virtual void Die(float KillingDamage, struct FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)override;

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	class AHorrorsHUD *HUD;
	class UInventory *Inventory;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> InteractableInterface;
	
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractData;

	TArray<FItemData*> PlayerItem;
	int32 PlayerCoin;

	class UAIPerceptionStimuliSourceComponent *StimulusSource;

	UPROPERTY(EditAnywhere, Category = "Interface")
	TSubclassOf<class APickUpItem> actor;
	
	TWeakObjectPtr<APickUpItem> pickitem;

	APickUpItem *PickItem;

	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	/*UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<class AWeaponBase*> SubInventory;*/

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartAimming();
	void EndAimming();
	void StartRunning();
	void EndRunning();
	void StartShoot();
	void EndShoot();
	void Interaction();
	void StartInteraction();
	void EndInteraction();
	void FoundInteractable(AActor *NewInteractable);
	void NotFoundInteractable();
	void Interact();
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
