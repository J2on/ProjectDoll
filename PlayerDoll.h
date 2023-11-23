// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerDoll.generated.h"


// Enum Type으로 플레이어 상태를 표현
enum EPlayerState
{
	STOP,
	WALK,
	RUN,
	BREATH_HOLD
};

UCLASS()
class PROJECTDOLL_API APlayerDoll : public ACharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* DefaultCameraSpringArm;
	UCameraComponent* DefaultCamera;
	
public:
	// Sets default values for this character's properties
	APlayerDoll();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Axis Mapping 처리 함수
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void ChangeCameraPitch(float AxisValue);
	UFUNCTION()
	void ChangeCameraYaw(float AxisValue);
	UFUNCTION()
	void ZoomIn();
	UFUNCTION()
	void ZoomOut();
	
	// Action Mapping 처리 함수
	UFUNCTION()
	void WalkForwardButtonDown();
	UFUNCTION()
	void WalkForwardButtonUp();
	UFUNCTION()
	void WalkRightButtonDown();
	UFUNCTION()
	void WalkRightButtonUp();
	UFUNCTION()
	void RunButtonDown();
	UFUNCTION()
	void RunButtonUp();
	UFUNCTION()
	void BreathHoldButtonUp();
	UFUNCTION()
	void BreathHoldButtonDown();
	UFUNCTION()
	void InteractionButtonDown();
	UFUNCTION()
	void InteractionButtonUp();
	
	// 기타 함수
	UFUNCTION()
	void UpdateBPM();
	UFUNCTION()
	void BodyHeaving();
	UFUNCTION()
	void SetPlayerState();

private:
	bool IsMouseRightButtonClick;
	float ZoomScale;
	EPlayerState PlayerState;

	// Tick함수에서 1초 단위 수행에 사용
	float TimeUnit;

	// Player State 변화에 사용
	int WalkButtonPressCount;
	int RunButtonPressCount;
	bool IsWalk;
	bool IsRun;
	bool IsBreathHold;

	// Body Heaving에 사용하는 s변수
	bool IsBodyHeavingUp;
	FVector BodyHeavingTempLocation;
	
public:
	//Player의 BPM은 적의 공격 판단에 사용됨.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerDoll")
	float PlayerBPM;
	// 타 Object와의 Interaction 여부 판단을 위해 사용됨.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerDoll")
	float IsInteractionButtonDown;
	// 임시 팔로 사용할 Sphere
	UPROPERTY(VisibleAnywhere, Category = "Temp")
	UStaticMeshComponent* PlayerHandSocket;
};
