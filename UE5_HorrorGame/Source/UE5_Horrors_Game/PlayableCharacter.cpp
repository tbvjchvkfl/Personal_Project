// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CollisionActor.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "WeaponActor.h"
#include "Engine/SkeletalMeshSocket.h"
#include "PistolWeapon.h"

void APlayableCharacter::AttachWeapon(TSubclassOf<class APistolWeapon> WeaponClass)
{
	if (WeaponClass)
	{
		EquipWeapon = GetWorld()->SpawnActor<APistolWeapon>(WeaponClass);

		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_R_Gun");

		if (EquipWeapon && WeaponSocket)
		{
			WeaponSocket->AttachActor(EquipWeapon, GetMesh());
		}
	}
}

APlayableCharacter::APlayableCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 65.0f), FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayableCharacter::OnOverlapBegin);

	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	
}


void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (bZoomIn)
		{
			ZoomFactor += DeltaTime / 0.2f;
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.2f;
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		CameraBoom->TargetArmLength = FMath::Lerp<float>(200.0f, 100.0f, ZoomFactor);
	}
	{
		if (bAimming)
		{
			GetCharacterMovement()->bOrientRotationToMovement = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			
		}
		if (!bAimming)
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}
	}
}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon(Weapon);
}

void APlayableCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// 이동 함수에 if 걸어보기
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APlayableCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayableCharacter::AddControllerYawInput);

	
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayableCharacter::StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayableCharacter::EndShoot);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayableCharacter::ZoomIn);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &APlayableCharacter::ZoomOut);

	// 달리기 함수 수정해야함.
	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &APlayableCharacter::DoRunning);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &APlayableCharacter::NoRunning);

}

void APlayableCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && Value != 0.0f)
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayableCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && Value != 0.0f)
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayableCharacter::ZoomIn()
{
	bZoomIn = true;
	bAimming = true;
	PlayAnimMontage(Pistol_Idle, 1.0f);
}

void APlayableCharacter::ZoomOut()
{
	bZoomIn = false;
	bAimming = false;
	PlayAnimMontage(Change_Idle, 1.0f);
}

void APlayableCharacter::DoRunning()
{
	bRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void APlayableCharacter::NoRunning()
{
	bRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void APlayableCharacter::StartShoot()
{
	EquipWeapon->StartShoot(this);
}

void APlayableCharacter::EndShoot()
{
	EquipWeapon->EndShoot();
}

void APlayableCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACollisionActor::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Touch!!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("myHealth = %f"), myHealth));
		myHealth -= 0.5f;
	}
}
