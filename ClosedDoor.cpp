// Fill out your copyright notice in the Description page of Project Settings.


#include "ClosedDoor.h"

AClosedDoor::AClosedDoor()
{

}

void AClosedDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AClosedDoor::BeginPlay()
{
	
}

void AClosedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 함수가 실행이 안됨...
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    if (PlayerDoll)
    {
        if(PlayerDoll->HasKey)
        {
            // Key가 문에 가까이 왔을 때, IsKeyOverlapped를 true
            IsKeyOverlapped = true;
            
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door in"));
            }
        }
    }
}

void AClosedDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}