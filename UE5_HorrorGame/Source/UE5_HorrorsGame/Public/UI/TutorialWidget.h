// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class UE5_HORRORSGAME_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TutorialText;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void NativeConstruct() override;
	void SetTutorialText();
};
