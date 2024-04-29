// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolWeapon.h"
#include "Camera/CameraComponent.h"

APistolWeapon::APistolWeapon()
{
	MaxAmmoCount = 15;
	AmmoCount = MaxAmmoCount;
	ReloadingDelayTime = 3.0f;
	FireInterval = 0.1f;
	TraceDistance = 15000.0f;
}

void APistolWeapon::StartShoot(TWeakObjectPtr<APlayableCharacter> owner)
{
	auto Character = owner.Get();

	if (Character)
	{
		switch (FireType)
		{
			case EFireType::EF_LineTrace:
				FireWithLineTrace(Character);
				
				//GetWorldTimerManager().SetTimer(FireTimerHandle, [&]() {return FireWithLineTrace(Character); }, FireInterval, true);
				break;
			case EFireType::EF_Projectile:
				break;
		}
	}
}

void APistolWeapon::EndShoot()
{
	if (FireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
}

void APistolWeapon::Reloading()
{
	AmmoCount = MaxAmmoCount;
}

void APistolWeapon::FireWithLineTrace(TWeakObjectPtr<APlayableCharacter> owner)
{
	/*if (AmmoCount <= 0)
	{
		EndShoot();
		return;
	}*/
	
	auto character = owner.Get();

	if (character)
	{
		AController* ownerController = character->GetController();

		if (ownerController)
		{
			auto Start = WeaponMesh->GetSocketLocation("FirePoint");
			auto EndPoint = (ownerController->GetControlRotation().Vector() * TraceDistance) + Start;
			FCollisionQueryParams CollisionQuery;
			FHitResult Hit;
			CollisionQuery.AddIgnoredActor(this);
			UWorld* CurrentWorld = GetWorld();

			DrawDebugLine(CurrentWorld, Start, EndPoint, FColor::Red, false, 3.0f);

			--AmmoCount;
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Ammocount : %i"), AmmoCount));

			
			if (CurrentWorld->LineTraceSingleByChannel(Hit, Start, EndPoint, ECC_Visibility, CollisionQuery))
			{
				if (Hit.GetActor())
				{
					auto hitactor = Hit.GetActor();
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, FString::Printf(TEXT("Hit Trace")));
				}
			}
			if (AmmoCount == 0)
			{
				character->StartReload();
			}
		}
	}
}
