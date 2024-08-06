// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameQuestUI.generated.h"


UCLASS()
class UE5_HORRORSGAME_API UGameQuestUI : public UUserWidget
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	FTimerHandle Timer;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *QuestText;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	void SetText(FString Text);
	void ShowQuestUI();
	void HideQuestUI();
};
