// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UE5_HORRORS_GAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MyState")
	float myHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyState")
	float myMaxhealth;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

public:
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Attack_AnimMontage;
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* BeHit_AnimMontage;
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimMontage;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;
};
