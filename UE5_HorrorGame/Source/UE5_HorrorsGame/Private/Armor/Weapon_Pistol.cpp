// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor/Weapon_Pistol.h"
#include "Character/Player/PlayerCharacter.h"

AWeapon_Pistol::AWeapon_Pistol()
{
	MaxAmmoCount = 15.0f;
	CurAmmoCount = MaxAmmoCount;
	ReloadingDelayTime = 3.0f;
	TraceDistance = 15000.0f;
}

void AWeapon_Pistol::StartShoot(TWeakObjectPtr<APlayerCharacter> owner)
{
	auto Character = owner.Get();

	if (Character)
	{
		switch (FireType)
		{
			case EFireType::EF_LineTrace:
				FireWithLineTrace(Character);
				break;

			case EFireType::EF_Projectile:
				break;
		}
	}
}

void AWeapon_Pistol::EndShoot()
{
	
}

void AWeapon_Pistol::Reload()
{
	ResetAmmoCount();
}

void AWeapon_Pistol::FireWithLineTrace(TWeakObjectPtr<APlayerCharacter> owner)
{
	auto Character = owner.Get();

	if (Character)
	{
		AController *ownerController = Character->GetController();

		if (ownerController)
		{
			FVector StartTrace = WeaponMesh->GetSocketLocation("FirePoint");
			FVector EndTrace = StartTrace + (ownerController->GetControlRotation().Vector() * TraceDistance);

			FCollisionQueryParams CollisionParam;
			CollisionParam.AddIgnoredActor(this);
			
			FHitResult HitTrace;

			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.0f);

			if (GetWorld()->LineTraceSingleByChannel(HitTrace, StartTrace, EndTrace, ECC_Visibility, CollisionParam))
			{
				if (HitTrace.GetActor())
				{
					// HitTrace가 액터와 부딪히면 여기서 함수 만들 것. 대미지 주는 함수
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Hit")));
				}
			}
			
			DecreaseAmmoCount();
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("CurAmmo : %i"), CurAmmoCount));

			if (CurAmmoCount == 0)
			{
				Character->StartReload();
			}
		}
	}
}
