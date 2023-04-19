// Fill out your copyright notice in the Description page of Project Settings.


#include "Man.h"

#if 1
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#endif
#if 2
#include"GameFramework/Controller.h"
#include"Engine/World.h"
#include"Components/InputComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#endif
// Sets default values
AMan::AMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	SpringArmComp->SetupAttachment(RootComponent); 
	SpringArmComp->TargetArmLength = 600;
	SpringArmComp->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

#if 2

	BaseTurnRate = 65;  //旋转率
	BaseLookupRate = 65;  //旋转率
	bUseControllerRotationYaw = false; //模型主体不跟随控制器旋转
	bUseControllerRotationPitch = false; 
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540, 0);
	GetCharacterMovement()->JumpZVelocity = 650;
	GetCharacterMovement()->AirControl = 0.2f;

#endif


}


void AMan::MoveForward(float Value)
{
	//控制器移动
	if (Controller && Value != 0) {
		//获取控制器的旋转
		const FRotator Rotation = Controller->GetControlRotation(); 
		//构造旋转
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);
		//构造旋转矩阵
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//前方向加入到运动组件中
		AddMovementInput(Direction, Value);
	}
}

void AMan::MoveRight(float Value)
{
	//控制器移动
	if (Controller && Value != 0) {
		//获取控制器的旋转
		const FRotator Rotation = Controller->GetControlRotation();
		//构造旋转
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);
		//构造旋转矩阵
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//前方向加入到运动组件中
		AddMovementInput(Direction, Value);
	}
}

void AMan::TurnAtRate(float Value)
{
	//控制器偏移输入                旋转速度控制量            两帧之间的时间
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void AMan::TurnLookupRate(float Value)
{
	//控制器偏移输入                旋转速度控制量            两帧之间的时间
	AddControllerPitchInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

// Called when the game starts or when spawned
void AMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定动作
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//轴向
	PlayerInputComponent->BindAxis("MoveForward", this, &AMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMan::MoveRight);

	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("Lookup", this, &AMan::TurnLookupRate);
	PlayerInputComponent->BindAxis("Turn", this, &AMan::TurnAtRate);

}

