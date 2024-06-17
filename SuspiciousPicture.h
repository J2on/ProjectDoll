// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDoll.h"
#include "SuspiciousPicture.generated.h"

UCLASS()
class PROJECTDOLL_API ASuspiciousPicture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuspiciousPicture();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuspiciousPicture")
	APlayerDoll* PlayerDoll;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuspiciousPicture")
	USpringArmComponent* DefaultSpringArm;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void RotateEye();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 액자
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuspiciousPicture")
	UStaticMeshComponent* PictureFrameComponent;
	// 왼쪽 눈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuspiciousPicture")
	UStaticMeshComponent* LeftEyeComponent;
	// 오른쪽 눈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuspiciousPicture")
	UStaticMeshComponent* RightEyeComponent;
};
