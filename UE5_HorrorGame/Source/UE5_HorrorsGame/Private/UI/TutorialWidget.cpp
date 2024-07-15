// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TutorialWidget.h"
#include "Components/TextBlock.h"

void UTutorialWidget::SetTutorialText(FString TutoText)
{
	TutorialText->SetText(FText::FromString(TutoText));
}
