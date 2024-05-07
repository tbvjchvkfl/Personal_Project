// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HorrorsHUD.generated.h"

class UMainMenu;
class UInteractionWidget;
struct FInteractableData;

UCLASS()
class UE5_HORRORSGAME_API AHorrorsHUD : public AHUD
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	//UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	//TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	bool bIsMenuVisible;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AHorrorsHUD();
	void DisplayMenu();
	void HideMenu();

	void ShowInteractionWidget();
	void HideInteractionWdiget();
	void UpdateInteractionWidget(const FInteractableData *InteractableData);

protected:

	UPROPERTY()
	UMainMenu *MainMenuWidget;

	//UPROPERTY()
	//UInteractionWidget *InteractionWidget;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	virtual void BeginPlay() override;
};
