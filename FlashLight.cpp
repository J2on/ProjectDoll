// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLight.h"




AFlashLight::AFlashLight()
{
	ItemNum = 2;
	
	// 손전등의 불빛
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComponent->SetupAttachment(RootComponent);

	// 
	IsLightTurnOn = false;
	SpotLightComponent->SetVisibility(IsLightTurnOn);
}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AFlashLight::Interact()
{
	// 손전등 켜기, 끄기;
	IsLightTurnOn = !IsLightTurnOn;
	SpotLightComponent->SetVisibility(IsLightTurnOn);
}



