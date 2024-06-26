// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HorrorsHUD.generated.h"

class UInGameHUD;
class UInventory;
class UGameResult;
class UInteractionWidget;

UCLASS()
class UE5_HORRORSGAME_API AHorrorsHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInGameHUD> InGameHUD;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInventory> Inventory;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameResult> Result;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionUI;

	bool bIsMenuVisible;
	bool bIsShowingResult;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AHorrorsHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

	void AddInventoryItem();

	void ShowResult();

	void HideResult();

	void ShowInteract();

	void HideInteract();

	UInGameHUD* GetInGameHUDWIdget() { return InGameHUDWidget; }

protected:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY()
	UInGameHUD *InGameHUDWidget;

	UPROPERTY()
	UInventory *InventoryWidget;

	UPROPERTY()
	UGameResult *GameResultWidget;

	UPROPERTY()
	UInteractionWidget *InteractionWidget;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;

};
