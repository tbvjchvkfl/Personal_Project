// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_0_API APortGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay()override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG Game")
	UUserWidget* CustomWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidget;
};
