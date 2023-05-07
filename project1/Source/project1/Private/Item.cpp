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
		//指定位置生成一个粒子系统。它可以用于在游戏中创建特效、爆炸和其他视觉效果。
		//指定要生成的粒子系统类型、生成位置、旋转角度以及其他可选参数。
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
	//动态绑定事件
	//这里是用来将OnBeginOverlap函数添加到SphereComp的OnComponentBeginOverlap事件中，
	//在SphereComp与其它物体发生碰撞时会调用OnEndOverlap函数。
	//AddDynamic函数需要传入两个参数，一个是事件响应函数的对象或实例，一个是响应函数的指针。
	//这里的this表示当前AItem实例的指针，& AItem::OnBeginOverlap则表示OnBeginOverlap函数的指针。
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



