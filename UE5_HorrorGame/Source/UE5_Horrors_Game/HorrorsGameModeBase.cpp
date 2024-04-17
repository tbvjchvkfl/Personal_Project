// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorsGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AHorrorsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();
}
