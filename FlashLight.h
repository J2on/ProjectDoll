// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Components/SpotLightComponent.h"
#include "FlashLight.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AFlashLight : public AInteractableActor
{
	GENERATED_BODY()


public:
	AFlashLight();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlashLight")
	USpotLightComponent* SpotLightComponent;
	
protected:
	virtual void Interact() override;
	virtual void Tick(float DeltaTime) override;
private:
	bool IsLightTurnOn;


};
