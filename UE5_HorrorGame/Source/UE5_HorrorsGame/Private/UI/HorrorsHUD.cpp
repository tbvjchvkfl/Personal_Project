// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HorrorsHUD.h"
#include "UI/MainMenu.h"

AHorrorsHUD::AHorrorsHUD()
{
}

void AHorrorsHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHorrorsHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHorrorsHUD::ShowInteractionWidget()
{
	/*if (InteractionWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}*/
}

void AHorrorsHUD::HideInteractionWdiget()
{
	/*if (InteractionWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}*/
}

void AHorrorsHUD::UpdateInteractionWidget(const FInteractableData *InteractableData)
{
	/*if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}*/
}

void AHorrorsHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport();
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	/*if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport();
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}*/
}
