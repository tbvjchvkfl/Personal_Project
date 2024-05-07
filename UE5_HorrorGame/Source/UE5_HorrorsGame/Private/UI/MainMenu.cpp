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

    // ������ �巡�� ��� �۾��� ĳ�����ϰ� �÷��̾ ��ȿ���� Ȯ���� �� �÷��̾ �ִ� ������ ����� ȣ���Ѵ�.
}
