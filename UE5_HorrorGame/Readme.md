Horror's Game
-
맵을 이동하며 좀비들을 무찌르는 3인칭 공포게임입니다.

플레이 영상
-
https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/f6b6c91a-f6d2-4659-9956-b415d3347c62

핵심 기능
-
> - 데이터 테이블을 활용한 Item과 Tutorial 기능
> - NPC의 상태별 행동패턴과 보스 NPC의 거리에 따른 공격 패턴
> - HUD를 활용한 전체 UI 관리
> - 액터 컴포넌트와 인터페이스를 활용한 Inventory 기능


기능 구현
-



시행 착오
-

> - Player가 원거리 공격을 할 때 Projectile방식이 아니라 LineTrace방식으로 구현해보고자 LineTraceSingleByChannel을 사용하여 사격하는 것 까지는 구현을 하였으나, 바닥을 제외한 다른 Actor들과는 Collision이 발생하지 않아 다른 Actor와 상호작용을 할 수 없었습니다.</br>처음엔 Unreal Document에 FResult에 대한 부분을 살펴보기도 하고 FResult->GetActor() 함수를 응용하여 해결해보려하였으나, 마찬가지로 EnemyCharacter와는 Collision이 발생하지 않았습니다. 결국 구글링을 통해 Collision 세팅에 대해서 알게 되었고, EnemyCharacter에 있는 CapsuleCollision의 Trace를 Block으로 바꾸어 Collision이 발생하지 않았던 문제를 해결했습니다.

> - Inventory를 구현할 때 Player에 있는 Item을 담을 배열의 정보를 InventoryUI에 있는 배열로 복사하고, InventoryUI의 ShowInventory함수가 실행될 때마다 AddChild가 실행되어 획득한 정보를 표시해주는 방식으로 구현했었는데, 이 때, Player의 배열 정보를 매번 받아오게되어 획득한 아이템이 계속 중복되어 표시되는 이슈가 있었습니다.</br> 처음엔 처음 시작부터 너무 잘못 생각했나하는 생각에 처음부터 다시 코딩을 해보려하였으나, 간단하게 해결할 수 있는 문제들은 간단하게 해결하자는 생각이 들어 Unreal Engine TArray의 Remove함수를 이용하여 Player에 있는 배열은 Item정보 획득 -> InventoryUI에 있는 배열로 정보 복사 -> 배열 정보 삭제 순으로 동작하게끔 수정하여 문제를 해결했습니다.
