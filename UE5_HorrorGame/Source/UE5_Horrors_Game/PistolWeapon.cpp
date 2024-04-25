// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolWeapon.h"
#include "Camera/CameraComponent.h"

APistolWeapon::APistolWeapon()
{
	AmmoCount = 15.0f;
	ReloadingDelayTime = 3.0f;
	FireInterval = 1.0f;
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
				GetWorldTimerManager().SetTimer(FireTimerHandle, [&Character, this]() {return FireWithLineTrace(Character); }, FireInterval, true);
				break;
			case EFireType::EF_Projectile:
				break;
		}
	}
}

void APistolWeapon::FireWithLineTrace(APlayableCharacter* owner)
{
	auto Start = WeaponMesh->GetSocketLocation("FirePoint");
	auto EndPoint = owner->FollowCamera;
	auto EndLocation = EndPoint->GetActorLocation();
	GetWorld()->LineTraceSingleByChannel
}
