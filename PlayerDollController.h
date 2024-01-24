// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryClass.h"
#include "PlayerDollController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API APlayerDollController : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerDollController();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
    int32 CurrentInventorySlot;

	// Action Mapping을 Binding
	virtual void SetupInputComponent() override;
	
	// 1번 슬롯 선택 함수
	void SelectInventorySlot1();
	// 2번 슬롯 선택 함수
	void SelectInventorySlot2();
	// 3번 슬롯 선택 함수
	void SelectInventorySlot3();
	// 4번 슬롯 선택 함수
	void SelectInventorySlot4();
	// 5번 슬롯 선택 함수
	void SelectInventorySlot5();

	void ChangeHandItem(int32 SlotNumber);
	
	// 플레이어의 인벤토리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryClass* PlayerInventory;
	
};
