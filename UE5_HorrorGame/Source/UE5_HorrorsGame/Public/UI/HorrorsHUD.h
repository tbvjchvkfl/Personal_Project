// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HorrorsHUD.generated.h"

class UInGameHUD;
class UInventory;
class UGameResult;
class UInteractionWidget;
class UTutorialWidget;
class UBossHealthBar;
class UGameQuestUI;

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
	TSubclassOf<UTutorialWidget> TutorialUI;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UBossHealthBar> BossHealthUI;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameQuestUI> QuestUI;

	bool bIsMenuVisible;
	bool bIsShowingResult;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	AHorrorsHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

	void ShowResult(FString Text);

	void HideResult();

	UFUNCTION(BlueprintCallable)
	UInGameHUD* GetInGameHUDWidget() { return InGameHUDWidget; }

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
	UTutorialWidget *TutorialWidget;

	UPROPERTY()
	UBossHealthBar *BossHealth;

	UPROPERTY()
	UGameQuestUI *QuestUIWidget;
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay()override;

};
