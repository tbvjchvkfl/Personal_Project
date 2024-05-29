Horror's Game
-
바이오 하자드4의 모작으로 텍스트 UI의 지시에 따라 게임을 진행하며 좀비들과 전투하고 아이템을 획득하는 게임입니다.

플레이 영상
-

제작 기간 & 사용 기술
-
> #### 제작 기간
>   - 30일 소요 (개인)

> #### 사용 기술
>   - Unreal C++ & Blueprint

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
>   - 인벤토리
>     - 아이템 획득 시 아이템 항목 생성
>     - 아이템 항목 클릭 시 아이템 사용

>   - 체력바
>     - 원형 체력바 (머티리얼 & 블루프린트로 제작)
>   - Aim UI
