// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameQuestUI.h"
#include "Components/TextBlock.h"

void UGameQuestUI::SetText(FString Text)
{
	QuestText->SetText(FText::FromString(Text));
}

void UGameQuestUI::ShowQuestUI()
{
}

void UGameQuestUI::HideQuestUI()
{
}
