Horror's Game
-
맵을 이동하며 좀비들을 무찌르는 3인칭 슈팅게임입니다.

플레이 영상
-
https://github.com/user-attachments/assets/f5c660a7-af4e-4ae2-80ee-15186c0162e6




전체 기능 구현
-
<table>
  <tr>
    <th colspan = "4">기능 구현 항목</th>
  </tr>
  <tr>
    <th>이동</th>
    <th>달리기</th>
    <th>조준</th>
    <th>사격</th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/1af7edfc-939b-41b0-afa7-d874ea87da34" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/1d0033b9-33a4-40e3-8c9f-0de0a14c8903" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/8b5355f4-b95a-45a2-a6ee-24bdd15bc133" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/6dd322c9-5d44-4b05-8ec6-423c6972ab4c" width = "200" heigh = "150"></td>
  </tr>
   <tr>
    <th>재장전</th>
    <th>인벤토리와 상호작용</th>
    <th>NPC 상태별 패턴</th>
    <th>NPC 거리별 패턴</th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/7c31e4ec-1c07-4263-8699-792856c3c2da" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/087e7fa1-5028-4b81-96e8-8ad277d1deda" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/0903da17-99f3-4dcf-98b3-124d17400f14" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/ff23c1b4-712b-4bc5-a306-0fe5048c75f4" width = "200" heigh = "150"></td>
  </tr>
   <tr>
    <th>히트 리액션과 원형 체력바</th>
    <th>튜토리얼 트리거</th>
    <th>결과 화면 UI</th>
    <th></th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/77a1bc56-7394-4e58-8aff-3bd5024b9f86" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/5bd25b9d-eaa7-4ca2-8069-b9b835d8254e" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/8fc87a91-791b-4eee-822a-55862598daf0" width = "200" heigh = "150"></td>
    <td></td>
  </tr>
   <tr>
    <th>레벨 오브젝트 <문></th>
    <th>레벨 오브젝트 <도깨비 불></th>
    <th>포스트 프로세스 볼륨 <안개></th>
    <th></th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/d0081894-e4ff-48ff-9d3f-840382566ba4" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/416a295c-0af3-45ed-b5b6-a3de1f01ad27" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/8757b28e-6196-41e0-99ee-64858a570d3a" width = "200" heigh = "150"></td>
    <td></td>
  </tr>
</table>

핵심 기능
-
> - DataTable을 활용한 Item과 Tutorial 기능
> - NPC의 상태별 행동패턴과 보스 NPC의 거리에 따른 공격 패턴
> - HUD를 활용한 전체 UI 관리
> - Actor Component와 Interface를 활용한 Inventory 기능

핵심 기능 설명
-

<details>
	<summary style = "font-size: 24px;">DataTable을 활용한 Item과 Tutorial 기능 (Click!)</summary>
<p>
	
> ### DataTable을 활용한 Item과 Tutorial 기능 ###
> - 빈 클래스에 데이터로 활용할 변수들을 struct로 묶어 선언해주었습니다. 그리고, 에디터에서 데이터 테이블 에셋으로 사용하기 위해 #include "Engine/DataTable.h"를 추가해주었습니다.
<pre>
  <code>
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
======================= ItemStruct.h =======================
UENUM()
enum class EItemType : uint8
{
	Armor UMETA(DisplayName = "Armor"),
	Weapon UMETA(DisplayName = "Weapon"),
	Coin UMETA(DisplayName = "Coin"),
	Consumable UMETA(DisplayName = "Consumable")
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D *Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh *Mesh;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "ItemData")
	int32 Amount;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemAssetData AssetData;
};
======================= ItemStruct.h =======================
	  
======================= TutorialStruct.h =======================
USTRUCT(BlueprintType)
struct FTutorialData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Title;

	UPROPERTY(EditAnywhere)
	FString Description;
};
======================= TutorialStruct.h =======================
  </code>
</pre>
> - 그리고, UObject타입의 클래스를 하나 더 생성하여 위 정보들을 각각 ItemBase와 TutorialBase라는 이름으로 복사해주었습니다. 
> - 앞 서 만들었던 ItemStruct와 TutorialStruct 만으로도 테이블 에셋과 바인딩하여 사용할 수는 있었지만, Item의 경우 게임에서 내 임의의 변수의 값이 바뀌게 될 경우(예를 들어 아이템을 획득한 후 아이템을 사용해서 아이템의 수량이 줄었을 때) 테이블에 있는 값까지 변경되는 이슈가 생겨 복사본을 만들어 테이블에 입력한 값은 변경되지 않도록 해주었습니다.
<pre>
  <code>
======================= ItemStruct.h =======================
#pragma once

#include "CoreMinimal.h"
#include "Data/ItemStruct.h"
#include "ItemBase.generated.h"


class UInventoryComponent;

UCLASS()
class UE5_HORRORSGAME_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	// ===========================================================
	// =                  Variable / Property		     =
	// ===========================================================
	UPROPERTY()
	UInventoryComponent *OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	int32 Amount;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemAssetData AssetData;
		
	// ===========================================================
	// =			 Functionary	   		     = 
	// ===========================================================
	UItemBase();

	UItemBase *CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	virtual void Use(class APlayerCharacter *Character);

protected:
	bool operator== (const FName &OtherID)
	{
		return this->ID == OtherID;
	}
};

	  
======================= TutorialStruct.h =======================
#pragma once

#include "CoreMinimal.h"
#include "Data/TutorialStruct.h"
#include "TutorialBase.generated.h"

UCLASS()
class UE5_HORRORSGAME_API UTutorialBase : public UObject
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property		     =
	// ===========================================================
	FTutorialData TutorialData;



	// ===========================================================
	// =			Functionary	   		     = 
	// ===========================================================
	UTutorialBase();
};
  </code>
</pre>
> - 이 후, 캐릭터와 실제로 인터렉션 하게되는 액터인 PickupItem과 TutorialTrigger를 만들어 UDataTable에 있는 FindRow함수를 사용하여 데이터테이블의 행을 가져오고, NewObject함수를 사용해서 테이블의 데이터를 아이템에 바인딩해주었습니다.
> - Item의 경우 실제 업무를 하게되었을 때, 기획자들이 레벨에 아이템을 배치할 경우 Item에 설정한 데이터에 맞게 외형이 즉시 변경되어 보일 수 있도록 PostEditChangeProperty함수를 사용하여 아이템의 Mesh를 연결해주었습니다. 
<pre>
  <code>
======================= PickUpItem.cpp =======================
	  
#include "Object/Item/PickUpItem.h"
#include "Object/Item/ItemBase.h"

void APickUpItem::BeginPlay()
{
	Super::BeginPlay();

	InitializePickUp(UItemBase::StaticClass());
	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APickUpItem::OnOverlapEnd);
}

void APickUpItem::InitializePickUp(const TSubclassOf<UItemBase> BaseClass)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData *ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);
		
		ItemReference->ID = ItemData->ID;
		ItemReference->Amount = ItemData->Amount;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;

		ItemMesh->SetStaticMesh(ItemData->AssetData.Mesh);
	}
}

void APickUpItem::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickUpItem, DesiredItemID))
	{
		if (ItemDataTable)
		{
			const FString ContextString{ DesiredItemID.ToString() };

			if (const FItemData *ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				ItemMesh->SetStaticMesh(ItemData->AssetData.Mesh);
			}
		}
	}
}

======================= PickUpItem.cpp =======================
				
#include "Object/TutorialTrigger.h"
#include "Object/TutorialBase.h"
				
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
}
				
  </code>
</pre>

</p>
</details>


<details>
	<summary>Actor Component와 Interface를 활용한 Inventory 기능 (Click!)</summary>
	<p>

  > ### Actor Component와 Interface를 활용한 Inventory 기능 ###
> - Inventory기능을 구현할 때, Unreal Interface와 Actor Component를 사용해서 클래스간의 유연성과 기능의 확장성을 고려하여 구현하였습니다.
> - InteractionInterface에 Interaction함수를 순수가상함수로 만들어 해당 클래스를 상속받는 클래스에서 override하여 사용하였습니다.
> - 이후, PlayerCharacter에서 LineTrace기능을 사용하여 PickUpItem의 미리 생성해둔 CollisionSphere에 Hit했을 경우 HitResult에 GetActor함수를 InteractionInterface로 형변환하여 Interaction함수를 호출해주었습니다.
<pre>
  <code>

======================= InteractionInterface.h =======================
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

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

======================= PlayerCharacter.cpp =======================

void APlayerCharacter::Interaction()
{
	FVector TraceStart{ GetPawnViewLocation() + FVector(5.0f, 8.0f, 10.0f)};
	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel2, QueryParams))
	{
		if (TraceHit.bBlockingHit)
		{
			if (auto item = Cast<APickUpItem>(TraceHit.GetActor()))
			{
				InteractableInterface = TraceHit.GetActor();
				InteractableInterface->Interaction(this);
			}
			if (auto Devie = Cast<AInteractionDoor>(TraceHit.GetActor()))
			{
				InteractableInterface = TraceHit.GetActor();
				InteractableInterface->Interaction(this);
			}
			if (auto Device = Cast<AInteractionDoorSingle>(TraceHit.GetActor()))
			{
				InteractableInterface = TraceHit.GetActor();
				InteractableInterface->Interaction(this);
			}
		}
	}
}

======================= PickUpItem.cpp =======================
				
void APickUpItem::Interaction(class APlayerCharacter *Player)
{
	if (Player)
	{
		TakePickUp(Player);
	}
}

void APickUpItem::TakePickUp(APlayerCharacter *Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UInventoryComponent *PlayerInventory = Taker->GetInventory())
			{
				PlayerInventory->AddItem(ItemReference);
				Destroy();
			}
		}
	}
}
  </code>
</pre>

> - 그리고, ActorComponent클래스를 만들어 Inventory 기능을 구현하고 PlayerCharacter에 컴포넌트를 추가하였습니다.
<pre>
 <code>
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemBase;
class AHorrorsHUD;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_HORRORSGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property   		     =
	// ===========================================================
	
	// 델리게이트 인벤토리 내용 업데이트용
	FOnInventoryUpdate OnInventoryUpdated;

	// ===========================================================
	// =		        Functionary			     = 
	// ===========================================================
	UInventoryComponent();

	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItemBase *> GetItemInventory()const { return ItemInventory; };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE int32 GetCoinInventory() const { return CoinInventory; }

	UFUNCTION(Category = "Inventory")
	void AddItem(UItemBase *Item);

protected:
	// ===========================================================
	// =                  Variable / Property		     =
	// ===========================================================

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 CoinInventory;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> ItemInventory;

	AHorrorsHUD *UIComp;

	// ===========================================================
	// =			Functionary			     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
 </code>
</pre>

	</p>
</details>

<details>
	<summary>HUD를 활용한 전체 UI 관리 (Click!)</summary>
	<p>
		
> ### HUD를 활용한 전체 UI 관리 ###
> - 게임 내 모든 UI를 HUD에서 처음으로 생성하고 관리될 수 있도록 구현했습니다.
> - HUD의 BeginPlay함수에서 게임 내 모든 UI들을 생성하고 세팅해주었습니다.
<pre>
  <code>
======================= AHorrorsHUD.h =======================
UCLASS()
class UE5_HORRORSGAME_API AHorrorsHUD : public AHUD
{
	GENERATED_BODY()
public:
	// ===========================================================
	// =                  Variable / Property		     =
	// ===========================================================
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInGameHUD> InGameHUD;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInventory> Inventory;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameResult> Result;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UTutorialWidget> TutorialUI;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UBossHealthBar> BossHealthUI;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameQuestUI> QuestUI;

	bool bIsMenuVisible;
	bool bIsShowingResult;
	// ===========================================================
	// =			  Functionary	   		     = 
	// ===========================================================
	AHorrorsHUD();

	void DisplayMenu();
	void HideMenu();

	void ToggleMenu();

	void ShowResult(FString Text);

	void HideResult();

	UFUNCTION(BlueprintCallable)
	UInGameHUD* GetInGameHUDWidget() { return InGameHUDWidget; }

protected:
	// ===========================================================
	// =                  Variable / Property		     =
	// ===========================================================
	UPROPERTY()
	UInGameHUD *InGameHUDWidget;

	UPROPERTY()
	UInventory *InventoryWidget;

	UPROPERTY()
	UGameResult *GameResultWidget;

	UPROPERTY()
	UTutorialWidget *TutorialWidget;

	UPROPERTY()
	UBossHealthBar *BossHealth;

	UPROPERTY()
	UGameQuestUI *QuestUIWidget;
	// ===========================================================
	// =			 Functionary	   		     = 
	// ===========================================================
	virtual void BeginPlay()override;

};

======================= AHorrorsHUD.cpp =======================
void AHorrorsHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InGameHUD)
	{
		InGameHUDWidget = CreateWidget<UInGameHUD>(GetWorld(), InGameHUD);
		InGameHUDWidget->AddToViewport();
		InGameHUDWidget->SetVisibility(ESlateVisibility::Visible);
	}
	if (Inventory)
	{
		InventoryWidget = CreateWidget<UInventory>(GetWorld(), Inventory);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Result)
	{
		GameResultWidget = CreateWidget<UGameResult>(GetWorld(), Result);
		GameResultWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (TutorialUI)
	{
		TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), TutorialUI);
		TutorialWidget->AddToViewport();
		TutorialWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (BossHealthUI)
	{
		BossHealth = CreateWidget<UBossHealthBar>(GetWorld(), BossHealthUI);
		BossHealth->AddToViewport();
		BossHealth->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (QuestUI)
	{
		QuestUIWidget = CreateWidget<UGameQuestUI>(GetWorld(), QuestUI);
		QuestUIWidget->AddToViewport();
		QuestUIWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
  </code>
</pre>
> 이 후, 각 UI들을 상황에 맞게 Visibility 상태를 변경해주는 것으로 구현했습니다.

	</p>
</details>

<details>
	<summary>NPC의 상태별 행동패턴과 보스 NPC의 거리별 공격 패턴 (Click!)</summary>
	<p>
		
> ### NPC의 상태별 행동패턴과 보스 NPC의 거리별 공격 패턴 ###
> - NPC와의 전투를 구현할 때, 상태별 행동 패턴과 거리별 행동패턴으로 나누어 구현해보았습니다.
> - 우선, 상태별 패턴은 NPC의 AIController에서 만들었던 Perception System을 활용하여 NPC가 PlayerCharacter를 발견했을 때와 발견하지 못했을 때로 나누어 주었습니다.
<pre>
  <Code>
======================= AHorrorsHUD.cpp =======================
	  
void AAI_Controller::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		SightConfig->SightRadius = 500.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AAI_Controller::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
{
	if (auto *const ch = Cast<APlayerCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
  </Code>
</pre>
> - UNavigationSystemV1에 있는 GetCurrent함수를 사용하여 현재 위치를 저장해주었고, GetRandomPointInNavigableRadius 함수를 사용하여 특정한 범위내에서 랜덤하게 위치를 찾도록 구현해주었습니다.
> - 이 후, NPC가 PlayerCharacter를 발견하지 못했다면 FindRandomLocation -> MoveTo -> Wait 순으로 반복될 수 있도록 Sequence노드로 연결하여 구현하였습니다.
<pre>
  <code>
======================= BTTask_FindRandomLocation.cpp =======================
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	if (AAI_Controller *const Controll = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto *const NPC = Controll->GetPawn())
		{
			FVector const Origin = NPC->GetActorLocation();
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
  </code>
</pre>

![스크린샷 2024-09-02 145103](https://github.com/user-attachments/assets/ba149f08-e1a6-4140-b36b-4a1bb17d5271)

> - NPC가 PlayerCharacter를 발견했다면 기존 랜덤하게 방향으로 찾아 이동하는 상태에서 벗어나 PlayerCharacter의 위치로 이동 할 수 있도록, FindPlayerLocation노드를 만들어 주었습니다.
> - 이 역시, Sequence노드로 연결하여 FindPlayerLocation -> MoveTo -> Wait의 행동을 반복하게끔 구현하였습니다.
> - 또한, MoveTo로 이동을 설정 할 경우 PlayerCharacter의 위치를 최초 한번만 탐색하여 해당 위치로 이동하는 현상이 있었습니다. 개인적으로는 NPC가 PlayerCharacter를 발견하고 해당 위치로 이동하는 동안 PlayerCharacter가 움직이면 바뀐 위치로 따라서 이동하게 구현하고 싶었기에 ChasingPlayer노드를 별도로 만들어 UAIBlueprintHelperLibrary에 있는 SimpleMoveToLocation노드를 사용하여 계속해서 Player의 위치를 업데이트하여 이동할 수 있도록 하였고, 비헤이비어트리 역시 FindPlayerLocation -> MoveTo -> Wait으로 변경해주었습니다.

<pre>
  <code>
======================= BTTask_FindPlayerLocation.cpp =======================
EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	if (auto *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		auto const PlayerLocation = Player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation Loc;

			if (auto *const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

======================= BTTask_ChasingPlayer.cpp =======================	
	  
EBTNodeResult::Type UBTTask_ChasingPlayer::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	if(auto *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

  </code>
</pre>

![image](https://github.com/user-attachments/assets/2f44f7ed-df15-4ab5-b13d-4a3a7cc1f21f)
> - 이 후, BT_Service노드를 사용하여 Player가 NPC의 특정 범위 안에 있을 경우 근접 공격을 실행할 수 있도록 구현해주었습니다.

<pre>
  <Code>
======================= BTTask_MeleeAttack.cpp =======================	
	  
EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    auto const *const Controller = OwnerComp.GetAIOwner();
    if (auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn()))
    {
        if (auto *const iCombat = Cast<IEnemyCombatInterface>(NPC))
        {
            if (MontageHasFinished(NPC))
            {
                iCombat->Execute_MeleeAttack(NPC);
            }
        }
    }
    if (auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn()))
    {
        if (BossMontageHasFinished(Boss))
        {
            Boss->PlayAttackAnim();
        }
    }
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
	    
bool UBTTask_MeleeAttack::MontageHasFinished(AEnemyCharacter *const NPC)
{
    return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetAttackMontage());
}

bool UBTTask_MeleeAttack::BossMontageHasFinished(ABossEnemyCharacter *const Boss)
{
    return Boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Boss->GetAttackAnimation());
}

	    
======================= BTService_IsPlayerInMeleeRange.cpp =======================	
void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	auto const *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());

	auto const *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), NPC->GetDistanceTo(Player) <= MeleeRange);
}
  </Code>
</pre>

![image](https://github.com/user-attachments/assets/a0fe3856-4d87-458e-b2dd-9653e209d725)

> - 보스 NPC의 경우 자기 자신과 PlayerCharacter 간의 거리에 따라 다른 행동을 할 수 있도록 구현하고 쿨타임 시스템 또한 구현해보았습니다.
> - CollTime 기능은 SetTimer함수를 사용하여 구현하였으며, Lambda를 사용했습니다.
<Pre>
  <code>
======================= BTTask_Skill.cpp =======================	
EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    auto *const Controller = Cast<ABossEnemyController>(OwnerComp.GetAIOwner());

    auto *const Boss = Cast<ABossEnemyCharacter>(Controller->GetPawn());

    auto *const BossEnemyAnimInstance = Cast<UBossEnemyAnimInstance>(Boss->GetMesh()->GetAnimInstance());

    auto *const Target = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (!CheckSkill(OwnerComp, Boss, Target, BossEnemyAnimInstance))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }
    else
    {
        AttackSkill(Controller, BossEnemyAnimInstance);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
}

void UBTTask_Skill::AttackSkill(ABossEnemyController* const BossController, UBossEnemyAnimInstance* const BossAnim)
{
    BossController->StopMovement();
    BossAnim->DoSkill(SkillDelay);
}

bool UBTTask_Skill::CheckSkill(UBehaviorTreeComponent &TreeComp, ABossEnemyCharacter *const Boss, APlayerCharacter *Player, UBossEnemyAnimInstance *const BossAnimInstance)
{
    if (Boss->GetDistanceTo(Player) >= SkillRange && !BossAnimInstance->GetCoolTime())
    {
        TreeComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        return true;
    }
    else
    {
        TreeComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        return false;
    }
    
}
	    
======================= BossEnemyAnimInstance.cpp =======================	
void UBossEnemyAnimInstance::AttackCoolDown(float CoolTime)
{
	if (!bIsCoolTime)
	{
		bIsCoolTime = true;
		GetWorld()->GetTimerManager().SetTimer
		(TimerHandle,
		[this]()
			{
				bIsCoolTime = false;
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			},
		CoolTime,
		false
		);
	}
}
  </code>
</Pre>

	</p>
</details>


시행 착오
-

> - Player가 원거리 공격을 할 때 Projectile방식이 아니라 LineTrace방식으로 구현해보고자 LineTraceSingleByChannel을 사용하여 사격하는 것 까지는 구현을 하였으나, 바닥을 제외한 다른 Actor들과는 Collision이 발생하지 않아 다른 Actor와 상호작용을 할 수 없었습니다.</br>처음엔 Unreal Document에 FResult에 대한 부분을 살펴보기도 하고 FResult->GetActor() 함수를 응용하여 해결해보려하였으나 마찬가지로 EnemyCharacter와는 Collision이 발생하지 않았습니다. 결국 구글링을 통해 Collision 세팅에 대해서 알게 되었고, EnemyCharacter에 있는 CapsuleCollision의 Trace를 Block으로 바꾸어 Collision이 발생하지 않았던 문제를 해결했습니다.

> - Inventory를 구현할 때 Player에 있는 Item을 담을 배열의 정보를 InventoryUI에 있는 배열로 복사하고, InventoryUI의 ShowInventory함수가 실행될 때마다 AddChild가 실행되어 획득한 정보를 표시해주는 방식으로 구현했었는데, 이 때, Player의 배열 정보를 매번 받아오게되어 획득한 아이템이 계속 중복되어 표시되는 이슈가 있었습니다.</br> 문제를 수정하는 과정에서 Plyayer에 있는 배열 정보가 Inventory로 복사 되었다면 Player에 있는 배열은 empty상태로 바꾸어 주는 방식으로 해당 문제를 해결하긴 하였으나 코드가 난잡해지고 스스로 보기에도 맘에 들지 않아 다른 사람들의 코드를 참고하였고, 델리게이트를 사용한 방식을 알게되어 아이템을 획득하였다면 Inventory의 배열에 자동으로 해당 아이템의 정보가 추가될 수 있도록 수정하였습니다.

> - Boss NPC와의 전투를 구현할 때, SetTimer함수에 람다를 이용해서 Boss NPC의 원거리 공격에 쿨타임 기능을 만들었었는데 Boss가 죽고 레벨에서 Destroy된 후 SetTimer에 사용한 Lambda에서 계속해서 크래쉬가 발생하는 이슈가 있었습니다. 처음엔 Lambda를 잘못 사용했나 하는 생각에 SetTimer함수의 로직과 Lambda를 살펴보았으나 Lambda에는 잘못된 부분이 없다고 생각하여 문제를 수정하지 못하고 있었습니다. 이 후, 계속해서 디버깅을 하던 중 Boss가 죽으면 Character는 사라지지만 레벨에 Boss의 Controller가 사라지지 않고 계속해서 남아있었다는 사실을 알게되었습니다. 확인해보니 실제로 Boss가 죽은 후에 Controller에 있던 TargetDeteced함수는 여전히 동작하고 있었고, 때문에 Controller클래스에 있던 일부 함수들이 Boss가 죽은 후 Controller에 있던 Boss의 일부 포인터가 nullptr이 되면서 발생한 이슈라는 것을 알 수 있었습니다. 이 후, Boss가 죽으면 BossController의 Unpossess함수를 함께 호출해주어 해당 문제를 해결했습니다.
