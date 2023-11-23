// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerDoll.h"
#include "PlayerDollController.h"
#include "Components/TextRenderComponent.h"
#include "InteractableActor.generated.h"

UCLASS()
class PROJECTDOLL_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	// Object의 이름을 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	FText ObjectName;
	// Interaction 시에 나타날 수 있는 메시지,
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	FText InteractionMessage;

	// 출력할 TEXT
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	UTextRenderComponent* TextComponent;

	// 이 Actor가 Player의 소유에 있는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	bool IsPlayerOwned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// checking this object is in player's viewport
	UFUNCTION()
	bool IsInPlayerViewPort();
	UFUNCTION()
	float CalcDistanceToPlayer();
	UFUNCTION()
	void SetTextVisibility();
	UFUNCTION()
	void AttachedToPlayerSocket(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	APlayerController* PlayerController;
	APawn* PlayerPawn;
	APlayerDoll* PlayerDoll;
	// X버튼이 얼마나 오래 눌렸는지 기록하는 변수
	float InteractionButtonPressTime;
	// Text가 항상 플레이어를 바라보도록 플레이어를 향하는 Vector
	FVector ToPlayer;
};
