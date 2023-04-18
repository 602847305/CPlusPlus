// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#if 1
#include "MyPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"//�������ͷ�ļ�
#include "GameFramework/SpringArmComponent.h" //���ɱ�ͷ�ļ�
#endif


// Sets default values
ACreature::ACreature()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�����
#if 1   //ʹ�����������Ϊ�����
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(80); //����ߴ�
	SphereComp->SetCollisionProfileName(TEXT("BlockAll")); //������ײ
	SphereComp->SetHiddenInGame(false);//��Ϸ����������
	SetRootComponent(SphereComp);
#else
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

#endif
	//����
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);


#if 1
	//
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		//��Դ�Ƿ���سɹ�
		if (MeshComponentAsset.Succeeded()) {
			//��������
			MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
			MeshComponent->SetRelativeLocation(FVector(0.f, 0, -50));
		}
#endif

#if 1
		SprintArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComp"));
		SprintArmComp->SetupAttachment(RootComponent); //�󶨵����
		SprintArmComp->TargetArmLength = 400; //���ɱ۳���
		SprintArmComp->SetRelativeRotation(FRotator(-45.f, 0, 0));//�������λ��
		SprintArmComp->bEnableCameraLag = true;//���Թ۸д�
		SprintArmComp->CameraLagSpeed = 3; 
#endif

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
#if 1
		Camera->SetupAttachment(SprintArmComp,USpringArmComponent::SocketName);//������󶨵����ɱ��ϣ�����->ָ����λ��"SocketName���"
#else
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.f,0,300));
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));
#endif
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

#if 1
	MovementComp = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MoveComponent"));
	MovementComp->UpdatedComponent = RootComponent;
#endif
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


}

//��ǰ�ƶ�
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

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
	SetActorLocation(NewLocation);


}

UPawnMovementComponent* ACreature::GetMovementComponent()const {
	return MovementComp;
}