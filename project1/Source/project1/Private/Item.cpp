// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(RootComponent);

	Rotate = false;
	RotationSpeed = 100;

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__func__));

	if (ParticleOverlap) {
		//ָ��λ������һ������ϵͳ����������������Ϸ�д�����Ч����ը�������Ӿ�Ч����
		//ָ��Ҫ���ɵ�����ϵͳ���͡�����λ�á���ת�Ƕ��Լ�������ѡ������
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleOverlap, GetActorLocation());
	}
	if (SoundOverlap) {
		UGameplayStatics::PlaySound2D(GetWorld(), SoundOverlap);
	}
	Destroy();
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	//��̬���¼�
	//������������OnBeginOverlap������ӵ�SphereComp��OnComponentBeginOverlap�¼��У�
	//��SphereComp���������巢����ײʱ�����OnEndOverlap������
	//AddDynamic������Ҫ��������������һ�����¼���Ӧ�����Ķ����ʵ����һ������Ӧ������ָ�롣
	//�����this��ʾ��ǰAItemʵ����ָ�룬& AItem::OnBeginOverlap���ʾOnBeginOverlap������ָ�롣
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnOverlapBegin);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Rotate)
	{
		FRotator Rotation = MeshComp->GetComponentRotation();
		Rotation.Yaw += DeltaTime * RotationSpeed;
		MeshComp->SetWorldRotation(Rotation);
	}

}



