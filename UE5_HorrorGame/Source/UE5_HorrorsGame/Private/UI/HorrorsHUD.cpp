// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HorrorsHUD.h"
#include "UI/Inventory.h"

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

void AHorrorsHUD::BeginPlay()
{
	Super::BeginPlay();
	if (Inventory)
	{
		InventoryWidget = CreateWidget<UInventory>(GetWorld(), Inventory);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
