// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDoll.h"

// tick() 
static constexpr const float ZoomFactor = 0.3f;
static constexpr const float UpdateTime = 1.5f;

// Move
static constexpr const float WalkSpeed = 5.0f;
static constexpr const float RunSpeed = 10.0f;

//CameraMoveFactor PitchFactor YawFactor
static constexpr const float CameraMoveFactor = 2.0f;

//UpdateBPM()
static constexpr const float MaxBPM = 180.0f;
static constexpr const float MinBPM = 70.0f;
static constexpr const float MinBPMStop = 80.0f;
static constexpr const float MinBPMWalk = 100.0f;




//BodyHeaving
static constexpr const float HeavingFactor = 40.0f;// ZOffset에서 BPM값을 몇으로 나누는지에 따라 Heaving 정도를 정할 수 있음.

// Sets default values
APlayerDoll::APlayerDoll()
{
 	PrimaryActorTick.bCanEverTick = true;

	// SpringArm 생성 및 위치 조정
	DefaultCameraSpringArm =  CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	DefaultCameraSpringArm->SetupAttachment(RootComponent); // RootComponent에 SpringArm Attach
	// SpringArm 초기 위치 설정
	DefaultCameraSpringArm->SetRelativeLocationAndRotation(FVector(80.0f,0.0f,60.0f), FRotator(0.0f, 0.0f, 0.0f));
	DefaultCameraSpringArm->TargetArmLength = 0.0f;
	DefaultCameraSpringArm->bEnableCameraLag = true;
	DefaultCameraSpringArm->CameraLagSpeed = 3.0f;

	// 카메라 최대 지연거리와 지연속도를 제한하여 콜리전 문제
	DefaultCameraSpringArm->CameraLagSpeed = 3.0f;
	DefaultCameraSpringArm->CameraLagMaxDistance = 20.0f;
	
	// spring arm의 collision을 계산해서 도움을 주는 기능이지만, 부자연스러운 카메라 움직임이 생겨서 꺼준다. 
	DefaultCameraSpringArm->bDoCollisionTest = false;

	// Camera 생성 및 SpringArm 소켓에 위치
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	DefaultCamera->SetupAttachment(DefaultCameraSpringArm, USpringArmComponent::SocketName);
	DefaultCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// WalkSound & RunSound
	WalkSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("WalkSound"));
	WalkSoundComponent->SetupAttachment(RootComponent);
	
	
	RunSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RunSound"));
	RunSoundComponent->SetupAttachment(RootComponent);

	
	// 기본 플레이어로 지정
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// initialize
	IsMouseRightButtonClick = false;
	IsBodyHeavingUp = false;

	IsRun = false;
	IsWalk = false;
	IsDead = false;
	HasKey = false;

	IsInteractionButtonDown = false;
	IsPickUpButtonDown = false;

	PlayerState = STOP;
	PrePlayerState = STOP;
	
	// 임시 팔 Sphere 생성
	PlayerHandSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerHandSocket"));
	PlayerHandSocket->SetupAttachment(DefaultCamera);
	// 임시 팔 Sphere 위치 설정
	PlayerHandSocket->SetRelativeLocation(FVector(25.0f, 15.0f,-7.5f));
	PlayerHandSocket->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	// Collision을 NoCollision으로 설정
	PlayerHandSocket->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void APlayerDoll::BeginPlay()
{
	Super::BeginPlay();
	
	// Pawn 초기 위치 설정
	//FVector InitialPosition = FVector(0.0f, 0.0f, 0.0f);
	//this->SetActorLocation(InitialPosition);
	
	// Initialize player bpm
	PlayerBPM = 80.0f;

	// Initialize Time Unit
	TimeUnit = 0.0f;

	// Initialize Player State
	WalkButtonPressCount = 0;
	RunButtonPressCount = 0;

}

// Called every frame
void APlayerDoll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Action Mapping에서 사용된 Bool 변수들을 통해  State설정
	SetPlayerState();
	PlayWalkSound();
	// 사망시 Camera의 위치를 제어하고, 이동을 
	if(IsDead)
	{
		//DefaultCamera->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
		//DefaultCamera->SetRelativeRotation(DefaultCamera->GetRelativeRotation() + FRotator(40.0f, 0.0f, 0.0f));
		InputComponent->RemoveAxisBinding("MoveForward");
		InputComponent->RemoveAxisBinding("MoveRight");
		InputComponent->RemoveAxisBinding("CameraPitch");
		InputComponent->RemoveAxisBinding("CameraYaw");
	}
	


	// Zoom 설정
	if(IsMouseRightButtonClick)
	{
		ZoomScale += DeltaTime / ZoomFactor;
	}
	else
	{
		ZoomScale -= DeltaTime / ZoomFactor;
	}
	// Zoom은 0~1 범위
	ZoomScale = FMath::Clamp<float>(ZoomScale, 0.0f, 0.2f);
	// Lerp -> Linear Interpolation으로 Zoom을 설정
	//DefaultCamera->FieldOfView = FMath::Lerp<float>(80.0f, 100.0f, ZoomScale);
	//DefaultCameraSpringArm->TargetArmLength = FMath::Lerp<float>(80.0f, 100.0f, ZoomScale);
	
	TimeUnit += DeltaTime;
	if(TimeUnit > UpdateTime)
	{
		UpdateBPM();
		BodyHeaving();
		
		TimeUnit = 0.0f;
	}
}

// Called to bind functionality to input
void APlayerDoll::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// PlayerInputComponent에서 받아온 입력을 Binding 해준다.
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Action Mapping의 Binding
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerDoll::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APlayerDoll::ZoomOut);
	InputComponent->BindAction("WalkForward", IE_Pressed, this, &APlayerDoll::WalkForwardButtonDown);
	InputComponent->BindAction("WalkForward", IE_Released, this, &APlayerDoll::WalkForwardButtonUp);
	InputComponent->BindAction("WalkRight", IE_Pressed, this, &APlayerDoll::WalkRightButtonDown);
	InputComponent->BindAction("WalkRight", IE_Released, this, &APlayerDoll::WalkRightButtonUp);
	InputComponent->BindAction("LieDown", IE_Pressed, this, &APlayerDoll::LieDownButtonDown);
	InputComponent->BindAction("LieDown", IE_Released, this, &APlayerDoll::LieDownButtonUp);
	InputComponent->BindAction("Run", IE_Pressed, this, &APlayerDoll::RunButtonDown);
	InputComponent->BindAction("Run", IE_Released, this, &APlayerDoll::RunButtonUp);
	InputComponent->BindAction("BreathHold", IE_Pressed, this, &APlayerDoll::BreathHoldButtonDown);
	InputComponent->BindAction("BreathHold", IE_Released, this, &APlayerDoll::BreathHoldButtonUp);
	InputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerDoll::InteractionButtonDown);
	InputComponent->BindAction("Interaction", IE_Released, this, &APlayerDoll::InteractionButtonUp);
	InputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerDoll::PickUpButtonDown);
	InputComponent->BindAction("PickUp", IE_Released, this, &APlayerDoll::PickUpButtonUp);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	
	
	// Axis Mapping의 Binding
	InputComponent->BindAxis("MoveForward", this, &APlayerDoll::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerDoll::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APlayerDoll::ChangeCameraPitch);
	InputComponent->BindAxis("CameraYaw", this, &APlayerDoll::ChangeCameraYaw);
}

void APlayerDoll::MoveForward(float AxisValue)
{
	int MoveSpeed = AxisValue;
	// Player State에 따라 이동속도 차등
	if(PlayerState == WALK)
	{
		MoveSpeed *= WalkSpeed;
	}
	else if(PlayerState == RUN)
	{
		MoveSpeed *= RunSpeed;
	}
	FVector NewLocation = GetActorLocation();
	// SpringArm을 기준으로 하여 현재 바라보고 있는 화면 기준으로 위치이동이 가능하게 함.
	NewLocation += DefaultCamera->GetForwardVector() * MoveSpeed; // 이동속도 결정
	this->SetActorLocation(NewLocation);
}

void APlayerDoll::MoveRight(float AxisValue)
{
	int MoveSpeed = AxisValue;
	// Player State에 따라 이동속도 차등
	if(PlayerState == WALK)
	{
		MoveSpeed *= WalkSpeed;
	}
	else if(PlayerState == RUN)
	{
		MoveSpeed *= RunSpeed;
	}
	FVector NewLocation = GetActorLocation();
	// SpringArm을 기준으로 하여 현재 바라보고 있는 화면 기준으로 위치이동이 가능하게 함.
	
	NewLocation += DefaultCamera->GetRightVector() * MoveSpeed;
	this->SetActorLocation(NewLocation);
}

void APlayerDoll::ChangeCameraPitch(float AxisValue)
{
	// SpringArm을 위 아래로 조정.
	FRotator NewRotation = DefaultCamera->GetComponentRotation();
	// Clamp를 통해 Y축 이동범위 제한
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue/CameraMoveFactor, -80.0f, 80.0f);
	DefaultCamera->SetWorldRotation(NewRotation);
}

void APlayerDoll::ChangeCameraYaw(float AxisValue)
{
	// Actor의 시야를 양 옆으로 조절.
	FRotator NewRotation = DefaultCamera->GetComponentRotation();
	// Clamp를 통한 제한은 없음.
	NewRotation.Yaw += AxisValue/CameraMoveFactor;
	DefaultCamera->SetWorldRotation(NewRotation);
}

void APlayerDoll::ZoomIn()
{
	IsMouseRightButtonClick = true;	
}

void APlayerDoll::ZoomOut()
{
	IsMouseRightButtonClick = false;
}

/* Player State에 따라 현재 BPM을 기준으로 다음 BPM을 결정. 이 과정은 약 1초마다 이루어짐.
STOP - BPM이 일정 이상인 경우 BPM 감소, 이 외에는 70~80 랜덤하게 가져감
WALK - BPM이 일정 이상인 경우 BPM 감소
RUN - BPM이 계속해서 상승하며 최대 180BPM으로 설정.
BREATH_HOLD - BPM을 빠르게 감소시킴.
*/
void APlayerDoll::UpdateBPM()
{
	int RandomInt = FMath::Rand();
	switch (PlayerState)
	{
	case STOP :
		if(PlayerBPM < MinBPMStop)
		{
			PlayerBPM = (RandomInt % 10) + MinBPM; // 기본 70~80 유지
		}
		else if(PlayerBPM >= MinBPMStop)
		{
			PlayerBPM -= (RandomInt % 2) + 3; // 3~5 하락
		}
		break;
	case WALK:
		if(PlayerBPM < MinBPMWalk)
		{
			PlayerBPM += RandomInt % 4; // 0~3 증가
		}
		else if(PlayerBPM >= MinBPMWalk)
		{
			PlayerBPM -= (RandomInt % 3) + 2; // 2~4 하락
		}
		break;
	case RUN:
			if (PlayerBPM && PlayerBPM < MaxBPM)
			{
				PlayerBPM += (RandomInt % 5) + 5; // 5~10 증가
				PlayerBPM = FMath::Min(PlayerBPM, MaxBPM);
			}
		break;
	case BREATH_HOLD:
		if (PlayerBPM > MinBPMStop)
		{
			PlayerBPM -= (RandomInt % 5) + 8; // 숨을 참은 경우 8~13씩 감소
			PlayerBPM = FMath::Max(PlayerBPM, MinBPM);
		}
		break;
	}
}

// Body Heaving with breath, 숨이 차서 몸을 헐떡거리는 기능
// IsBodyHeavingUp 변수를 통해 직전에 동작과 반대로 수행
void APlayerDoll::BodyHeaving()
{
	BodyHeavingTempLocation = DefaultCameraSpringArm->GetComponentLocation();
	float ZOffset = PlayerBPM / HeavingFactor;
	if (IsBodyHeavingUp)
	{
		BodyHeavingTempLocation -= FVector(0.0f, 0.0f, ZOffset);
	}
	else
	{
		BodyHeavingTempLocation += FVector(0.0f, 0.0f, ZOffset);
	}
	
	DefaultCameraSpringArm->SetWorldLocation(BodyHeavingTempLocation);
	IsBodyHeavingUp = !IsBodyHeavingUp;
}

// Action Mapping으로 Binding된 함수가 bool 변수로 각 행동의 입력상태를 알려주면,
// 이를 바탕으로 STATE 설정 / 행동의 우선순위는 BRETH_HOLD→RUN→WALK→STOP 으로 구성
void APlayerDoll::SetPlayerState()
{
	if(IsDead)
	{
		PlayerState = DEATH;	
	}
	else if(IsBreathHold)
	{
		PlayerState = BREATH_HOLD;
	}
	else if(IsRun)
	{
		PlayerState = RUN;
	}
	else if(IsWalk)
	{
		PlayerState = WALK;
	}
	else
	{
		PlayerState = STOP;
	}
}


// 아래 함수들은 이동에 따른 PlayerState 변화를 지정.
void APlayerDoll::WalkForwardButtonDown()
{
	WalkButtonPressCount++;
	if(WalkButtonPressCount == 1)
	{
		IsWalk = true;
	}
}
void APlayerDoll::WalkForwardButtonUp()
{
	if(WalkButtonPressCount>0)
	{
		WalkButtonPressCount--;
	}
	if(WalkButtonPressCount == 0)
	{
		IsWalk = false;
	}
}

void APlayerDoll::WalkRightButtonDown()
{
	WalkButtonPressCount++;
	if(WalkButtonPressCount == 1)
	{
		IsWalk = true;
	}
}

void APlayerDoll::WalkRightButtonUp()
{
	if(WalkButtonPressCount>0)
	{
		WalkButtonPressCount--;
	}
	if(WalkButtonPressCount == 0)
	{
		IsWalk = false;
	}
}

void APlayerDoll::LieDownButtonDown()
{
	RootComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
}

void APlayerDoll::LieDownButtonUp()
{
	RootComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void APlayerDoll::RunButtonDown()
{
	IsRun = true;
}

void APlayerDoll::RunButtonUp()
{
	IsRun = false;
}

void APlayerDoll::BreathHoldButtonDown()
{
	IsBreathHold = true;
}

void APlayerDoll::BreathHoldButtonUp()
{
	IsBreathHold = false;
}

void APlayerDoll::InteractionButtonDown()
{
	IsInteractionButtonDown = true;
}

void APlayerDoll::InteractionButtonUp()
{
	IsInteractionButtonDown = false;
}

void APlayerDoll::PickUpButtonDown()
{
	IsPickUpButtonDown = true;
}

void APlayerDoll::PickUpButtonUp()
{
	IsPickUpButtonDown = false;
}

FVector APlayerDoll::GetCameraForwardVector()
{
	return DefaultCamera->GetForwardVector();
}


void APlayerDoll::PlayWalkSound()
{
	//if(PrePlayerState == PlayerState){ return; }


	
	if(PlayerState == WALK)
	{
		//if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("소리가 들리니"));
		//}
		if(!WalkSoundComponent->IsPlaying())
		{
			WalkSoundComponent->Play();		
		}

		if(RunSoundComponent->IsPlaying())
		{
			RunSoundComponent->Stop();
		}
	}
	else if(PlayerState == RUN)
	{
		if(!RunSoundComponent->IsPlaying())
		{
			RunSoundComponent->Play();		
		}
		
		if(WalkSoundComponent->IsPlaying())
		{
			WalkSoundComponent->Stop();
		}
	}
	else if(PlayerState == STOP)
	{
		if(RunSoundComponent->IsPlaying())
		{
			RunSoundComponent->Stop();		
		}
		else if(WalkSoundComponent->IsPlaying())
		{
			WalkSoundComponent->Stop();
		}
	}
}
