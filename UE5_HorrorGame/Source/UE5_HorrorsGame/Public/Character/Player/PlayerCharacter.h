// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
class AWeapon_Pistol;
class UInGameHUD;

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

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon_Pistol> Weapon;

	AWeapon_Pistol *EquipWeapon;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UInGameHUD> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UInGameHUD *HUDWidget;



	FVector2D CameraInput;
	float ZoomFactor;
	bool bRunning;
	bool bAimming;
	bool bReloading;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	APlayerCharacter();

	
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void AttachWeapon(TSubclassOf<AWeapon_Pistol> WeaponClass);
	void StartReload();
	void EndReload();
	
	void CreateHUD();
	void BindingAmmoChangedDelegate() const;


protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================








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


};
