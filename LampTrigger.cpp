// Fill out your copyright notice in the Description page of Project Settings.


#include "LampTrigger.h"

// Sets default values
ALampTrigger::ALampTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Init
	IsLightTurnOn = false;

	// BoxCollision 생성 및 함수 바인딩
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALampTrigger::OnOverlapBegin);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ALampTrigger::OnOverlapEnd);

	// Lamp Mesh
	LampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lamp"));
	LampMeshComponent->SetupAttachment(RootComponent);
	
	// Lamp Light
	LampLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LampLight"));
	LampLightComponent->SetupAttachment(LampMeshComponent);
	LampLightComponent->SetVisibility(IsLightTurnOn);
	
	
}
// Overlap시 Light on
void ALampTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsLightTurnOn = !IsLightTurnOn;
	LampLightComponent->SetVisibility(IsLightTurnOn);
	
}
// Light Off
void ALampTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsLightTurnOn = !IsLightTurnOn;
	LampLightComponent->SetVisibility(IsLightTurnOn);
}

// Called when the game starts or when spawned
void ALampTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}



