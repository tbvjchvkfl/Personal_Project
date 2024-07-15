// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "Data/TutorialStruct.h"
#include "Engine/DataTable.h"
#include "TutorialTrigger.generated.h"

class UBoxComponent;
class UTutorialBase;
class UTutorialWidget;

//USTRUCT(BlueprintType)
//struct FTutorialData : public FTableRowBase
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere)
//	FString Title;
//
//	UPROPERTY(EditAnywhere)
//	FString Description;
//};

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
	UDataTable *TutorialDataTable;

	UPROPERTY(EditAnywhere, Category = "TutoComp")
	FName DesiredTutoName;

	UPROPERTY(VisibleAnywhere, Category = "TutoComp")
	UTutorialBase *TutorialReference;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	ATutorialTrigger();

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	AHorrorsHUD *HUD;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InitializeTutorial(TSubclassOf<UTutorialBase> BaseClass);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex);

};
