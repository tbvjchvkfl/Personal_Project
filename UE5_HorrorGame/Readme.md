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

> ### Playable Character
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
>     - 이미지 예시(블루프린트)

>  ### Weapon
>   - 사격
>     - <pre>
>          <code>
>            a
>            a
>            a
>          </code>
>       </pre>

> ### Zombie_AI
>   - 시야각
>   - 근접 공격
>   - 추격(이동)
>   - AI_FoundLocationSystem

> ### Level Object
>   - Collision Object

> ### UMG
>   - 인벤토리
>     - 아이템 획득 시 아이템 항목 생성
>     - 아이템 항목 클릭 시 아이템 사용

>   - 체력바
>     - 원형 체력바 (머티리얼 & 블루프린트로 제작)
>   - Aim UI
