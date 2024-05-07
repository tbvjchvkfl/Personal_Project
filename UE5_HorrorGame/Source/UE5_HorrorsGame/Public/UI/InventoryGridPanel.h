// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridPanel.generated.h"

class UBorder;
class UCanvasPanel;
class UCanvasPanelSlot;
class UInventoryComponent;

UCLASS()
class UE5_HORRORSGAME_API UInventoryGridPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	float Tilesize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UBorder *GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel *GridCanvasPanel;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================

	void Init(float ColTilesize, float RowTileSize);
	void CreateLineSegments();
};
