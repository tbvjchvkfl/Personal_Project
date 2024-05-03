// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "UI_HUD_Widget.h"
#include "InteractionInterface.h"
#include "PlayableCharacter.generated.h"

/**
 * 
 */


USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{
	};

	UPROPERTY()
	AActor *CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_Dynamic);

UCLASS()
class UE5_HORRORS_GAME_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUI_HUD_Widget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UUI_HUD_Widget* HUDWidget;
	
	class UCircleHPBar* UHPBar;
	void CreateHUD();

	void BindingAmmoChagedDelegate() const;
public:
	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APistolWeapon> Weapon;

	class APistolWeapon* EquipWeapon;

	void AttachWeapon(TSubclassOf<class APistolWeapon> WeaponClass);

public:
	APlayableCharacter();

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	FVector2D CameraInput;
	float ZoomFactor;
	bool bRunning;
	bool bAimming;
	bool bReloading;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartAimming();
	void EndAimming();
	void DoRunning();
	void NoRunning();
	void StartShoot();
	void EndShoot();

	

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Event")
	FDele_Dynamic FDele_Start_Reload;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Event")
	FDele_Dynamic FDele_Start_Aimming;

	UFUNCTION()
	void StartReload();

	UFUNCTION()
	void EndReload();

	void SetUIHealth();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> projectileActor;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Pistol_Idle;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Change_Idle;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteract();
	void BeginInteract();
	void EndInteract();
	void Interact();
};
