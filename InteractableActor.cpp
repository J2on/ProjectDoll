// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"




// SetTextVisibility()
static  constexpr const float VisibleDistance = 500.0f;
// AttachedToPlayerSocket()
static constexpr const float PressTimeFactor = 1.0f;

// Sets default values
AInteractableActor::AInteractableActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	//Initialize
	ItemNum = 0;
	PickUpButtonPressTime = 0.0f;
	InteractButtonPressTime = 0.0f;
	IsPlayerOwned = false;
	IsTextVisible = false;

	// CapsuleComponent 생성 후 Root로 선언 
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(50.0f, 50.0f); // 캡슐 크기 설정 (반지름 50, 높이 100)
	CapsuleComponent->SetCollisionProfileName(TEXT("BlockAll")); // 충돌 설정
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetSimulatePhysics(false);

	
	// MeshComponent 생성
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	
	
	// Viewport 안에 들어왔을때 나타낼 Text -> 추후 이미지로 변경 가능.
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextComponent->SetText(FText::FromString(TEXT("Press X Button")));
	TextComponent->SetTextRenderColor(FColor::Green);
	TextComponent->SetupAttachment(RootComponent);

	//this->SetActorEnableCollision(ECollisionEnabled::PhysicsOnly);
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
	}
	else // 플레이어가 획득한 경우
	{
		if(PlayerDoll->IsInteractionButtonDown)
		{
			// 버튼이 처음 눌렸을때 동작하고 딜레이를 가지도록 && Hidden이 아닐때 => 손에 들고있을때
			if(InteractButtonPressTime == 0.0f && !this->IsHidden())
			{
				Interact();
				InteractButtonPressTime += DeltaTime;
			}
		}
		else
		{
			InteractButtonPressTime = 0.0f;
		}
	}
}

// Interaction 가능 여부를 나타내는 Text의 Visibility를 설정.
void AInteractableActor::SetTextVisibility()
{
	// Viewport 내부에 있고, 일정 거리 이하일때 visible하게
	if(IsInPlayerViewPort() && CalcDistanceToPlayer() < VisibleDistance)
	{
		IsTextVisible = true;
	}
	else
	{
		IsTextVisible = false;	
	}
	TextComponent->SetVisibility(IsTextVisible);
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

// PlayerSocket으로 object를 Player의 손에 이동하게 함. 
void AInteractableActor::AttachedToPlayerSocket(float DeltaTime)
{
	if(this->IsHidden()){ return; } // Item이 hidden인 경우 -> inventory에 있지만 손에 들고있지 않은 경우 
	
	if(PlayerDoll->IsPickUpButtonDown)
	{
		if(!IsPlayerOwned) // 플레이어가 획득하지 않은 경우, 획득하는 기능
		{
			PickUpButtonPressTime += DeltaTime;
			// PressTimeFactor 이상의 시간이 지났고, Text가 보일때(view frustum 안에 있을때) 실행.
			if(PickUpButtonPressTime > PressTimeFactor && IsTextVisible)
			{ 
				// 여기에서 Object의 위치를 플레이어의 소켓으로 이동하는 코드를 작성
				this->AttachToComponent(PlayerDoll->PlayerHandSocket, FAttachmentTransformRules::SnapToTargetIncludingScale);
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("쉬바 문 열린다"));
				}
				this->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
				
				this->TextComponent->SetVisibility(false);
				IsPlayerOwned = true;
				
				// 플레리어와 충돌을 방지하기 위해 콜리전 해제
				this->SetActorEnableCollision(false);
				
				// PlayerController를 가져옴, '0'은 플레이어의 지정 숫자를 이야기 함.
				PlayerDollController = Cast<APlayerDollController>(PlayerController);
				
				// Inventory에 넣는 과정 : 플레이어 컨트롤러의 멤버변수 PlayerInventory에 넣어줌.
				if(PlayerDollController)
				{
					PlayerDollController->PlayerInventory->AddItem(this, PlayerDollController->CurrentInventorySlot);
					
				}
			}
		}
	}
	else
	{
		PickUpButtonPressTime = 0.0f;
	}
}

void AInteractableActor::Interact()
{
	
}

