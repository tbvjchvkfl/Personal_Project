// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Armor/Weapon_Pistol.h"
#include "UI/InGameHUD.h"
#include "Object/Item/PickUpItem.h"
#include "UI/HorrorsHUD.h"
#include "UI/Inventory.h"

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
	AttachWeapon(Weapon);

	CreateHUD();
	BindingAmmoChangedDelegate();
	
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Inventory = Cast<UInventory>(GetWorld());
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

void APlayerCharacter::StartInteract()
{
	CurHealth -= 10.0f;
}

void APlayerCharacter::EndInteract()
{

}

void APlayerCharacter::Interaction()
{
	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ TraceStart + (GetControlRotation().Vector() * 1500.0f) };
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (AActor *Actor = TraceHit.GetActor())
		{
			for (FName Tag : Actor->Tags)
			{
				if (Tag.ToString() == "PickUp")
				{
					IPickUpInterface *interface = Cast<IPickUpInterface>(Actor);
					interface->Interact(this);
				}
			}
		}
	}
}

void APlayerCharacter::DoSubAction()
{
	CurHealth -= 10.0f;
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

void APlayerCharacter::ShowInventory()
{
	HUD->ToggleMenu();
}

void APlayerCharacter::AddItem(FItemData* Item)
{
	if (Item && Item->ItemType == EItemType::Coin)
	{
		PlayerCoin += Item->Amount;
		HUD->AddInventoryItem();
	}
	else
	{
		PlayerItem.Add(Item);
		HUD->AddInventoryItem();
		PlayerItem.Pop();
	}
	/*int index = FindStack(Item);
	if (index == -1)
	{
		FItemData* newItemSlot;
		newItemSlot->Amount = Item->Amount;
		newItemSlot->ItemType = Item->ItemType;
		newItemSlot->TextData = Item->TextData;
		newItemSlot->AssetData = Item->AssetData;
		PlayerItem.Add(newItemSlot);
		HUD->AddInventoryItem();
		PlayerItem.Pop();
	}
	else
	{
		PlayerItem[index]->Amount += Item->Amount
	}*/
	//if (Item)
	//{
	//	PlayerItem.Add(Item);
	//	HUD->AddInventoryItem();
	//	PlayerItem.Pop();
	//}
}

TArray<FItemData*> APlayerCharacter::GetInventoryItem()
{
	return PlayerItem;
}

int32 APlayerCharacter::GetPlayerCoin()
{
	return PlayerCoin;
}

int APlayerCharacter::FindStack(FItemData* Item)
{
	for (int i = 0; i < PlayerItem.Num(); i++)
	{
		if (PlayerItem[i] == Item)
		{
			return i;
		}
	}

	return -1;
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
