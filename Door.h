// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "KeyActor.h"	
#include "Door.generated.h"


enum EDoorState
{
	OPEN,
	OPENING,
	CLOSE
};

UCLASS()
class PROJECTDOLL_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool IsOpen;

	// 문틀
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DoorframeMeshComponent;
	// 경첩
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DoorHingeComponent;
	// 문
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DoorMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	UTextRenderComponent* TextComponent;
	
	EDoorState DoorState; 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Key가 박스 안에 들어온 경우
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Key가 박스에서 나가는 경우 
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	// Key가 Overlap 되었는지 파악하기 위한 Box
	UBoxComponent* BoxCollisionComponent;
	
	// Key가 Box Collision 내부로 진입했는지 확인하는 Bool형 변수
	bool IsKeyOverlapped;
	
	AKeyActor* KeyActor;

	APlayerDoll* PlayerDoll;

	float DoorOpeningFactor;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
