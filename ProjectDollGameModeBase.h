// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ProjectDollGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AProjectDollGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public :
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ProjectDoll")
	UUserWidget* CurrentWidget;
	
	//TSubclassOf<Type> <- Type을 제한하는 구문
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ProjectDoll")
	TSubclassOf<UUserWidget> HUDWidget;
};
