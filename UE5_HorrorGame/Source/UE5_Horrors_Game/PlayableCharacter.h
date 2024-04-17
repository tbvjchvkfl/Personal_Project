// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayableCharacter();

public:
	class UCapsuleComponent* CollsionBox;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	//class UCapsuleComponent* CollisionBox;

	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomIn;
	bool bRunning;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void ZoomIn();
	void ZoomOut();
	void DoRunning();
	void NoRunning();

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
