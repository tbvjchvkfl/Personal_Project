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
class UBossHealthBar;
class ABossEnemyCharacter;
class UGameQuestUI;

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

	UPROPERTY(meta = (BindWidget))
	UTutorialWidget *TutorialWidget;

	UPROPERTY(meta = (BindWidget))
	UGameQuestUI *QuestUIWidget;

	UPROPERTY(meta = (BindWidget))
	UBossHealthBar *BossHealthBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *ShowCoinUI;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *ShowTutorial;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *HideTutorial;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *ShowQuest;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *HideQuest;

	FTimerHandle Timer;

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
	void ShowBossHealthBar();
	void SetBossHealthBar(ABossEnemyCharacter *Boss);
	void HideBossHealthBar();
	UFUNCTION(BlueprintCallable)
	void ShowQuestWidget(FString UIText);
	void HideQuestWidget();
};

