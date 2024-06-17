// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenedDoor.h"


AOpenedDoor::AOpenedDoor() : ADoor()
{
	
}


void AOpenedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOpenedDoor::BeginPlay()
{
	
}

void AOpenedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 함수가 실행이 안됨...
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(PlayerDoll)
	{
		IsKeyOverlapped = true;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door in :: Opend Door"));
		}
	}
}

void AOpenedDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if (GEngine) {
    	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door out :: Opend Door"));
    }
}


