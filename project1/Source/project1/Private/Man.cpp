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

	BaseTurnRate = 65;  //��ת��
	BaseLookupRate = 65;  //��ת��
	bUseControllerRotationYaw = false; //ģ�����岻�����������ת
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
	//�������ƶ�
	if (Controller && Value != 0) {
		//��ȡ����������ת
		const FRotator Rotation = Controller->GetControlRotation(); 
		//������ת
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);
		//������ת����
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//ǰ������뵽�˶������
		AddMovementInput(Direction, Value);
	}
}

void AMan::MoveRight(float Value)
{
	//�������ƶ�
	if (Controller && Value != 0) {
		//��ȡ����������ת
		const FRotator Rotation = Controller->GetControlRotation();
		//������ת
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);
		//������ת����
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//ǰ������뵽�˶������
		AddMovementInput(Direction, Value);
	}
}

void AMan::TurnAtRate(float Value)
{
	//������ƫ������                ��ת�ٶȿ�����            ��֮֡���ʱ��
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void AMan::TurnLookupRate(float Value)
{
	//������ƫ������                ��ת�ٶȿ�����            ��֮֡���ʱ��
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

	//�󶨶���
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//����
	PlayerInputComponent->BindAxis("MoveForward", this, &AMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMan::MoveRight);

	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("Lookup", this, &AMan::TurnLookupRate);
	PlayerInputComponent->BindAxis("Turn", this, &AMan::TurnAtRate);

}

