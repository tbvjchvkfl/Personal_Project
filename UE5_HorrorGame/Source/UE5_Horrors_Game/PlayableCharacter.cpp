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
#include "CircleHPBar.h"
#include "DrawDebugHelpers.h"

void APlayableCharacter::CreateHUD()
{
	if (HUDWidgetClass)
	{
		HUDWidget = Cast<UUI_HUD_Widget>(CreateWidget(GetWorld(), HUDWidgetClass));

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

			int AmmoRemainCount = EquipWeapon ? EquipWeapon->GetAmmoCount() : 0;
			int AmmoMaxCount = EquipWeapon ? EquipWeapon->GetMaxAmmoCount() : 0;

			HUDWidget->Init(AmmoRemainCount, AmmoMaxCount);
		}
	}
}

void APlayableCharacter::BindingAmmoChagedDelegate() const
{
	if (EquipWeapon)
	{
		EquipWeapon->AmmoChangedDelegate.AddLambda([&]()
			{
				if (HUDWidget)
				{
					HUDWidget->SetAmmoCountText(EquipWeapon->GetAmmoCount(), EquipWeapon->GetMaxAmmoCount());
				}
			});
	}
}

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
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 75.0f), FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayableCharacter::OnOverlapBegin);

	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	Maxhealth = 100.0f;
	CurHealth = Maxhealth;

	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 250.0f;
}


void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (bAimming)
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
	{
		if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
		{
			PerformInteractionCheck();
		}
	}
}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon(Weapon);

	CreateHUD();
	BindingAmmoChagedDelegate();
	SetUIHealth();
}

void APlayableCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis mapping
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APlayableCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayableCharacter::AddControllerYawInput);


	//Action Mapping
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APlayableCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &APlayableCharacter::EndInteract);

	PlayerInputComponent->BindAction("Reloading", IE_Released, this, &APlayableCharacter::StartReload);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayableCharacter::StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayableCharacter::EndShoot);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayableCharacter::StartAimming);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &APlayableCharacter::EndAimming);

	
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

void APlayableCharacter::StartAimming()
{
	bAimming = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void APlayableCharacter::EndAimming()
{
	bAimming = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayableCharacter::DoRunning()
{
	if (!bAimming)
	{
		bRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}

void APlayableCharacter::NoRunning()
{
	bRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void APlayableCharacter::StartShoot()
{
	if (bAimming && !bReloading)
	{
		EquipWeapon->StartShoot(this);
	}
}

void APlayableCharacter::EndShoot()
{
	EquipWeapon->EndShoot();
}

void APlayableCharacter::StartReload()
{
	if (EquipWeapon->GetAmmoCount() == EquipWeapon->GetMaxAmmoCount())
	{
		return;
	}

	bReloading = true;
	if (bAimming)
	{
		bAimming = false;
	}
}

void APlayableCharacter::EndReload()
{
	if (EquipWeapon)
	{
		bReloading = false;
		EquipWeapon->Reloading();
	}
}

void APlayableCharacter::SetUIHealth()
{
	if (HUDWidget)
	{
		float HP = CurHealth / 100.0f;
		UHPBar->SetPercent(HP);
	}
}

void APlayableCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			const float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

			if (TraceHit.GetActor() != InteractionData.CurrentInteractable && Distance <= InteractionCheckDistance)
			{
				FoundInteractable(TraceHit.GetActor());
				return;
			}

			if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
			{
				return;
			}
		}
	}
	NoInteract();
}

void APlayableCharacter::FoundInteractable(AActor *NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	TargetInteractable->BeginFocus();
}

void APlayableCharacter::NoInteract()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void APlayableCharacter::BeginInteract()
{
	PerformInteractionCheck();
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &APlayableCharacter::Interact, TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void APlayableCharacter::EndInteract()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndInteract();
		}
	}
}

void APlayableCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}


void APlayableCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACollisionActor::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Touch!!"));
		CurHealth -= 20.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("myHealth = %f"), CurHealth));
		
	}
}

