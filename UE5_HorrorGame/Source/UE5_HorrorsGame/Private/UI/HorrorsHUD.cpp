// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "UI/Inventory.h"
#include "UI/GameResult.h"
#include "UI/InteractionWidget.h"

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

void AHorrorsHUD::AddInventoryItem()
{
	if (Inventory)
	{
		InventoryWidget->AddItemToInventory();
	}
}

void AHorrorsHUD::ShowResult()
{
	if (GameResultWidget)
	{
		bIsShowingResult = true;
		GameResultWidget->AddToViewport();
		GameResultWidget->SetVisibility(ESlateVisibility::Visible);
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

void AHorrorsHUD::ShowInteract()
{
	if (InteractionWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHorrorsHUD::HideInteract()
{
	if (InteractionWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
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
	
	if (InteractionUI)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionUI);
		InteractionWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
