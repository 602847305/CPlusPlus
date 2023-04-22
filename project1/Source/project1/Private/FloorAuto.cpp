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

	TriggerBox->SetBoxExtent(FVector(64,64,32));//����TriggerBox�Ĵ�С
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//��ײ��ʹ��->ѯ��
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);//ѡ�����������->�����еľ�̬����
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);//������ײ����Ϊ->����
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(64, 64, 32));


}

// Called when the game starts or when spawned
void AFloorAuto::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this,&AFloorAuto::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this,&AFloorAuto::OnOverlapEnd);

}

// Called every frame
void AFloorAuto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorAuto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
}

void   AFloorAuto::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

