// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerDoll.h"
#include "PlayerDollController.h"
#include "InventoryClass.h"
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
	
	// Root가 될 Capsule Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UCapsuleComponent* CapsuleComponent;
	
	// 출력할 TEXT
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	UTextRenderComponent* TextComponent;

	//MeshComponent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	UStaticMeshComponent* MeshComponent;

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

	virtual void Interact();
	
	// Item마다 고유 번호 부여
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	int32 ItemNum;
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	APlayerController* PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	APlayerDollController* PlayerDollController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	APlayerDoll* PlayerDoll;
	
	// X버튼이 얼마나 오래 눌렸는지 기록하는 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	float PickUpButtonPressTime;

	// C버튼 딜레이를 확인
	float InteractButtonPressTime;

	// 플레이어의 view 안에 있는지 확인
	bool IsTextVisible;


};
