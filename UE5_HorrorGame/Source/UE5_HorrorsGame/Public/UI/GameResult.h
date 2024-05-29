// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameResult.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class UE5_HORRORSGAME_API UGameResult : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button", meta = (BindWidget))
	UButton *RestartButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button", meta = (BindWidget))
	UButton *Cancle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button", meta = (BindWidget))
	UTextBlock *ResultText;
	class AHorrorsHUD *HUD;
	virtual void NativeConstruct()override;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	UFUNCTION(BlueprintCallable)
	void OnClickedRestartButton();
	//void OnClickedCancleButton();
};