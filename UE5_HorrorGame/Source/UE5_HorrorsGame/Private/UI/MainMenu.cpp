// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Character/Player/PlayerCharacter.h"

void UMainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // 아이템 드래그 드롭 작업을 캐스팅하고 플레이어가 유효한지 확인한 후 플레이어에 있는 아이템 드롭을 호출한다.
}
