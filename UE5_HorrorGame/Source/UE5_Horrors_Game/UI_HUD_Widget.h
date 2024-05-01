// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_HUD_Widget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API UUI_HUD_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "TEXT", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* AmmoCount;

protected:
	virtual void NativeConstruct() override;

public:
	void Init(int remainAmmoCount, int maxAmmoCount)const;
	void SetAmmoCountText(int remain, int max) const;
};
