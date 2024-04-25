// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayableCharacter.h"
#include "WeaponActor.generated.h"


UENUM(BlueprintType)
enum class EFireType : uint8
{
	EF_LineTrace UMETA(DisplayName = "Line Trace"),
	EF_Projectile UMETA(DisplayName = "Projectile")
};

UCLASS(Abstract)
class UE5_HORRORS_GAME_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	inline int GetAmmoCount() { return AmmoCount; }
	inline float GetReloadingDelayTime() { return ReloadingDelayTime; }

	

protected:
	UPROPERTY(EditAnywhere, Category = "WeaponMesh")
	class USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	int AmmoCount;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	float ReloadingDelayTime;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	float FireInterval;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	float TraceDistance;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAcceess = "true"))
	EFireType FireType = EFireType::EF_LineTrace;


	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void StartShoot(TWeakObjectPtr<APlayableCharacter> owner);
	virtual void EndShoot();
	virtual void Reloading();

};
