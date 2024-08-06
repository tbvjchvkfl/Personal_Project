#include "Object/InteractionDoor.h"
#include "Object/LastDoorTrigger.h"
#include "UI/HorrorsHUD.h"
#include "UI/InGameHUD.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AInteractionDoor::AInteractionDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractionType = EInteractionType::Device;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>("LeftDoor");
	LeftDoor->SetupAttachment(CollisionBox);
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>("RightDoor");
	RightDoor->SetupAttachment(CollisionBox);

	bIsInteract = true;
}

void AInteractionDoor::Interaction(APlayerCharacter *Player)
{
	if (DoorTrigger->EnableDoorInteraction)
	{
		bIsInteract = false;
		GetWorldTimerManager().SetTimer(Timerhandle, this, &AInteractionDoor::OpenDoor, 0.01f, true);
	}
	else
	{
		FString QuestString = FString::Printf(TEXT("LOCK"));
		HUD->GetInGameHUDWidget()->ShowQuestWidget(QuestString);
	}
}

void AInteractionDoor::OpenDoor()
{
	LeftRotRate -= 0.1f;
	LeftDoor->SetRelativeRotation(FRotator(0.0f, (- 180.0f + LeftRotRate), 0.0f));

	RightRotRate += 0.1f;
	RightDoor->SetRelativeRotation(FRotator(0.0f, RightRotRate, 0.0f));
	if (RightRotRate >= 90.0f)
	{
		GetWorldTimerManager().PauseTimer(Timerhandle);
		GetWorldTimerManager().ClearTimer(Timerhandle);
	}
}

void AInteractionDoor::BeginPlay()
{
	Super::BeginPlay();
	if (DoorTriggerClass)
	{
		DoorTrigger = Cast<ALastDoorTrigger>(UGameplayStatics::GetActorOfClass(GetWorld(), DoorTriggerClass));
	}
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AInteractionDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

