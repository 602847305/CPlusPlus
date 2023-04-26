// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorAuto.h"
#include"Components/BoxComponent.h"
#include"Components/StaticMeshComponent.h"



// Sets default values
AFloorAuto::AFloorAuto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetBoxExtent(FVector(64,64,16));//����TriggerBox�Ĵ�С
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//��ײ��ʹ��->ѯ��
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);//ѡ�����������->�����еľ�̬����
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);//������ײ����Ϊ->����
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StoneSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoneSwitch"));
	StoneSwitch->SetupAttachment(RootComponent);


	Effigy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Effigy"));
	StoneSwitch->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AFloorAuto::BeginPlay()
{
	Super::BeginPlay();
	//�õ�����ĳ�ʼλ��
	InitialStoneSwitchLocation = StoneSwitch->GetComponentLocation();
	InitialEffigyLocation = Effigy->GetComponentLocation();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this,&AFloorAuto::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this,&AFloorAuto::OnOverlapEnd);

	

}

// Called every frame
void AFloorAuto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//�ص�״̬��ʼ
void AFloorAuto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));

	EffigyLower();//�����½�
	StoneSwitchLower();//�����½�
}

//�ص�״̬����
void   AFloorAuto::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	EffigyUp();//��������
	StoneSwitchUp();//��������
}

void AFloorAuto::updateSwitchLocation(float z)
{
	FVector Location = InitialStoneSwitchLocation;
	Location.Z += z;
	StoneSwitch->SetWorldLocation(Location);

}

void AFloorAuto::updateEffigyLocation(float z)
{
	FVector Location = InitialEffigyLocation;
	Location.Z += z;
	Effigy->SetWorldLocation(Location);

}

