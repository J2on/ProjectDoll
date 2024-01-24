// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "PlayerDoll.generated.h"


// Enum Type으로 플레이어 상태를 표현
enum EPlayerState
{
	STOP,
	WALK,
	RUN,
	BREATH_HOLD,
	DEATH
};

UCLASS()
class PROJECTDOLL_API APlayerDoll : public ACharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	//UPROPERTY(EditAnywhere)
	//UCapsuleComponent* DefaultCapsuleComponent;
	
public:
	// Sets default values for this character's properties
	APlayerDoll();

	// Player State
	EPlayerState PlayerState;
	EPlayerState PrePlayerState;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Walk Sound Audio Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* WalkSoundComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* RunSoundComponent;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    UCameraComponent* DefaultCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    USpringArmComponent* DefaultCameraSpringArm;
	
	
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
	void LieDownButtonDown();
	UFUNCTION()
	void LieDownButtonUp();
	UFUNCTION()
	void RunButtonDown();
	UFUNCTION()
	void RunButtonUp();
	UFUNCTION()
	void BreathHoldButtonDown();
	UFUNCTION()
	void BreathHoldButtonUp();
	UFUNCTION()
	void InteractionButtonDown();
	UFUNCTION()
	void InteractionButtonUp();
	UFUNCTION()
	void PickUpButtonDown();
	UFUNCTION()
	void PickUpButtonUp();
	
	// 기타 함수
	UFUNCTION()
	void UpdateBPM();
	UFUNCTION()
	void BodyHeaving();
	UFUNCTION()
	void SetPlayerState();
	UFUNCTION()
	void PlayWalkSound();

private:
	bool IsMouseRightButtonClick;
	float ZoomScale;
	

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
	// Item Pick Up 버튼 클릭 여부를 판단하기 위해 사용됨.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerDoll")
	float IsPickUpButtonDown;
	// 임시 팔로 사용할 Sphere
	UPROPERTY(VisibleAnywhere, Category = "Temp")
	UStaticMeshComponent* PlayerHandSocket;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerDoll")
	bool IsDead;

	bool HasKey;

	// 타 클래스에서 카메라가 바라보는 방향을 얻기 위해
	UFUNCTION()
	FVector GetCameraForwardVector();
};
