// Fill out your copyright notice in the Description page of Project Settings.


#include "SuspiciousPicture.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASuspiciousPicture::ASuspiciousPicture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


		
	// Mesh 생성
	PictureFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PictureFrame"));
	LeftEyeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftEye"));
	RightEyeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightEye"));
	// Root Component에 부착
	PictureFrameComponent->SetupAttachment(RootComponent);
	LeftEyeComponent->SetupAttachment(PictureFrameComponent);
	RightEyeComponent->SetupAttachment(PictureFrameComponent);
	
}

// Called when the game starts or when spawned
void ASuspiciousPicture::BeginPlay()
{
	Super::BeginPlay();
	
	// 플레이어
	PlayerDoll = Cast<APlayerDoll>(UGameplayStatics::GetPlayerPawn(this, 0));
	DefaultSpringArm = PlayerDoll->DefaultCameraSpringArm;
}

// Called every frame
void ASuspiciousPicture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RotateEye();
}

// 플레이어만 바라보는 눈알 만들기
void ASuspiciousPicture::RotateEye()
{
	//플레이어 위치를 받아오기
	FVector PlayerLocation = PlayerDoll->GetActorLocation();
	// 왼쪽 눈알
	FVector LeftEyeVec = PlayerLocation - LeftEyeComponent->GetComponentLocation();
	FRotator LeftEyeRotator = FRotator(0.f, LeftEyeVec.Rotation().Yaw -90.f, -LeftEyeVec.Rotation().Pitch +90.f);
	LeftEyeComponent->SetWorldRotation(LeftEyeRotator);
	// 오른쪽 눈알
	FVector RightEyeVec = PlayerLocation - RightEyeComponent->GetComponentLocation();
	FRotator RightEyeRotator = FRotator(0.f, RightEyeVec.Rotation().Yaw - 90.f, -RightEyeVec.Rotation().Pitch + 90.f);
	RightEyeComponent->SetWorldRotation(RightEyeRotator);
	
}


