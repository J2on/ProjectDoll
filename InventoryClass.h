// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "InventoryClass.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API UInventoryClass : public UObject
{
	GENERATED_BODY()

public:
	UInventoryClass();

	// 인벤토리 크기
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 MaxInventorySize;

	// 인벤토리 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<AActor*> Inventory;

	// 아이템을 인벤토리에 추가
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(AActor* Item, int32 CurrentInventorySlot);

	// 아이템을 인벤토리에서 제거
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(AActor* Item);

	// 아이템 사용
	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void UseItem(AActor* Item);
};
