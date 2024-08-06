Horror's Game
-
맵을 이동하며 좀비들을 무찌르는 3인칭 슈팅게임입니다.

플레이 영상
-
https://github.com/user-attachments/assets/d6d4c018-d635-46a2-9d91-9d937efa383a

핵심 기능
-
> - 데이터 테이블을 활용한 Item과 Tutorial 기능
> - NPC의 상태별 행동패턴과 보스 NPC의 거리에 따른 공격 패턴
> - HUD를 활용한 전체 UI 관리
> - 액터 컴포넌트와 인터페이스를 활용한 Inventory 기능


기능 구현
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
    <td><img src = "https://github.com/user-attachments/assets/8b5355f4-b95a-45a2-a6ee-24bdd15bc133" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/6dd322c9-5d44-4b05-8ec6-423c6972ab4c" width = "200" heigh = "150"</td>
  </tr>
   <tr>
    <th>재장전</th>
    <th>인벤토리와 상호작용</th>
    <th>NPC 상태별 패턴</th>
    <th>NPC 거리별 패턴</th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/7c31e4ec-1c07-4263-8699-792856c3c2da" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/087e7fa1-5028-4b81-96e8-8ad277d1deda" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/0903da17-99f3-4dcf-98b3-124d17400f14" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/ff23c1b4-712b-4bc5-a306-0fe5048c75f4" width = "200" heigh = "150"</td>
  </tr>
   <tr>
    <th>히트 리액션과 원형 체력바</th>
    <th>튜토리얼 트리거</th>
    <th>결과 화면 UI</th>
    <th></th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/77a1bc56-7394-4e58-8aff-3bd5024b9f86" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/5bd25b9d-eaa7-4ca2-8069-b9b835d8254e" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/8fc87a91-791b-4eee-822a-55862598daf0" width = "200" heigh = "150"</td>
    <td></td>
  </tr>
   <tr>
    <th>레벨 오브젝트 <문></th>
    <th>레벨 오브젝트 <도깨비 불></th>
    <th>포스트 프로세스 볼륨 <안개></th>
    <th></th>
  </tr>
  <tr>
    <td><img src = "https://github.com/user-attachments/assets/d0081894-e4ff-48ff-9d3f-840382566ba4" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/416a295c-0af3-45ed-b5b6-a3de1f01ad27" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/8757b28e-6196-41e0-99ee-64858a570d3a" width = "200" heigh = "150"</td>
    <td></td>
  </tr>
</table>

시행 착오
-

> - Player가 원거리 공격을 할 때 Projectile방식이 아니라 LineTrace방식으로 구현해보고자 LineTraceSingleByChannel을 사용하여 사격하는 것 까지는 구현을 하였으나, 바닥을 제외한 다른 Actor들과는 Collision이 발생하지 않아 다른 Actor와 상호작용을 할 수 없었습니다.</br>처음엔 Unreal Document에 FResult에 대한 부분을 살펴보기도 하고 FResult->GetActor() 함수를 응용하여 해결해보려하였으나 마찬가지로 EnemyCharacter와는 Collision이 발생하지 않았습니다. 결국 구글링을 통해 Collision 세팅에 대해서 알게 되었고, EnemyCharacter에 있는 CapsuleCollision의 Trace를 Block으로 바꾸어 Collision이 발생하지 않았던 문제를 해결했습니다.

> - Inventory를 구현할 때 Player에 있는 Item을 담을 배열의 정보를 InventoryUI에 있는 배열로 복사하고, InventoryUI의 ShowInventory함수가 실행될 때마다 AddChild가 실행되어 획득한 정보를 표시해주는 방식으로 구현했었는데, 이 때, Player의 배열 정보를 매번 받아오게되어 획득한 아이템이 계속 중복되어 표시되는 이슈가 있었습니다.</br> 문제를 수정하는 과정에서 Plyayer에 있는 배열 정보가 Inventory로 복사 되었다면 Player에 있는 배열은 empty상태로 바꾸어 주는 방식으로 해당 문제를 해결하긴 하였으나 코드가 난잡해지고 스스로 보기에도 맘에 들지 않아 다른 사람들의 코드를 참고하였고, 델리게이트를 사용한 방식을 알게되어 아이템을 획득하였다면 Inventory의 배열에 자동으로 해당 아이템의 정보가 추가될 수 있도록 수정하였습니다.

> - Boss NPC와의 전투를 구현할 때, SetTimer함수에 람다를 이용해서 Boss NPC의 원거리 공격에 쿨타임 기능을 만들었었는데 Boss가 죽고 레벨에서 Destroy된 후 SetTimer에 사용한 Lambda에서 계속해서 크래쉬가 발생하는 이슈가 있었습니다. 처음엔 Lambda를 잘못 사용했나 하는 생각에 SetTimer함수의 로직과 Lambda를 살펴보았으나 Lambda에는 잘못된 부분이 없다고 생각하여 문제를 수정하지 못하고 있었습니다. 이 후, 계속해서 디버깅을 하던 중 Boss가 죽으면 Character는 사라지지만 레벨에 Boss의 Controller가 사라지지 않고 계속해서 남아있었다는 사실을 알게되었습니다. 확인해보니 실제로 Boss가 죽은 후에 Controller에 있던 TargetDeteced함수는 여전히 동작하고 있었고, 때문에 Controller클래스에 있던 일부 함수들이 Boss가 죽은 후 Controller에 있던 Boss의 일부 포인터가 nullptr이 되면서 발생한 이슈라는 것을 알 수 있었습니다. 이 후, Boss가 죽으면 BossController의 Unpossess함수를 함께 호출해주어 해당 문제를 해결했습니다.
