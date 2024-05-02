// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORS_GAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	class UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	class UWrapBox* InventoryBox;

};
