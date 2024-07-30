// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Skill.generated.h"

class ABossEnemyCharacter;

UCLASS()
class UE5_HORRORSGAME_API UBTTask_Skill : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Skill();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)override;

private:

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float SkillRange;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float SkillDelay;

	void AttackSkill(ABossEnemyController *const BossController, UBossEnemyAnimInstance *const BossAnim);

	bool CheckSkill(UBehaviorTreeComponent &TreeComp, ABossEnemyCharacter *const Boss, APlayerCharacter *Player, UBossEnemyAnimInstance *const BossAnimInstance);
};
