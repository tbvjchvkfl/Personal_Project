Horror's Game
-
맵을 이동하며 좀비들을 무찌르는 3인칭 공포게임입니다.

플레이 영상
-
https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/f6b6c91a-f6d2-4659-9956-b415d3347c62

제작 기간 & 사용 기술
-
> #### 제작 기간
>   - 30일 소요 (개인)

> #### 사용 기술
>   - Unreal C++ & Blueprint

핵심 기능
-
> - 데이터 테이블을 활용한 Item, Inventory, Tutorial 기능
> - FSM 활용 AI와 거리에 따른 보스의 공격 패턴


기능 구현
-

> ### Player Character
>   - 이동
>       - 키보드 WASD 버튼에 키를 할당하고 AddtoMovement함수를 사용하여 구현하였으며, Yaw회전을 적용시켜 입력된 버튼의 방향으로 Yaw회전할 수 있게 구현했습니다.
>      - <pre>
>         <code>
>              void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
>              {
>                Super::SetupPlayerInputComponent(PlayerInputComponent);
>                //축 매핑
>              	 PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
>                 PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
>              } 
>              void APlayerCharacter::MoveForward(float Value)
>              {
>     	         FRotator NewRotation(0, Controller->GetControlRotation().Yaw, 0);
>     	         FVector NewDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
>     	         AddMovementInput(NewDirection, Value);
>              }
>              void APlayerCharacter::MoveRight(float Value)
>              {
>     	         FRotator NewRotation(0, Controller->GetControlRotation().Yaw, 0);
>     	         FVector NewDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::Y);
>     	         AddMovementInput(NewDirection, Value);
>              }
>        </code>
>     </pre>
>   
>     - 예시 영상
>
>   - 조준
>     - 마우스 오른쪽 버튼에 키를 할당하고 해당 버튼 입력 시 카메라 스프링암의 길이를 조절하여 카메라를 'Zoom'할 수 있게 구현하였고, CharacterMovementCompoenent의 MoveSpeed를 조절하여 조준을 하고 있으면 이동속도가 걷기 속도로 변경되게 하였습니다.
>     - <pre>
>         <code>
>              void APlayerCharacter::Tick(float DeltaTime)
>              {
>              	  Super::Tick(DeltaTime);
>              	  {
>              		if(bAimming)
>              		{
>              			ZoomFactor += DeltaTime / 0.2f;
>              			GetCharacterMovement()->bOrientRotationToMovement = false;
>              			GetCharacterMovement()->bUseControllerDesiredRotation = true;
>              		}
>              		else
>              		{
>              			ZoomFactor -= DeltaTime / 0.2f;
>              			GetCharacterMovement()->bOrientRotationToMovement = true;
>              			GetCharacterMovement()->bUseControllerDesiredRotation = false;
>              		}
>                 // 카메라 조절              
>              		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
>              		FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
>              		CameraBoom->TargetArmLength = FMath::Lerp<float>(200.0f, 100.0f, ZoomFactor);
>                }
>              }
>              void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
>              {
>              	Super::SetupPlayerInputComponent(PlayerInputComponent);
>               // 입력 매핑
>              	PlayerInputComponent->BindAction("Aimming", IE_Pressed, this, &APlayerCharacter::StartAimming);
>              	PlayerInputComponent->BindAction("Aimming", IE_Released, this, &APlayerCharacter::EndAimming);
>              } 
>              //
>              void APlayerCharacter::StartAimming()
>              {
>              	bAimming = true;
>              	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
>              }
>              void APlayerCharacter::EndAimming()
>              {
>              	bAimming = false;
>              	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
>              }
>         </code>
>       </pre>
>
>     - 이후 Aim-Offset을 이용하여 조준하는 동안 카메라 회전에 따라 팔의 위치를 바꾸어주었습니다.
>       <img width="700" alt="image" src="https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/ca53eaa6-a9ea-46d8-9e89-8fb073f9332d">
>
>  - 상호작용
>    - LineTraceSingleByChannel을 사용하였으며, ItemObject에 Tag를 추가하여 TraceCollisionChannel과 해당 Tag를 가진 액터가 충돌하면 인터렉션하게 구현했습니다.
>    - <pre>
>          <code>
>            void APlayerCharacter::Interaction()
>            {
>            	FVector TraceStart{ GetPawnViewLocation() };
>            	FVector TraceEnd{ TraceStart + (GetControlRotation().Vector() * 1500.0f) };
>            	
>            	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f);
>            
>            	FCollisionQueryParams QueryParams;
>            	QueryParams.AddIgnoredActor(this);
>            	FHitResult TraceHit;
>            
>            	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
>            	{
>            		if (AActor *Actor = TraceHit.GetActor())
>            		{
>            			for (FName Tag : Actor->Tags)
>            			{
>            				if (Tag.ToString() == "PickUp")
>            				{
>            					IPickUpInterface *interface = Cast<IPickUpInterface>(Actor);
>            					interface->Interact(this);
>            				}
>            			}
>            		}
>            	}
>            }
>          </code>
>       </pre>


>  ### Weapon
>   - 사격
>     - 무기 클래스를 만들 때 확장성을 고려하여 WeaponBase 클래스를 만들어 무기의 속성들을 정해주었고, 해당 클래스를 상속하여 하위 클래스를 만들었습니다.
>     - LineTraceSingleByChannel을 사용하여 총기 사격을 구현했습니다.
>     - <pre>
>          <code>
>             void AWeapon_Pistol::FireWithLineTrace(TWeakObjectPtr<APlayerCharacter> owner)
>             {
>            	  auto Character = owner.Get();
>            	  if (Character)
>               {
>              	 	AController *ownerController = Character->GetController();
>             		if (ownerController)
>             		{
>             			FVector StartTrace = WeaponMesh->GetSocketLocation("FirePoint");
>             			FVector EndTrace = StartTrace + Character->FollowCamera->GetForwardVector() * TraceDistance;
>             			FCollisionQueryParams CollisionParam;
>             			CollisionParam.AddIgnoredActor(this);
>             			FHitResult HitTrace;
>             
>             			if (GetWorld()->LineTraceSingleByChannel(HitTrace, StartTrace, EndTrace, ECC_Visibility, CollisionParam))
>             			{
>             				FRotator Rotation;
>             				FVector ShotDirection = -Rotation.Vector();
>             				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, HitTrace.Location, ShotDirection.Rotation());
>             				
>             				if (HitTrace.bBlockingHit)
>             				{
>             					if(auto *NPC = Cast<AEnemyCharacter>(HitTrace.GetActor()))
>             					{
>             						UGameplayStatics::ApplyDamage(NPC, 20.0f, NULL, this, UDamageType::StaticClass());
>             
>             						GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("HP : %f"), NPC->GetCurHealth()));
>             					}
>             				}
>             			}
>             			
>             			DecreaseAmmoCount();
>             
>             			if (CurAmmoCount == 0)
>             			{
>             				Character->StartReload();
>             			}
>             		}
>               }
>             }
>          </code>
>       </pre>

> ### EnemyCharacter
>   - AIController
>     - 생성자에서 UAISenseConfig_Sight클래스를 사용하여 해당 컨트롤러를 사용하는 Character가 시야를 가질 수 있도록 탐지 가능 범위, 타겟인식이 해제되는 조건 등을 구현해주었습니다.
>     - <pre>
>         <code>
>             AAI_Controller::AAI_Controller()
>             {
>             	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
>               if (SightConfig)
>               {
>               	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
>               
>               	SightConfig->SightRadius = 500.0f;
>               	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
>               	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
>               	SightConfig->SetMaxAge(5.0f);
>               	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
>               
>               	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
>               	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
>               	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
>               
>               	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
>               	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnTargetDetected);
>               	GetPerceptionComponent()->ConfigureSense(*SightConfig);
>               }
>             }
>         </code>
>       </pre>
>     - 다음으로 OnTargetDetected함수를 사용하여 Character가 타겟을 인식했는지에 대한 여부를 블랙보드의 Bool값으로 받을 수 있도록 구현했습니다.
>     - <pre>
>         <code>
>             void AAI_Controller::OnTargetDetected(AActor *Actor, FAIStimulus const Stimulus)
>             {
>             	if (auto *const ch = Cast<APlayerCharacter>(Actor))
>             	{
>             		GetBlackboardComponent()->SetValueAsBool("IsSearch", Stimulus.WasSuccessfullySensed());
>             	}
>             }
>         </code>
>       </pre>
>   - BTTask_FindRandomLocation
>     - UNavigationSystmeV1클래스의 GetCurrent함수를 사용하여 현재 월드에 배치되어있는 네비매시바운드 볼륨에 대한 정보를 변수에 저장하였고, GetRandomPointInNavigableRadius함수를 사용하여 자기 자신의 위치를 기준으로 특정한 범위를 랜덤하게 탐색하도록 했습니다. 그 다음 랜덤으로 찾은 지역으로의 방향 값을 블랙보드의 Vector타입으로 받을 수 있도록 구현했습니다.
>     - <pre>
>         <code>
>             EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
>             {
>             	if (AAI_Controller *const Controll = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
>             	{
>             		if (auto *const NPC = Controll->GetPawn())
>             		{
>             			FVector const Origin = NPC->GetActorLocation();
>             			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
>             			{
>             				FNavLocation Loc;
>             				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
>             				{
>             					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
>             				}
>             				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
>             				return EBTNodeResult::Succeeded;
>             			}
>             		}
>             	}
>             	return EBTNodeResult::Failed;
>             	
>             }
>         </code>
>       </pre>
>   - BTTask_FindPlayerLocation
>     - bool 타입의SearchRandom이라는 변수를 선언해주었고, 해당 변수가 참일 경우 GetRandomPointInNavigableRadius함수를 사용하여 타겟의 주변 위치를 탐색하도록 그렇지 않다면 타겟의 위치로의 방향을 블랙보드의 Vector 타입으로 얻어올 수 있게 구현했습니다.
>     - <pre>
>         <code>
>             EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
>             {
>             	if (auto *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
>             	{
>             		auto const PlayerLocation = Player->GetActorLocation();
>             		if (SearchRandom)
>             		{
>             			FNavLocation Loc;
>             
>             			if (auto *const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
>             			{
>             				if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc))
>             				{
>             					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
>             					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
>             					return EBTNodeResult::Succeeded;
>             				}
>             			}
>             		}
>             		else
>             		{
>             			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
>             			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
>             			return EBTNodeResult::Succeeded;
>             		}
>             	}
>             	return EBTNodeResult::Failed;
>             }
>         </code>
>       </pre>
>   - BTTask_MeleeAttack
>     - 블랙보드의 bool타입의 변수 값에 의해서 OutOfRange라는 변수의 값이 true가 아닐 경우 공격 애니메이션을 실행하게 구현했습니다.
>     - 공격 실행 몽타주의 경우 UnrealInterface를 이용하였으며, 접두어 Execute_와 접미사 _Implementation 활용하여 IEnemyCombatInterface를 상속받아 EnemyCharacter 클래스에서 재정의한 MeleeAttack 함수를 실행시켰습니다.
>     - <pre>
>         <code>
>             EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
>             {
>                 auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
>                 if (OutOfRange)
>                 {
>                     FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
>                     return EBTNodeResult::Succeeded;
>                 }
>             
>                 auto const *const Controller = OwnerComp.GetAIOwner();
>                 auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());
>             
>                 if (auto *const iCombat = Cast<IEnemyCombatInterface>(NPC))
>                 {
>                     if (MontageHasFinished(NPC))
>                     {
>                         iCombat->Execute_MeleeAttack(NPC);
>                     }
>                 }
>                 
>                 FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
>                 return EBTNodeResult::Succeeded;
>             }
>             
>             bool UBTTask_MeleeAttack::MontageHasFinished(AEnemyCharacter *const NPC)
>             {
>                 return NPC->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(NPC->GetAttackMontage());
>             }
> 
>         </code>
>       </pre>
>   - BTService_ChangeSpeed
>     - OnBecomRelevant라는 함수에 EnemyCharacter클래스에 있는 CharacterMovementComponent를 불러왔고, 블루프린트에서 MaxWalkSpeed를 조절할 수 있도록 구현하였습니다.
>     - <pre>
>         <code>
>             void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
>             {
>             	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
>             
>             	if (auto const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner()))
>             	{
>             		if (auto *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn()))
>             		{
>             			NPC->GetCharacterMovement()->MaxWalkSpeed = Speed;
>             		}
>             	}
>             }
>         </code>
>       </pre>
>   - BTTask_IsPlayerInMeleeRange
>     - GetDistanceTo함수를 사용해서 자기 자신과 타겟의 거리를 구한 후 타겟과의 거리가 공격 거리와 같거나 작으면 블랙보드의 Bool 값을 세팅할 수 있게 구현했습니다.
>     - <pre>
>         <code>
>             void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
>             {
>             	auto const *const Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
>             	auto const *const NPC = Cast<AEnemyCharacter>(Controller->GetPawn());
>             
>             	auto const *const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
>             
>             	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), NPC->GetDistanceTo(Player) <= MeleeRange);
>             }
>         </code>
>       </pre>


> ### Level Object
>   - PickUpItem
>     - 빈 클래스에 언리얼 struct를 선언하고 FTableRow를 상속받아 후에 PickUpItem들의 정보로 이용할 ItemBase를 만들었습니다.
>     - <pre>
>         <code>
>           UENUM()
>           enum class EItemType : uint8
>           {
>     	      Armor UMETA(DisplayName = "Armor"),
>     	      Weapon UMETA(DisplayName = "Weapon"),
>     	      Coin UMETA(DisplayName = "Coin"),
>     	      Consumable UMETA(DisplayName = "Consumable")
>           };
>           USTRUCT()
>           struct FItemTextData
>           {
>     	      GENERATED_USTRUCT_BODY()
>           
>     	      UPROPERTY(EditAnywhere)
>     	      FString Name;
>         
>     	      UPROPERTY(EditAnywhere)
>     	      FString Description;
>           };
>           USTRUCT()
>           struct FItemAssetData
>           {
>     	      GENERATED_USTRUCT_BODY()
>           
>     	      UPROPERTY(EditAnywhere)
>     	      UTexture2D *Icon;
>           
>     	      UPROPERTY(EditAnywhere)
>       	    UStaticMesh *Mesh;
>           };
>           USTRUCT(BlueprintType)
>           struct FItemData : public FTableRowBase
>           {
>     	      GENERATED_USTRUCT_BODY()
>           
>     	      UPROPERTY(EditAnywhere)
>     	      int32 Amount;
>           
>     	      UPROPERTY(EditAnywhere)
>     	      EItemType ItemType;
>       
>     	      UPROPERTY(EditAnywhere)
>     	      FItemTextData TextData;
>           
>     	      UPROPERTY(EditAnywhere)
>     	      FItemAssetData AssetData;
>           };
>         </code>
>       </pre>
>
>      - 위에서 만든 ItemBase를 토대로 데이터테이블 에셋을 만들고, 실제 상호작용할 액터 클래스를 만들어 FObjectFinder를 이용하여 해당 데이터테이블 에셋을 가져왔습니다.
>      - <pre>
>           <code>
>             APickUpItem::APickUpItem()
>             {
>             	PrimaryActorTick.bCanEverTick = true;
>             
>     	        ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
>     	        SetRootComponent(ItemMesh);
>             
>             	// 데이터 테이블 불러오기
>             	ConstructorHelpers::FObjectFinder<UDataTable>DataTable(TEXT("DataTable'/Game/HorrorsGame/Data/ItemDataTable.ItemDataTable'"));
>             	
>     	        if (DataTable.Succeeded())
>     	        {
>     	        	ItemDataTable = DataTable.Object;
>     	        	ItemRowHandle.DataTable = ItemDataTable;
>             	}
>             }
>           </code>
>         </pre>
> 
>      - BeginPlay함수와 OnConstruction함수에서 아래 코드들을 실행시켜 주었습니다.
>      - <pre>
>           <code>
>             void APickUpItem::BeginPlay()
>             {
>             	Super::BeginPlay();
>             	// 데이터 테이블 바인딩
>           	  ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
>             }
>             
>             void APickUpItem::OnConstruction(const FTransform &Transform)
>             {
>             	ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
>             	if (ItemRow)
>     	        {
>     	        	ItemMesh->SetStaticMesh(ItemRow->AssetData.Mesh);
>           	  }
>             }
>           </code>
>         </pre>

> ### UMG
>   - InGameHUD
>     - 화면에 표시해줄 체력바와 총알 개수를 표시해주는 기능을 구현했습니다.
>     - 체력바는 머티리얼을 만들어 아래와 같이 블루프린트를 구현해주었고, 해당 머티리얼의 인스턴스를 UMG 이미지박스에 적용시켜 주었습니다. 그 후, 머티리얼에서 만든 변수 Percent값을 캐릭터의 체력과 연결하여주었습니다.
>     - #### <MT_Circle_ProgressBar>
>     - ![스크린샷 2024-06-05 213648](https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/be2aff82-6940-4982-a449-755fd7e1b340)
>     - #### <BP_InGameUI>
>     - ![스크린샷 2024-06-05 213745](https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/54da01f9-7e79-4f33-aa9a-49024c234338)
>     - 총알 개수는 UTextBlock에 있는 SetText함수를 이용하여 정수를 표시하게끔 해주었으며, 해당 함수를 PlayerCharacter에서 불러와 총알의 값을 세팅해주었습니니다.
>      - <pre>
>           <code>
>             void UInGameHUD::SetAmmoCountText(int remain, int max) const
>             {
>             	FString string = FString::Printf(TEXT(" %d / %d"), remain, max);
>             	AmmoCount->SetText(FText::FromString(string));
>             }
>           </code>
>         </pre>
>      - <pre>
>           <code>
>             << PlayerCharacter.h >>
>             UPROPERTY(EditAnywhere, Category = "Widget")
>             TSubclassOf<UInGameHUD> HUDWidgetClass;
>             UPROPERTY(VisibleAnywhere, Category = "Widget")
>             UInGameHUD *HUDWidget;
> 
>             << PlayerCharacter.cpp >>
>             void APlayerCharacter::CreateHUD()
>             {
>             	if (HUDWidgetClass)
>             	{
>             		HUDWidget = Cast<UInGameHUD>(CreateWidget(GetWorld(), HUDWidgetClass));
>             
>             		if (HUDWidget)
>             		{
>             			HUDWidget->AddToViewport();
>             			HUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
>             
>             			int AmmoRemainCount = EquipWeapon ? EquipWeapon->GetCurAmmo() : 0;
>             			int AmmoMaxCount = EquipWeapon ? EquipWeapon->GetMaxAmmo() : 0;
>             
>             			HUDWidget->Init(AmmoRemainCount, AmmoMaxCount);
>             		}
>             	}
>             }
>           </code>
>         </pre>
>   - Inventory
>     - 플레이어의 인터렉션에 따라 PlaerCharacter의 배열 정보를 Inventory의 배열정보로 옮겨 각 인덱스마다 InventorySlot으로 정보를 표시해주었습니다.
>      - <pre>
>           <code>
>             void UInventory::AddItemToInventory()
>             {
>             	if (Player)
>             	{
>             		InventoryItems = Player->GetInventoryItem();
>             		BindingCoinText();
>             		for (int i = 0; i < InventoryItems.Num(); i++)
>             		{
>             			if (InventoryClass)
>             			{
>             				SlotWidget = Cast<UInventorySlot>(CreateWidget(GetWorld(), InventoryClass));
>             				if (SlotWidget)
>             				{
>             					SlotWidget->SetItemSlot(InventoryItems[i]);
>             					WrapBox->AddChild(SlotWidget);
>             				}
>             			}
>             		}
>             	}
>             }
>           </code>
>         </pre>
>     - 플레이어가 인터렉션한 아이템의 타입이 Coin이라면 InventorySlot을 생성하지 않고 문자열로 개수만을 표시해주도록 구현했습니다.
>      - <pre>
>           <code>
>             void UInventory::BindingCoinText()
>             {
>             	FString CoinString = FString::Printf(TEXT("%d"), Player->GetPlayerCoin());
>             	CoinText->SetText(FText::FromString(CoinString));
>             }
>           </code>
>         </pre>
>   - InventorySlot
>     - PickUpItem에 있는 아이템 정보를 받아와 PickUpItem의 이미지와 텍스트로 표시해주도록 구현했습니다.
>     - Inventory에서 AddChild함수를 통해 생성된 InventorySlot을 클릭하면 해당 아이템의 타입에 따라 아이템을 사용할 수 있습니다.
>      - <pre>
>           <code>
>             void UInventorySlot::SetItemSlot(FItemData *ItemSlot)
>             {
>             	ItemData = ItemSlot;
>             }
>           </code>
>         </pre>
>      - <pre>
>           <code>
>             float UInventorySlot::UseHealthPotion()
>             {
>             	auto Health = MyPlayer->GetCurHealth() + 20.0f;
>             	if (Health > 100.0f)
>             	{
>             		Health = 100.0f;
>             	}
>             	return MyPlayer->SetCurHealth(Health);
>             }
>           </code>
>         </pre>
>   - GameResult
>     - PlayerCharacter의 CurrentHP가 0과 같거나 작아지거나 EnemeyCharacter의 CurrentHP가 0과 같거나 작아지면 각 조건에 따라 다른 텍스트를 바인딩 하도록 구현했습니다.
>     - 해당 UI가 화면에 표시될 때 화면에 마우스를 띄워주고 InputMode를 UI전용으로 바꾸어 주었으며, 게임이 일시정지되도록 구현했습니다.
>      - <pre>
>           <code>
>             void UGameResult::NativeConstruct()
>             {
>             	FString WinString = FString::Printf(TEXT("You Win"));
>             	FString LoseString = FString::Printf(TEXT("You Lose"));
>             
>             	auto *const Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
>             
>             	HUD = Cast<AHorrorsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
>             
>             	if (Player->GetCurHealth() <= 0)
>             	{
>             		ResultText->SetText(FText::FromString(LoseString));
>             	}
>             	else
>             	{
>             		ResultText->SetText(FText::FromString(WinString));
>             	}
>             }
>           </code>
>         </pre>
>      - <pre>
>           <code>
>             void AHorrorsHUD::ShowResult()
>             {
>             	if (GameResultWidget)
>             	{
>             		bIsShowingResult = true;
>             		GameResultWidget->AddToViewport();
>             		GameResultWidget->SetVisibility(ESlateVisibility::Visible);
>             		FInputModeUIOnly UIInputMode;
>             		GetOwningPlayerController()->SetInputMode(UIInputMode);
>             		GetOwningPlayerController()->SetShowMouseCursor(true);
>             		GetOwningPlayerController()->Pause();
>             	}
>             }
>             
>             void AHorrorsHUD::HideResult()
>             {
>             	if (GameResultWidget)
>             	{
>             		bIsShowingResult = false;
>             		GameResultWidget->SetVisibility(ESlateVisibility::Collapsed);
>             		FInputModeGameOnly GameInput;
>             		GetOwningPlayerController()->SetInputMode(GameInput);
>             	}
>             }
>           </code>
>         </pre>


시행 착오
-

> - Player가 원거리 공격을 할 때 Projectile방식이 아니라 LineTrace방식으로 구현해보고자 LineTraceSingleByChannel을 사용하여 사격하는 것 까지는 구현을 하였으나, 바닥을 제외한 다른 Actor들과는 Collision이 발생하지 않아 다른 Actor와 상호작용을 할 수 없었습니다.</br>처음엔 Unreal Document에 FResult에 대한 부분을 살펴보기도 하고 FResult->GetActor() 함수를 응용하여 해결해보려하였으나, 마찬가지로 EnemyCharacter와는 Collision이 발생하지 않았습니다. 결국 구글링을 통해 Collision 세팅에 대해서 알게 되었고, EnemyCharacter에 있는 CapsuleCollision의 Trace를 Block으로 바꾸어 Collision이 발생하지 않았던 문제를 해결했습니다.

> - Inventory를 구현할 때 Player에 있는 Item을 담을 배열의 정보를 InventoryUI에 있는 배열로 복사하고, InventoryUI의 ShowInventory함수가 실행될 때마다 AddChild가 실행되어 획득한 정보를 표시해주는 방식으로 구현했었는데, 이 때, Player의 배열 정보를 매번 받아오게되어 획득한 아이템이 계속 중복되어 표시되는 이슈가 있었습니다.</br> 처음엔 처음 시작부터 너무 잘못 생각했나하는 생각에 처음부터 다시 코딩을 해보려하였으나, 간단하게 해결할 수 있는 문제들은 간단하게 해결하자는 생각이 들어 Unreal Engine TArray의 Remove함수를 이용하여 Player에 있는 배열은 Item정보 획득 -> InventoryUI에 있는 배열로 정보 복사 -> 배열 정보 삭제 순으로 동작하게끔 수정하여 문제를 해결했습니다.
