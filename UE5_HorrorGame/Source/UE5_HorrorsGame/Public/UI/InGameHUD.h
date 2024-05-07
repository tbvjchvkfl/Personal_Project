// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

class UTextBlock;

UCLASS()
class UE5_HORRORSGAME_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "TEXT", meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock *AmmoCount;


public:
	void Init(int remainAmmoCount, int maxAmmoCount) const;
	void SetAmmoCountText(int remain, int max) const;
	
};
