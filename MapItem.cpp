// Fill out your copyright notice in the Description page of Project Settings.


#include "MapItem.h"



AMapItem::AMapItem()
{
	ItemNum = 3;

	IsInitialized = false;
	IsMapOnDisplay = false;
}


void AMapItem::Interact()
{
	if(!IsInitialized)
	{
		SetMapWidget();
	}
	SetMapVisibility();
}

void AMapItem::SetMapWidget()
{
	AProjectDollGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AProjectDollGameModeBase>();
	MapWidget = GameMode->MapWidget;
}

void AMapItem::SetMapVisibility()
{
	// Interact 함수를 통해 MapWidget의 시각화 조절
	if(!IsMapOnDisplay)
	{
		MapWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MapWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	IsMapOnDisplay = !IsMapOnDisplay;
}



void AMapItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}