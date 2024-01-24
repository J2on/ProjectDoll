// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryClass.h"

UInventoryClass::UInventoryClass()
{
	MaxInventorySize = 5;
	Inventory.Init(nullptr, MaxInventorySize);
}

// Item을 Inventory에 넣음
bool UInventoryClass::AddItem(AActor* Item, int32 CurrentInventorySlot)
{
	// 배열을 돌며 빈공간을 찾음
	for (int32 i=0; i <MaxInventorySize; i++)
	{
		// 빈공간이 있는 경우 아이템을 넣고 true를 리턴
		if (!Inventory[i])
		{
			Inventory[i] = Item;
			// 현재 선택된 Inventory Slot이 아니라면 게임에서 숨기기 
			if(i != CurrentInventorySlot)
			{
				Item->SetActorHiddenInGame(true);	
			}
			return true;
		}
	}
	// 빈공간이 없는 경우 false;
	return false;
}

bool UInventoryClass::RemoveItem(AActor* Item)
{
	// 배열을 돌며 item을 찾음
	for(int32 i = 0; i < MaxInventorySize; i++)
	{
		// inventory에 Item이 있는 경우 nullptr로 대체 후 true 리턴
		if(Inventory[i] == Item)
		{
			Inventory[i] = nullptr;
			return true;
		}
	}
	// 아이템이 inventory에 없으므로 false 리턴
	return false; 
}





