// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#if 1
#include "MyPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"//球形组件头文件
#include "GameFramework/SpringArmComponent.h" //弹簧臂头文件
#endif


// Sets default values
ACreature::ACreature()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//跟组件
#if 1   //使用球形组件作为跟组件
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(80); //组件尺寸
	SphereComp->SetCollisionProfileName(TEXT("BlockAll")); //开启碰撞
	SphereComp->SetHiddenInGame(false);//游戏开启后隐藏
	SetRootComponent(SphereComp);
#else
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

#endif
	//网格
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);


#if 1
	//
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		//资源是否加载成功
		if (MeshComponentAsset.Succeeded()) {
			//设置网格
			MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
			MeshComponent->SetRelativeLocation(FVector(0.f, 0, -50));
		}
#endif

#if 1
		SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComp"));
		SpringArmComp->SetupAttachment(RootComponent); //绑定到组件
		SpringArmComp->TargetArmLength = 400; //弹簧臂长度
		SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0, 0));//设置相对位置
		SpringArmComp->bEnableCameraLag = true;//弹性观感打开
		SpringArmComp->CameraLagSpeed = 3;
#endif

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
#if 1
		Camera->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);//摄像机绑定到弹簧臂上，参数->指定绑定位置"SocketName插槽"
#else
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.f,0,300));
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));
#endif

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	MovementComp = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MoveComponent"));
	MovementComp->UpdatedComponent = RootComponent;

	//视角变化量，初始化为0向量
	CameraInput = FVector2D(0.f, 0);


}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACreature::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACreature::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ACreature::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ACreature::CameraYaw);

}

//向前移动
void ACreature::MoveForward(float Value)
{
	//CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	//AddMovementInput(GetActorForwardVector() * Value);

	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorForwardVector() * Value);
	}
}

void ACreature::MoveRight(float Value)
{
	//CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorRightVector() * Value);
	}

}

//记录鼠标运动Y
void ACreature::CameraPitch(float Value)
{
	CameraInput.Y = Value;
}

//记录鼠标运动X
void ACreature::CameraYaw(float Value)
{
	CameraInput.X = Value;
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//旋转 ： 新的旋转方向
	FRotator NewRotation = GetActorRotation(); 
	NewRotation.Yaw += CameraInput.X; 
	SetActorRotation(NewRotation);

	//向上向下看使用弹簧臂控制，首先拿到原始角度
	FRotator NewSpringArmRotation = SpringArmComp->GetComponentRotation(); 
	NewSpringArmRotation.Pitch += CameraInput.Y;
	//加上角度约束
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch, -80.f, -15.f);
	//设置弹簧臂的角度
	SpringArmComp->SetWorldRotation(NewSpringArmRotation);

}

UPawnMovementComponent* ACreature::GetMovementComponent()const {
	return MovementComp;
}

