// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API AHorrorsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG GAME")
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG GAME")
	TSubclassOf<UUserWidget> HUDWidget;
	
};
