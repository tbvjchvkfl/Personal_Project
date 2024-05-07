// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Armor/Weapon_Pistol.h"
#include "UI/InGameHUD.h"


APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 75.0f), FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	

	MaxHealth = 100.0f;
	CurHealth = MaxHealth;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if(bAimming)
		{
			ZoomFactor += DeltaTime / 0.2f;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.2f;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
		}

		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		CameraBoom->TargetArmLength = FMath::Lerp<float>(200.0f, 100.0f, ZoomFactor);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Bind Action Functionary
	PlayerInputComponent->BindAction("Aimming", IE_Pressed, this, &APlayerCharacter::StartAimming);
	PlayerInputComponent->BindAction("Aimming", IE_Released, this, &APlayerCharacter::EndAimming);

	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &APlayerCharacter::StartRunning);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &APlayerCharacter::EndRunning);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCharacter::EndShoot);

	PlayerInputComponent->BindAction("Reload", IE_Released, this, &APlayerCharacter::StartReload);

	// Bind Axis Functionary
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerCharacter::AddControllerYawInput);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon(Weapon);

	CreateHUD();
	BindingAmmoChangedDelegate();
}

void APlayerCharacter::MoveForward(float Value)
{
	FRotator NewRotation(0, Controller->GetControlRotation().Yaw, 0);
	FVector NewDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(NewDirection, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	FRotator NewRotation(0, Controller->GetControlRotation().Yaw, 0);
	FVector NewDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(NewDirection, Value);
}

void APlayerCharacter::StartAimming()
{
	bAimming = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void APlayerCharacter::EndAimming()
{
	bAimming = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::StartRunning()
{
	if (!bAimming)
	{
		bRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}

void APlayerCharacter::EndRunning()
{
	bRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void APlayerCharacter::StartShoot()
{
	if (bAimming && !bReloading)
	{
		EquipWeapon->StartShoot(this);
	}
}

void APlayerCharacter::EndShoot()
{
	EquipWeapon->EndShoot();
}

void APlayerCharacter::StartReload()
{
	if (EquipWeapon->GetCurAmmo() == EquipWeapon->GetMaxAmmo())
	{
		return;
	}

	bReloading = true;
	if (bAimming)
	{
		bAimming = false;
	}
}

void APlayerCharacter::EndReload()
{
	bReloading = false;
	EquipWeapon->Reload();
}

void APlayerCharacter::CreateHUD()
{
	if (HUDWidgetClass)
	{
		HUDWidget = Cast<UInGameHUD>(CreateWidget(GetWorld(), HUDWidgetClass));

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

			int AmmoRemainCount = EquipWeapon ? EquipWeapon->GetCurAmmo() : 0;
			int AmmoMaxCount = EquipWeapon ? EquipWeapon->GetMaxAmmo() : 0;

			HUDWidget->Init(AmmoRemainCount, AmmoMaxCount);
		}
	}
}

void APlayerCharacter::BindingAmmoChangedDelegate() const
{
	if (EquipWeapon)
	{
		EquipWeapon->ShowUIDelegate.AddLambda([&]()
			{
				if (HUDWidget)
				{
					HUDWidget->SetAmmoCountText(EquipWeapon->GetCurAmmo(), EquipWeapon->GetMaxAmmo());
				}
			});
	}
}

void APlayerCharacter::AttachWeapon(TSubclassOf<AWeapon_Pistol> WeaponClass)
{
	if (WeaponClass)
	{
		EquipWeapon = GetWorld()->SpawnActor<AWeapon_Pistol>(WeaponClass);

		const USkeletalMeshSocket *WeaponSocket = GetMesh()->GetSocketByName("HandGun");

		if (EquipWeapon && WeaponSocket)
		{
			WeaponSocket->AttachActor(EquipWeapon, GetMesh());
		}
	}
}