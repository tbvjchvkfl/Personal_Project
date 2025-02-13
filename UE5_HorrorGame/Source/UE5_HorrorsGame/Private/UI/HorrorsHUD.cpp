// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "UI/Inventory.h"
#include "UI/GameResult.h"
#include "UI/InteractionWidget.h"
#include "UI/TutorialWidget.h"
#include "UI/BossHealthBar.h"
#include "UI/GameQuestUI.h"

AHorrorsHUD::AHorrorsHUD()
{
}

void AHorrorsHUD::DisplayMenu()
{
	if (InventoryWidget)
	{
		bIsMenuVisible = true;
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHorrorsHUD::HideMenu()
{
	if (InventoryWidget)
	{
		bIsMenuVisible = false;
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHorrorsHUD::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AHorrorsHUD::ShowResult(FString Text)
{
	if (GameResultWidget)
	{
		bIsShowingResult = true;
		GameResultWidget->AddToViewport();
		GameResultWidget->SetVisibility(ESlateVisibility::Visible);
		GameResultWidget->SetResult(Text);
		FInputModeUIOnly UIInputMode;
		GetOwningPlayerController()->SetInputMode(UIInputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
		GetOwningPlayerController()->Pause();
	}
}

void AHorrorsHUD::HideResult()
{
	if (GameResultWidget)
	{
		bIsShowingResult = false;
		GameResultWidget->SetVisibility(ESlateVisibility::Collapsed);
		FInputModeGameOnly GameInput;
		GetOwningPlayerController()->SetInputMode(GameInput);
	}
}

void AHorrorsHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InGameHUD)
	{
		InGameHUDWidget = CreateWidget<UInGameHUD>(GetWorld(), InGameHUD);
		InGameHUDWidget->AddToViewport();
		InGameHUDWidget->SetVisibility(ESlateVisibility::Visible);
	}
	if (Inventory)
	{
		InventoryWidget = CreateWidget<UInventory>(GetWorld(), Inventory);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Result)
	{
		GameResultWidget = CreateWidget<UGameResult>(GetWorld(), Result);
		GameResultWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (TutorialUI)
	{
		TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialUI);
		TutorialWidget->AddToViewport();
		TutorialWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (BossHealthUI)
	{
		BossHealth = CreateWidget<UBossHealthBar>(GetWorld(), BossHealthUI);
		BossHealth->AddToViewport();
		BossHealth->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (QuestUI)
	{
		QuestUIWidget = CreateWidget<UGameQuestUI>(GetWorld(), QuestUI);
		QuestUIWidget->AddToViewport();
		QuestUIWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
