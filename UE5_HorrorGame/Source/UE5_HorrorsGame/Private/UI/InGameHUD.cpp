// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "UI/InteractionWidget.h"
#include "UI/TutorialWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Component/InventoryComponent.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Player/PlayerCharacter.h"
#include "Armor/Weapon_Pistol.h"

void UInGameHUD::ShowInteractUI() const
{
	InteractUI->SetVisibility(ESlateVisibility::Visible);
}

void UInGameHUD::HideInteractUI() const
{
	InteractUI->SetVisibility(ESlateVisibility::Collapsed);
}

void UInGameHUD::InitializeHUD() const
{
	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (auto Weapon = Cast<AWeaponBase>(Player->GetCurrentWeapon()))
	{
		int AmmoRemain = Weapon ? Weapon->GetCurAmmo() : 0;
		int AmmoMaxCount = Weapon ? Weapon->GetMaxAmmo() : 0;
		SetAmmoCountText(AmmoRemain, AmmoMaxCount);
	}
	HideInteractUI();
	CoinHorizon->SetVisibility(ESlateVisibility::Collapsed);
}

void UInGameHUD::SetAmmoCountText(int remain, int max) const
{
	FString string = FString::Printf(TEXT("%d / %d"), remain, max);
	AmmoCount->SetText(FText::FromString(string));
}

void UInGameHUD::SetCoinText(UInventoryComponent *Inventory) const
{
	FString CoinString = FString::Printf(TEXT("%d"), Inventory->GetCoinInventory());
	CoinText->SetText(FText::FromString(CoinString));
}

void UInGameHUD::PlayCoinAnimation()
{
	PlayAnimation(ShowCoinUI);
}

void UInGameHUD::ShowTutorialWidget(FString Text)
{
	TutorialWidget->SetTutorialText(Text);
	TutorialWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInGameHUD::HideTutorialWidget()
{
	FString NullString = "";
	TutorialWidget->SetTutorialText(NullString);
	TutorialWidget->SetVisibility(ESlateVisibility::Collapsed);
}
