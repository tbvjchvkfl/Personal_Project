// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircleHPBar.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API UCircleHPBar : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "HPBar", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* HP_Bar;

public:
	UMaterialInstanceDynamic* ProgressBar;

	void SetPercent(float Percent);
};
