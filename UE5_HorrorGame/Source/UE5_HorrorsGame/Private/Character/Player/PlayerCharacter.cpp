// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Armor/WeaponBase.h"
#include "Armor/Weapon_Pistol.h"
#include "Armor/Weapon_ShotGun.h"
#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "Component/InventoryComponent.h"
#include "Object/Item/PickUpItem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter() : KillCount(0), InteractionCheckDistance(200.0f)
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

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->InitSphereRadius(200.0f);

	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryInfo"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	SetupStimulusSource();

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
		if (CurrentWeapon)
		{
			HUD->GetInGameHUDWidget()->SetAmmoCountText(CurrentWeapon->GetCurAmmo(), CurrentWeapon->GetMaxAmmo());
		}
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

	PlayerInputComponent->BindAction("ChangePistol", IE_Released, this, &APlayerCharacter::WeaponChangePistol);
	PlayerInputComponent->BindAction("ChangeShotGun", IE_Released, this, &APlayerCharacter::WeaponChangeShotGun);

	PlayerInputComponent->BindAction("Reload", IE_Released, this, &APlayerCharacter::StartReload);

	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &APlayerCharacter::Interaction);

	PlayerInputComponent->BindAction("Inventory", IE_Released, this, &APlayerCharacter::ShowInventory);

	PlayerInputComponent->BindAction("SubAcion", IE_Released, this, &APlayerCharacter::DoSubAction);
	// Bind Axis Functionary
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerCharacter::AddControllerYawInput);
}



void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	for (auto WeaponType : WeaponTypes)
	{
		AddWeapon(WeaponType);
	}
	SwitchingGun(0);
	UpdateCurrentWeaponVisibility();
	HUD->GetInGameHUDWidget()->InitializeHUD();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
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
	if (CurrentWeapon == WeaponInventory[0])
	{
		bPistolWeapon = true;
		bShotGunWeapon = false;
	}
	if (CurrentWeapon == WeaponInventory[1])
	{
		bPistolWeapon = false;
		bShotGunWeapon = true;
	}
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void APlayerCharacter::EndAimming()
{
	bAimming = false;
	bPistolWeapon = false;
	bShotGunWeapon = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::StartRunning()
{
	if (!bAimming)
	{
		bRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

void APlayerCharacter::EndRunning()
{
	bRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
}

void APlayerCharacter::StartShoot()
{
	if (bAimming && !bReloading)
	{
		if (CurrentWeapon)
		{
			if (CurrentWeapon == WeaponInventory[0])
			{
				PlayAnimMontage(ShootPistolAnim);
			}
			if (CurrentWeapon == WeaponInventory[1])
			{
				PlayAnimMontage(ShootShotGunAnim);
			}
			CurrentWeapon->StartShoot(this);
		}
		else
		{
			return;
		}
	}
}

void APlayerCharacter::StartReload()
{
	if (CurrentWeapon->GetCurAmmo() == CurrentWeapon->GetMaxAmmo())
	{
		return;
	}

	if (CurrentWeapon == WeaponInventory[0])
	{
		bPistolReloading = true;
		bShotGunReloading = false;
	}
	if(CurrentWeapon == WeaponInventory[1])
	{
		bPistolReloading = false;
		bShotGunReloading = true;
	}

	bReloading = true;
	if (bAimming)
	{
		bAimming = false;
		bPistolWeapon = false;
		bShotGunWeapon = false;
	}
}

void APlayerCharacter::EndReload()
{
	bReloading = false;
	bPistolReloading = false;
	bShotGunReloading = false;
	if (CurrentWeapon)
	{
		CurrentWeapon->Reload();
	}
}

void APlayerCharacter::ShowInventory()
{
	HUD->ToggleMenu();
}

void APlayerCharacter::Interaction()
{
	FVector TraceStart{ GetPawnViewLocation() + FVector(5.0f, 8.0f, 10.0f)};
	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (TraceHit.bBlockingHit)
		{
			if (auto item = Cast<APickUpItem>(TraceHit.GetActor()))
			{
				InteractableInterface = TraceHit.GetActor();
				InteractableInterface->Interaction(this);
			}
		}
	}
}

void APlayerCharacter::DoSubAction()
{
	CurHealth -= 10.0f;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, FString::Printf(TEXT("%d"), WeaponInventory.Num()), true);
}

void APlayerCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto item = Cast<APickUpItem>(OtherActor))
	{
		HUD->GetInGameHUDWidget()->ShowInteractUI();
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto item = Cast<APickUpItem>(OtherActor))
	{
		HUD->GetInGameHUDWidget()->HideInteractUI();
	}
}

void APlayerCharacter::Die(float KillingDamage, FDamageEvent const &DamageEvent, AController *Killer, AActor *DamageCauser)
{
	HUD->ShowResult();
}

void APlayerCharacter::WeaponChangePistol()
{
	SwitchingGun(0);
	PlayAnimMontage(GunChangeAnim);
}

void APlayerCharacter::WeaponChangeShotGun()
{
	SwitchingGun(1);
	PlayAnimMontage(GunChangeAnim);
}

void APlayerCharacter::SwitchingGun(int WeaponIndex)
{
	if (WeaponInventory.Num() > WeaponIndex)
	{
		if (WeaponInventory[WeaponIndex] != CurrentWeapon)
		{
			LastWeapon = CurrentWeapon;
			CurrentWeapon = WeaponInventory[WeaponIndex];
		}
		if (WeaponInventory[WeaponIndex] == CurrentWeapon)
		{
			return;
		}
	}
}

void APlayerCharacter::AddWeapon(TSubclassOf<AWeaponBase> WeaponType)
{
	AWeaponBase *NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponType);
	NewWeapon->SetOwner(this);
	NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "HandGun");
	NewWeapon->SetActorHiddenInGame(true);
	WeaponInventory.Add(NewWeapon);
}

void APlayerCharacter::UpdateCurrentWeaponVisibility()
{
	if (LastWeapon != nullptr)
	{
		LastWeapon->SetActorHiddenInGame(true);
	}
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->SetActorHiddenInGame(false);
	}
}