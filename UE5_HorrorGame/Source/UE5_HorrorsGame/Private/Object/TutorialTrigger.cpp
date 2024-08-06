// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/TutorialTrigger.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Object/TutorialBase.h"
#include "UI/HorrorsHUD.h"
#include "UI/TutorialWidget.h"
#include "UI/InGameHUD.h"

ATutorialTrigger::ATutorialTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision");
	CollisionBox->SetupAttachment(RootComponent);
	
}

void ATutorialTrigger::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATutorialTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATutorialTrigger::OnOverlapEnd);

	InitializeTutorial(UTutorialBase::StaticClass());
}

void ATutorialTrigger::InitializeTutorial(TSubclassOf<UTutorialBase> BaseClass)
{
	if (TutorialDataTable && !DesiredTutoName.IsNone())
	{
		const FTutorialData *TutoData = TutorialDataTable->FindRow<FTutorialData>(DesiredTutoName, DesiredTutoName.ToString());

		TutorialReference = NewObject<UTutorialBase>(this, BaseClass);

		TutorialReference->TutorialData.Title = TutoData->Title;
		TutorialReference->TutorialData.Description = TutoData->Description;
	}

	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ATutorialTrigger::OnOverlapBegin(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const &SweepResult)
{
	if (auto Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (HUD)
		{
			HUD->GetInGameHUDWidget()->ShowTutorialWidget(TutorialReference->TutorialData.Description);
		}
	}
}

void ATutorialTrigger::OnOverlapEnd(UPrimitiveComponent *const OverlapComp, AActor *const OtherActor, UPrimitiveComponent *const OtherComponent, int const OtherBodyIndex)
{
	if (auto Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (HUD)
		{
			HUD->GetInGameHUDWidget()->HideTutorialWidget();
			Destroy();
		}
	}
}



void ATutorialTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}