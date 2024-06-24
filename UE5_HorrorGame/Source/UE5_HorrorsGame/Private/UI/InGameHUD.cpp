// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "Components/TextBlock.h"
#include "UI/InteractionWidget.h"
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

	if (auto Pistol = Cast<AWeapon_Pistol>(Player->Pistol))
	{
		int AmmoRemain = Pistol ? Pistol->GetCurAmmo() : 0;
		int AmmoMaxCount = Pistol ? Pistol->GetMaxAmmo() : 0;
		SetAmmoCountText(AmmoRemain, AmmoMaxCount);
	}
	HideInteractUI();
}

void UInGameHUD::SetAmmoCountText(int remain, int max) const
{
	FString string = FString::Printf(TEXT("%d / %d"), remain, max);
	AmmoCount->SetText(FText::FromString(string));
}

//void UInGameHUD::SetCoinText(class APlayerCharacter *Player)
//{
//	FString CoinString = FString::Printf(TEXT("%d"), Player->GetPlayerCoin());
//	CoinText->SetText(FText::FromString(CoinString));
//}
