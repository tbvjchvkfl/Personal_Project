// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/TutorialStruct.h"
#include "TutorialBase.generated.h"

/**
 * 
 */


UCLASS()
class UE5_HORRORSGAME_API UTutorialBase : public UObject
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	FTutorialData TutorialData;



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	UTutorialBase();
};
