// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComponent);
}

void AWeaponBase::DecreaseAmmoCount()
{
	--CurAmmoCount;
	if (ShowUIDelegate.IsBound())
	{
		ShowUIDelegate.Broadcast();
	}
}

void AWeaponBase::ResetAmmoCount()
{
	CurAmmoCount = MaxAmmoCount;
	if (ShowUIDelegate.IsBound())
	{
		ShowUIDelegate.Broadcast();
	}
}

void AWeaponBase::StartShoot(TWeakObjectPtr<APlayerCharacter> owner)
{
}

void AWeaponBase::Reload()
{
}

