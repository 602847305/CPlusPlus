// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	WanderSpeed = 4;
	WanderTime = 5;

}


void AFloatingPlatform::ToggleWandering()
{
	bWanderingUp = !bWanderingUp;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	bWanderingUp = true;
	GetWorldTimerManager().SetTimer(WanderTimer,this,&AFloatingPlatform::ToggleWandering,WanderTime,true);
	
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation;
	if (bWanderingUp) {
		TargetLocation = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, WanderSpeed);
	}
	else
	{
		TargetLocation = FMath::VInterpTo(CurrentLocation, StartPoint, DeltaTime, WanderSpeed);
	}
	
	SetActorLocation(TargetLocation);



}

