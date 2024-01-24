// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

constexpr int CollisionBoxSizeX = 200;
constexpr int CollisionBoxSizeY = 100;
constexpr int CollisionBoxSizeZ = 100;

constexpr float MaxOpenAxis = 120.0f;

// Sets default values
ADoor::ADoor() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// BoxCollision 생성 및 함수 바인딩
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
	RootComponent = BoxCollisionComponent;
	// Collision box의 크기 조정
	BoxCollisionComponent->SetBoxExtent(FVector(CollisionBoxSizeX, CollisionBoxSizeY, CollisionBoxSizeZ));

	// Door및 Doorframe 생성
	DoorframeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorframe"));
	DoorframeMeshComponent->SetupAttachment(RootComponent);
	// 경첩
	DoorHingeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hinge"));
	DoorHingeComponent->SetupAttachment(DoorframeMeshComponent);
	// 문
	DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMeshComponent->SetupAttachment(DoorHingeComponent);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextComponent->SetText(FText::FromString(TEXT("Press C Button")));
	TextComponent->SetTextRenderColor(FColor::Green);
	TextComponent->SetupAttachment(RootComponent);

	
	// initialize
	IsOpen = false;
	IsKeyOverlapped = false;
	DoorState = CLOSE;
	DoorOpeningFactor = 0.0f;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(DoorState == OPEN){return;}
	else if(DoorState == CLOSE)
	{ // Key가 가까이 있고 문을 열고자하는 경우
	    
		if(IsKeyOverlapped && PlayerDoll->IsInteractionButtonDown)
		{
			APlayerDollController* PlayerDollController = Cast<APlayerDollController>(PlayerDoll->GetController());
			KeyActor = Cast<AKeyActor>(PlayerDollController->PlayerInventory->Inventory[PlayerDollController->CurrentInventorySlot]);
			if(KeyActor) // 들고 있는게 key가 맞다면
			{	
				KeyActor->DestroyKey();
				DoorState = OPENING; // Door Open신호
			}
		}
		else{ return; }
	}
	else // DoorState == OPENING
	{
		DoorOpeningFactor += 1.0f;
		// 문 열기 파트
		DoorHingeComponent->SetRelativeRotation(DoorHingeComponent->GetComponentRotation() - FRotator(0.0f, 1.0f, 0.0f));

		if(DoorOpeningFactor > MaxOpenAxis)
		{
			DoorState = OPEN; // 문 다 열렸다.
		}
	}
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 다른 액터가 문의 영역에 진입했을 때 호출되는 코드
	// 플레이어인지 확인
	if(Cast<APlayerDoll>(OtherActor)){
		PlayerDoll = Cast<APlayerDoll>(OtherActor);
	}
	
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

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    PlayerDoll = nullptr;
	IsKeyOverlapped = false;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Door out"));
	}
}

