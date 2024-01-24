// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "KeyActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AKeyActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	AKeyActor();

	UFUNCTION()
	void DestroyKey();
	
	// Door에 해당 Key가 Interact를 시도하고 있는지 알려주는 변수
	bool IsInteract;

private:
	virtual void Interact() override;
	virtual void Tick(float DeltaTime) override;

protected:

};
