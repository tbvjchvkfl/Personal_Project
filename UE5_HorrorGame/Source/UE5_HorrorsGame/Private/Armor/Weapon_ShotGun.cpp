// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor/Weapon_ShotGun.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/BossEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"


AWeapon_ShotGun::AWeapon_ShotGun()
{
	MaxAmmoCount = 7.0f;
	CurAmmoCount = MaxAmmoCount;
	ReloadingDelayTime = 3.0f;
	TraceDistance = 5000.0f;
	AttackRate = 20.0f;
}

void AWeapon_ShotGun::StartShoot(TWeakObjectPtr<APlayerCharacter> owner)
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

void AWeapon_ShotGun::Reload()
{
	ResetAmmoCount();
}

void AWeapon_ShotGun::FireWithLineTrace(TWeakObjectPtr<APlayerCharacter> owner)
{
	auto Character = owner.Get();

	if (Character)
	{
		AController *ownerController = Character->GetController();

		if (ownerController)
		{
			FVector StartTrace = WeaponMesh->GetSocketLocation("");
			FVector EndTrace = StartTrace + Character->FollowCamera->GetForwardVector() * TraceDistance;

			FCollisionQueryParams CollisionParam;
			CollisionParam.AddIgnoredActor(this);

			FHitResult HitTrace;

			if (GetWorld()->LineTraceSingleByChannel(HitTrace, StartTrace, EndTrace, ECC_GameTraceChannel3, CollisionParam))
			{
				FRotator Rotation;
				FVector ShotDirection = -Rotation.Vector();

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, HitTrace.Location, ShotDirection.Rotation());

				if (HitTrace.bBlockingHit)
				{
					if (auto *NPC = Cast<AEnemyCharacter>(HitTrace.GetActor()))
					{
						UGameplayStatics::ApplyDamage(NPC, 60.0f, NULL, this, UDamageType::StaticClass());

					}
					if (auto Boss = Cast<ABossEnemyCharacter>(HitTrace.GetActor()))
					{
						UGameplayStatics::ApplyDamage(Boss, 40.0f, NULL, this, UDamageType::StaticClass());
					}
				}
			}

			DecreaseAmmoCount();

			if (CurAmmoCount == 0)
			{
				Character->StartReload();
			}
		}
	}
}

void AWeapon_ShotGun::SpawnEffect()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMesh, TEXT("FirePoint"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMesh, TEXT("FirePoint"));
}
