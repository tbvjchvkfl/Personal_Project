// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor/Weapon_Pistol.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AWeapon_Pistol::AWeapon_Pistol()
{
	MaxAmmoCount = 15.0f;
	CurAmmoCount = MaxAmmoCount;
	ReloadingDelayTime = 3.0f;
	TraceDistance = 15000.0f;
	AttackRate = 20.0f;
}

void AWeapon_Pistol::StartShoot(TWeakObjectPtr<APlayerCharacter> owner)
{
	auto Character = owner.Get();

	if (Character)
	{
		switch (FireType)
		{
			case EFireType::EF_LineTrace:
			{
				FireWithLineTrace(Character);
				SpawnEffect();
			}
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
			FVector EndTrace = StartTrace + Character->FollowCamera->GetForwardVector() * TraceDistance;  //(ownerController->GetControlRotation().Vector() * TraceDistance);

			FCollisionQueryParams CollisionParam;
			CollisionParam.AddIgnoredActor(this);
			
			FHitResult HitTrace;

			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.0f);
			

			if (GetWorld()->LineTraceSingleByChannel(HitTrace, StartTrace, EndTrace, ECC_Visibility, CollisionParam))
			{
				FRotator Rotation;
				FVector ShotDirection = -Rotation.Vector();

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, HitTrace.Location, ShotDirection.Rotation());
				
				if (HitTrace.bBlockingHit)
				{
					if(auto *NPC = Cast<AEnemyCharacter>(HitTrace.GetActor()))
					{
						auto HP = NPC->GetCurHealth() - 20.0f;
						NPC->SetCurHealth(HP);
						GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("HP : %f"), HP));
					}
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

void AWeapon_Pistol::SpawnEffect()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMesh, TEXT("FirePoint"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMesh, TEXT("FirePoint"));
}
