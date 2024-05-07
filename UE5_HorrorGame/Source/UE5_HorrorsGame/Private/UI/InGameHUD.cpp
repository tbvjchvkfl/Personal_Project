// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "Components/TextBlock.h"

void UInGameHUD::Init(int remainAmmoCount, int maxAmmoCount) const
{
	SetAmmoCountText(remainAmmoCount, maxAmmoCount);
}

void UInGameHUD::SetAmmoCountText(int remain, int max) const
{
	FString string = FString::Printf(TEXT(" %d / %d"), remain, max);
	AmmoCount->SetText(FText::FromString(string));
}
