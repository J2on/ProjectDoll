// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InteractableActor.h"
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
	
	// Inventory 구현	
	TArray<int> Inventory;
	// 지금 들고있는 item의 index
	int CurrentInventoryIndex;
};
