// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/RotationMatrix.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayableCharacter::APlayableCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (bZoomIn)
		{
			ZoomFactor += DeltaTime / 0.5f;
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		CameraBoom->TargetArmLength = FMath::Lerp<float>(200.0f, 100.0f, ZoomFactor);
	}
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnPitch", this, &APlayableCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnYaw", this, &APlayableCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayableCharacter::ZoomIn);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &APlayableCharacter::ZoomOut);
}

void APlayableCharacter::MoveForward(float Value)
{
	if (bZoomIn)
	{
		const FVector FowardDirection = GetActorForwardVector();
		AddMovementInput(FowardDirection, Value);
	}
	else
	{
		if ((Controller != NULL) && Value != 0.0f)
		{
			const FRotator Rot = Controller->GetControlRotation();
			const FRotator YawRot(0, Rot.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayableCharacter::MoveRight(float Value)
{
	if (bZoomIn)
	{
		const FVector RightDirection = GetActorRightVector();
		AddMovementInput(RightDirection, Value);
	}
	else
	{
		if ((Controller != NULL) && Value != 0.0f)
		{
			const FRotator Rot = Controller->GetControlRotation();
			const FRotator YawRot(0, Rot.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayableCharacter::ZoomIn()
{
	bZoomIn = true;
}

void APlayableCharacter::ZoomOut()
{
	bZoomIn = false;
}
