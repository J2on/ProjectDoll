// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "ProjectDollGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MapItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AMapItem : public AInteractableActor
{
	GENERATED_BODY()

public:
	AMapItem();

	bool IsInitialized;
	bool IsMapOnDisplay;

	
protected:
	virtual void Interact() override;
	virtual void Tick(float DeltaTime) override;
	void SetMapWidget();
	void SetMapVisibility();
	UUserWidget* MapWidget;
};
