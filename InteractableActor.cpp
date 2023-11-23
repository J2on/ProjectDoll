// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"


// SetTextVisibility()
static  constexpr const float VisibleDistance = 500.0f;
// AttachedToPlayerSocket()
static constexpr const float PressTimeFactor = 2.0f;

// Sets default values
AInteractableActor::AInteractableActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	//Initialize
	InteractionButtonPressTime = 0.0f;
	IsPlayerOwned = false;

	// Viewport 안에 들어왔을때 나타낼 Text -> 추후 이미지로 변경 가능.
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextComponent->SetText(FText::FromString(TEXT("Press X Button")));
	TextComponent->SetTextRenderColor(FColor::Green);

	this->SetActorEnableCollision(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Viewport의 크기와 ScreenSpace 좌표 계산을 위한 PlayerController 소환
	PlayerController = GetWorld()->GetFirstPlayerController();

	// 플레이어 폰을 가져옴
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerDoll = Cast<APlayerDoll>(PlayerPawn);
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 플레이어가 획득하지 않았을때만
	if(!IsPlayerOwned)
	{
		SetTextVisibility();
		AttachedToPlayerSocket(DeltaTime);


	// TEXT가 플레이어를 향하도록
		
		// 플레리어의 위치 - Actor의 위치는 Actor에서 플레이어를 향하는 벡터가 될테니까.
		ToPlayer = PlayerDoll->GetActorLocation() - this->GetActorLocation();
		// ToPlayer vector는 z축 위치가 상관없다.
		ToPlayer.Z = 0.0f;
		this->SetActorRotation(ToPlayer.Rotation());
	}
}

// Interaction 가능 여부를 나타내는 Text의 Visibility를 설정.
void AInteractableActor::SetTextVisibility()
{
	// Viewport 내부에 있고, 일정 거리 이하일때 visible하게
	bool IsVisible;
	if(IsInPlayerViewPort() && CalcDistanceToPlayer() < VisibleDistance)
	{
		IsVisible = true;
	}
	else
	{
		IsVisible = false;	
	}
	TextComponent->SetVisibility(IsVisible);
}

// Player가 Viewport 안에 있는지 확인하는 함수
bool AInteractableActor::IsInPlayerViewPort()
{
	if(!PlayerController)
	{
		return false;
	}
	// 이 Actor의 World Space 좌표
	FVector WorldSpaceLocation = GetActorLocation();
	// 이 Actor의 Screen Space 좌표
	FVector2D ScreenSpaceLocation;
	FIntVector2 ViewportSize;
	// WorldSpace->ScreenSpace 좌표 / viewport size 구하기
	PlayerController->ProjectWorldLocationToScreen(WorldSpaceLocation, ScreenSpaceLocation);
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
	// 이 Screen Space 좌표가 [ 0 < X좌표 < 뷰포트 X축 크기, 0 < Y좌표 < 뷰포트 Y축 크기 ] 여기에 속할때
	if(ScreenSpaceLocation.X >= 0 && ScreenSpaceLocation.X <= ViewportSize.X
		&& ScreenSpaceLocation.Y >= 0 && ScreenSpaceLocation.Y <= ViewportSize.Y)
	{
		return true;
	}
	return false;	
}

// 이 Object와 Player간의 거리를 계산
float AInteractableActor::CalcDistanceToPlayer()
{
	// Location 좌표 가져옴
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector ObjectLocation = this->GetActorLocation();
	// 거리 계산 후 바로 return
	return FVector::Distance(PlayerLocation, ObjectLocation);
}

// Interaction을 통해 PlayerSocket으로 object를 Player의 손에 이동하게 함. 
void AInteractableActor::AttachedToPlayerSocket(float DeltaTime)
{
	if(PlayerDoll->IsInteractionButtonDown)
	{
	 	InteractionButtonPressTime += DeltaTime;
		// PressTimeFactor 이상의 시간이 지났을때 Interaction을 실행.
		if(InteractionButtonPressTime > PressTimeFactor)
		{
			// 여기에서 Object의 위치를 플레이어의 소켓으로 이동하는 코드를 작성
			this->AttachToComponent(PlayerDoll->PlayerHandSocket, FAttachmentTransformRules::SnapToTargetIncludingScale);
			// 문구는 보이지 않게 변경
			this->TextComponent->SetVisibility(false);
			// 플레이어가 획득 했음을 확인
			IsPlayerOwned = true;

			// PlayerController를 가져옴, '0'은 플레이어의 지정 숫자를 이야기 함.
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			APlayerDollController* PlayerDollController = Cast<APlayerDollController>(PlayerController);


			// 일단 Key Number 1로 지정
			PlayerDollController->Inventory.Add(1);
		}
	}
	else
	{
		InteractionButtonPressTime = 0.0f;
	}
}


