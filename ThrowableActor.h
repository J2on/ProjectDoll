// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThrowableActor.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AThrowableActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	AThrowableActor();
	
	virtual void Interact() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Projectile movement component for physics
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
};
