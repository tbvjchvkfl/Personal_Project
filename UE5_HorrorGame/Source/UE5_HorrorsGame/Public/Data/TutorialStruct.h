// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TutorialStruct.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTutorialData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Title;

	UPROPERTY(EditAnywhere)
	FString Description;
};

class UE5_HORRORSGAME_API TutorialStruct
{
public:
	TutorialStruct();
	~TutorialStruct();
};
