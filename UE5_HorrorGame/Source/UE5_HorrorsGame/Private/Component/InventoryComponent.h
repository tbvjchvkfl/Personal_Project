// Fill out your copyright notice in the Description page of Project Settings.

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
	// =                  Variable / Property					 =
	// ===========================================================
	
	// 델리게이트 인벤토리 내용 업데이트용
	FOnInventoryUpdate OnInventoryUpdated;



	// ===========================================================
	// =					  Functionary	   				     = 
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
	// =                  Variable / Property					 =
	// ===========================================================

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 CoinInventory;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> ItemInventory;

	AHorrorsHUD *UIComp;

	// ===========================================================
	// =					  Functionary	   				     = 
	// ===========================================================
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


};
