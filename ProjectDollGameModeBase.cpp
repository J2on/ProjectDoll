// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectDollGameModeBase.h"



void AProjectDollGameModeBase::StartPlay() {
	Super::StartPlay();

	//if (GEngine) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world, this is GameMode"));
	//}

	PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	PlayerWidget->AddToViewport();

	MapWidget = CreateWidget<UUserWidget>(GetWorld(), HUDMapWidget);
	MapWidget->AddToViewport();
	MapWidget->SetVisibility(ESlateVisibility::Collapsed);
}
