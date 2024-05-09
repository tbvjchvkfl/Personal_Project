// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HorrorsHUD.generated.h"

class UInGameHUD;
class UInventory;

UCLASS()
class UE5_HORRORSGAME_API AHorrorsHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInGameHUD> InGameHUD;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInventory> Inventory;

	bool bIsMenuVisible;

	AHorrorsHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

protected:
	UPROPERTY()
	UInGameHUD *InGameHUDWidget;

	UPROPERTY()
	UInventory *InventoryWidget;

	virtual void BeginPlay()override;

};
