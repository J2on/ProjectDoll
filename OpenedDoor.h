// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "OpenedDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDOLL_API AOpenedDoor : public ADoor
{
	GENERATED_BODY()
public:
	AOpenedDoor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;


	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
