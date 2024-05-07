// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_HORRORSGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ===========================================================
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	int Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	int Rows;


	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

};
