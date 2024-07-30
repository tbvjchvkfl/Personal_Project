// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsScreaming.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UBTService_IsScreaming : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTService_IsScreaming();

	void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	int Count;
};
