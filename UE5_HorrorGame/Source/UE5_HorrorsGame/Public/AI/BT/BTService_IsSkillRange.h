// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsSkillRange.generated.h"


UCLASS()
class UE5_HORRORSGAME_API UBTService_IsSkillRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_IsSkillRange();
	void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float MeleeRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float SkillDelay = 10.0f;

	bool IsDoingSkill(ABossEnemyCharacter* BossEnemy, APlayerCharacter* Target);
};
