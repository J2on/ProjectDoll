// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDollController.h"

APlayerDollController::APlayerDollController()
{
	// PlayerController에서 Inventory를 객체로 가지게 함.
	PlayerInventory = CreateDefaultSubobject<UInventoryClass>(TEXT("PlayerInventory"));
	// 지금 들고있는 Item의 slot
	CurrentInventorySlot = 0;
}

void APlayerDollController::SetupInputComponent()	
{
	Super::SetupInputComponent();

	// 1번 슬롯 선택: 키 입력 이벤트를 1 키에 연결
	InputComponent->BindAction("Inventory1", IE_Pressed, this, &APlayerDollController::SelectInventorySlot1);
	// 2번 슬롯 선택: 키 입력 이벤트를 2 키에 연결
	InputComponent->BindAction("Inventory2", IE_Pressed, this, &APlayerDollController::SelectInventorySlot2);
	// 3번 슬롯 선택: 키 입력 이벤트를 3 키에 연결
	InputComponent->BindAction("Inventory3", IE_Pressed, this, &APlayerDollController::SelectInventorySlot3);
	// 4번 슬롯 선택: 키 입력 이벤트를 4 키에 연결
	InputComponent->BindAction("Inventory4", IE_Pressed, this, &APlayerDollController::SelectInventorySlot4);
	// 5번 슬롯 선택: 키 입력 이벤트를 5 키에 연결
	InputComponent->BindAction("Inventory5", IE_Pressed, this, &APlayerDollController::SelectInventorySlot5);
}

void APlayerDollController::SelectInventorySlot1()
{
	ChangeHandItem(0);
}

void APlayerDollController::SelectInventorySlot2()
{
	ChangeHandItem(1);
}

void APlayerDollController::SelectInventorySlot3()
{
	ChangeHandItem(2);
}

void APlayerDollController::SelectInventorySlot4()
{
	ChangeHandItem(3);
}

void APlayerDollController::SelectInventorySlot5()
{
	ChangeHandItem(4);
}


// 손에 들고있는 물체를 변경하는 함수 : Object Pooling에 따라 물체는 모두 손에 잡고 있으며 선택 되었는지에 따라 보이게/안보이게 설정함.
void APlayerDollController::ChangeHandItem(int32 SlotNumber)
{
	// PlayerInventory의 Inventory array에 해당 index가 존재하는지 확인
	if (PlayerInventory->Inventory.IsValidIndex(CurrentInventorySlot))
	{

		// 지금 들고있는 물체 보이지 않게
		if (AActor* CurrentItem = PlayerInventory->Inventory[CurrentInventorySlot])
		{
			CurrentItem->SetActorHiddenInGame(true);
		}
	}
	
	CurrentInventorySlot = SlotNumber;
	
	if (PlayerInventory->Inventory.IsValidIndex(CurrentInventorySlot))
	{
		// 새로운 물체 보이게
		if (AActor* NextItem = PlayerInventory->Inventory[CurrentInventorySlot])
		{
			NextItem->SetActorHiddenInGame(false);
		}
	}
}


