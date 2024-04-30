// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HUD_Widget.h"
#include "PistolWeapon.h"
#include "Components/TextBlock.h"

void UUI_HUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_HUD_Widget::Init(int remainAmmoCount, int maxAmmoCount) const
{
	SetAmmoCountText(remainAmmoCount, maxAmmoCount);
}

void UUI_HUD_Widget::SetAmmoCountText(int remain, int max) const
{
	FString string = FString::Printf(TEXT(" %d / %d"), remain, max);
	AmmoCount->SetText(FText::FromString(string));
}
