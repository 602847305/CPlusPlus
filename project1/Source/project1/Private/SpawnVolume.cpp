// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Engine/World.h"
#include "Creature.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
}


FVector ASpawnVolume::GetSpawnPoint()//��������λ��
{
	FVector Extent = SpawnBox->GetScaledBoxExtent();//���ӵĳ����
	FVector Origin = SpawnBox->GetComponentLocation();//��ȡ�������ĵ��λ��
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);//��ȡ���λ��
	return Point;
}

FVector ASpawnVolume::GetSpawnPointDummy(FVector Value)
{
	return FVector();
}

//void ASpawnVolume::SpawnMyPawn_Implementation(UClass* PawnClass, FVector const& Location)
//{
//	if (PawnClass)
//	{
//		UWorld* MyWorld = GetWorld();
//		if (MyWorld)
//		{
//			ACreature* Creature = MyWorld->SpawnActor<ACreature>(PawnClass, Location,FRotator(0.f));
//		}
//	}
//}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

