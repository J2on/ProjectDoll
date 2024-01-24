// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "LampTrigger.generated.h"

UCLASS()
class PROJECTDOLL_API ALampTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ALampTrigger();

protected:
	virtual void BeginPlay() override;

	// Collision 박스 안에 들어온 경우
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Key가 박스에서 나가는 경우 
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsLightTurnOn;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LampTrigger")
	UStaticMeshComponent* LampMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LampTrigger")
	UBoxComponent* BoxCollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LampTrigger")
	UPointLightComponent* LampLightComponent;
};
