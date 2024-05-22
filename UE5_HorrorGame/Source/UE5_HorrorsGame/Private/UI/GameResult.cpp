// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameResult.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HorrorsHUD.h"

void UGameResult::NativeConstruct()
{
	FString WinString = FString::Printf(TEXT("You Win"));
	FString LoseString = FString::Printf(TEXT("You Lose"));

	auto *const Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (Player->GetCurHealth() <= 0)
	{
		ResultText->SetText(FText::FromString(LoseString));
	}
	else
	{
		ResultText->SetText(FText::FromString(WinString));
	}
}

void UGameResult::OnClickedRestartButton()
{
	auto Controller = Cast<APlayerController>(GetOwningPlayer());
	//auto *GameMode = Cast<AHorrorsGameModeBase>(GetOwningPlayer());
	//UGameplayStatics::OpenLevel(GetWorld(), "TestLevel");
	if (Controller)
	{
		Controller->RestartLevel();
	}
	HUD->HideResult();
	//GameMode->ResetLevel();
}

//void UGameResult::OnClickedCancleButton()
//{
//	auto Controller = Cast<APlayerController>(GetOwningPlayer());
//	Controller->EndPlay
//}

