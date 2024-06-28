// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UENUM()
enum class EInteractionType : uint8
{
	Pickup UMETA(DisplayName = "PickUp"),
	Device UMETA(DisplayNmae = "Device")
};

//USTRUCT()
//struct FInteractableData
//{
//	GENERATED_USTRUCT_BODY()
//
//	FInteractableData() :
//		InteractionType(EInteractionType::Pickup),
//		Name(FText::GetEmpty()),
//		Action(FText::GetEmpty()),
//		Amount(0),
//		InteractionDuration(0.0f)
//	{
//	};
//
//	UPROPERTY(EditInstanceOnly)
//	EInteractionType InteractionType;
//
//	UPROPERTY(EditInstanceOnly)
//	FText Name;
//
//	UPROPERTY(EditInstanceOnly)
//	FText Action;
//
//	// Used Only PickUp
//	UPROPERTY(EditInstanceOnly)
//	int8 Amount;
//
//	UPROPERTY(EditInstanceOnly)
//	float InteractionDuration;
//};

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class UE5_HORRORSGAME_API IInteractionInterface
{
	GENERATED_BODY()

public:
	EInteractionType InteractionType;

	virtual void Interaction(class APlayerCharacter *Player) = 0;
};
