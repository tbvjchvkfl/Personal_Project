// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameResult.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"

void UGameResult::SetResult(FString ResultText)
{
	ResultTitleText->SetText(FText::FromString(ResultText));
}

void UGameResult::OnClickedRestartButton()
{
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	auto Controller = Cast<APlayerController>(GetOwningPlayer());
	if (Controller)
	{
		Controller->RestartLevel();
	}
	HUD->HideResult();
}

