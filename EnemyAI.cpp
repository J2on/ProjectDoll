// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"


AEnemyAI::AEnemyAI()
{

}
void AEnemyAI::OnPossess(APawn* InPawn)
{

}

void AEnemyAI::BeginPlay()
{
	
	Super::BeginPlay();;
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if(PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Pawn is not found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerPawn->GetName());
	}
	ChasePlayer();
}

void AEnemyAI::ChasePlayer()
{
	
	//UE_LOG(LogTemp, Log, );
	
}

void AEnemyAI::Tick(float DeltaTime)
{
	
	if (PlayerPawn) // 플레이어가 보이는 범위 내에 있는지 확인합니다.
	{
		MoveToActor(PlayerPawn); // 플레이어 폰을 향해 이동합니다.
	}
	
}
