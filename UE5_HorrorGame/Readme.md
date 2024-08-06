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
    <td><img src = "https://github.com/user-attachments/assets/91103ddd-e20c-4e3c-9ce7-7319a0aff2a1" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/4ce3b003-bc7c-4c06-9191-eb704d837e2d" width = "200" heigh = "150"></td>
    <td><img src = "https://github.com/user-attachments/assets/4784e008-c1af-4b22-b247-5a2bfbb7f190" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/5a6e2e3d-d7d8-4e3a-84d0-26b2e2c88ff8" width = "200" heigh = "150"</td>
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
    <td><img src = "https://github.com/user-attachments/assets/b0c0e1b6-f141-4bb7-8377-4547c254d54d" width = "200" heigh = "150"</td>
    <td><img src = "https://github.com/user-attachments/assets/971a2f92-b9dd-4d46-bf81-2f0f503cefc7" width = "200" heigh = "150"</td>
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

> - Player가 원거리 공격을 할 때 Projectile방식이 아니라 LineTrace방식으로 구현해보고자 LineTraceSingleByChannel을 사용하여 사격하는 것 까지는 구현을 하였으나, 바닥을 제외한 다른 Actor들과는 Collision이 발생하지 않아 다른 Actor와 상호작용을 할 수 없었습니다.</br>처음엔 Unreal Document에 FResult에 대한 부분을 살펴보기도 하고 FResult->GetActor() 함수를 응용하여 해결해보려하였으나, 마찬가지로 EnemyCharacter와는 Collision이 발생하지 않았습니다. 결국 구글링을 통해 Collision 세팅에 대해서 알게 되었고, EnemyCharacter에 있는 CapsuleCollision의 Trace를 Block으로 바꾸어 Collision이 발생하지 않았던 문제를 해결했습니다.

> - Inventory를 구현할 때 Player에 있는 Item을 담을 배열의 정보를 InventoryUI에 있는 배열로 복사하고, InventoryUI의 ShowInventory함수가 실행될 때마다 AddChild가 실행되어 획득한 정보를 표시해주는 방식으로 구현했었는데, 이 때, Player의 배열 정보를 매번 받아오게되어 획득한 아이템이 계속 중복되어 표시되는 이슈가 있었습니다.</br> 처음엔 처음 시작부터 너무 잘못 생각했나하는 생각에 처음부터 다시 코딩을 해보려하였으나, 간단하게 해결할 수 있는 문제들은 간단하게 해결하자는 생각이 들어 Unreal Engine TArray의 Remove함수를 이용하여 Player에 있는 배열은 Item정보 획득 -> InventoryUI에 있는 배열로 정보 복사 -> 배열 정보 삭제 순으로 동작하게끔 수정하여 문제를 해결했습니다.
