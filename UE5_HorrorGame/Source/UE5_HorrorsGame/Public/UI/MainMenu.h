// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class APlayerCharacter;

UCLASS()
class UE5_HORRORSGAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	UPROPERTY()
	APlayerCharacter *PlayerCharacter;
	

protected:
	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void  NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;



	
};