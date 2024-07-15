// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

class UTextBlock;
class UInteractionWidget;
class UInventoryComponent;
class UWidgetAnimation;
class UHorizontalBox;
class UTutorialWidget;

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
	UHorizontalBox *CoinHorizon;

	UPROPERTY(meta = (BindWidget))
	UInteractionWidget *InteractUI;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *ShowCoinUI;

	UPROPERTY(meta = (BindWidget))
	UTutorialWidget *TutorialWidget;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void ShowInteractUI() const;
	void HideInteractUI()const;
	void InitializeHUD() const;
	void SetAmmoCountText(int remain, int max) const;
	void SetCoinText(UInventoryComponent* Inventory) const;
	void PlayCoinAnimation();
	void ShowTutorialWidget(FString Text);
	void HideTutorialWidget();
};

