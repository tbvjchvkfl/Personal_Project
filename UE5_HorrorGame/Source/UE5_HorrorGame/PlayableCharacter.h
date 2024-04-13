// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "PlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORGAME_API APlayableCharacter : public ABasicCharacter
{
	GENERATED_BODY()
	
public:
	APlayableCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

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
};
