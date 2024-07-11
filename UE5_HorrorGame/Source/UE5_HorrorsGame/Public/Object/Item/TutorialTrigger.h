// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialTrigger.generated.h"

class UBoxComponent;

UCLASS()
class UE5_HORRORSGAME_API ATutorialTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(VisibleAnywhere, Category = "TutoComp")
	UBoxComponent *CollisionBox;

	UPROPERTY(EditAnywhere, Category = "TutoComp")
	UDataTable *TutorialData;

	UPROPERTY(EditAnywhere, Category = "TutoComp")
	FName DesiredTutoName;

	//UPROPERTY(VisibleAnywhere, Category = "TutoComp")
	FTutorialData* TutorialReference;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	ATutorialTrigger();

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InitializeTutorial();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);

};
