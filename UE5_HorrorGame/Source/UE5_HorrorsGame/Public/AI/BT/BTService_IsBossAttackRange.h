// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsBossAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class UE5_HORRORSGAME_API UBTService_IsBossAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_IsBossAttackRange();
	void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 200.0f;
};
