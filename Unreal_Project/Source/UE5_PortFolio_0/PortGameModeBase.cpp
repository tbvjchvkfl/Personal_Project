// Fill out your copyright notice in the Description page of Project Settings.


#include "PortGameModeBase.h"
#include "Blueprint/UserWidget.h"

void APortGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CustomWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CustomWidget->AddToViewport();
}
