// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenedDoor.h"


AOpenedDoor::AOpenedDoor()
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
	if(Cast<APlayerDoll>(OtherActor)){
		PlayerDoll = Cast<APlayerDoll>(OtherActor);
	}

	if(PlayerDoll)
	{
		IsKeyOverlapped = true;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door in"));
		}
	}
}

void AOpenedDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerDoll = nullptr;
	IsKeyOverlapped = false;
	if (GEngine) {
    	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door out"));
    }
}


