// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

class UTextBlock;
class UInteractionWidget;

UCLASS()
class UE5_HORRORSGAME_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(BlueprintReadOnly, Category = "TEXT", meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock *AmmoCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *CoinText;

	UPROPERTY(meta = (BindWidget))
	UInteractionWidget *InteractUI;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void ShowInteractUI() const;
	void HideInteractUI()const;
	void InitializeHUD() const;
	void SetAmmoCountText(int remain, int max) const;
	//void SetCoinText(class APlayerCharacter* Player);
};

