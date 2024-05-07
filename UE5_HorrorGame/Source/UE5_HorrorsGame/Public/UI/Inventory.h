// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class UButton;
class UWrapBox;

UCLASS()
class UE5_HORRORSGAME_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	//UButton *CloseButton;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = /(BindWidget))
	//UWrapBox *InventoryBox;



	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void NativeConstruct()override;
};
