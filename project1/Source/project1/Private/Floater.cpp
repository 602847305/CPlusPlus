// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	
	InitialLocation = FVector(0);
	
	
	InitialDirection = FVector(1);
	InitialRotator = FRotator(0);
	
	PlacedLocation = FVector(0);

	InitialTorque = FVector(0);
	InitialForce = FVector(0);

	bShouldFloat = false;
	bInitializeFloaterLocation = false;
	bIsLocal = false;

	RunningTime = 0;
	A = 1;
	B = 1;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();
	//SetActorLocation(InitialLocation);
	PlacedLocation = GetActorLocation();
	if (bInitializeFloaterLocation)
	{
		SetActorLocation(InitialLocation);
	}

	//PlacedLocation = GetActorLocation();

	//StaticMesh->AddForce(InitialForce);
	//StaticMesh->AddTorque(InitialTorque);
	float initialX = FMath::FRand() * 500;
	float initialY = FMath::FRandRange(100,500);
	float initialZ = 0;
	SetActorLocation(FVector(initialX, initialY, initialZ));
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	RunningTime += DeltaTime;
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = A * FMath::Sin(B * RunningTime);

	SetActorLocation(NewLocation);


	if (bShouldFloat)
	{
		if (bIsLocal)
		{
			AddActorLocalOffset(InitialDirection);
			AddActorLocalRotation(InitialRotator);
		}
		else
		{
			AddActorWorldOffset(InitialDirection);
			AddActorWorldRotation(InitialRotator);
		}



	
	
	
	
	}
	else {
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, true, &HitResult);

		//if (HitResult.bBlockingHit){
		

		
			UE_LOG(LogTemp,Warning,
				TEXT("%%f Hit@: x=%f , y=%f , z = %f"),
				HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z
			);

			UE_LOG(LogTemp, Warning,
				TEXT("%%s Hit@: x=%s , y=%s , z = %s"),
				*FString::SanitizeFloat(HitResult.Location.X), 
				*FString::SanitizeFloat(HitResult.Location.Y), 
				*FString::SanitizeFloat(HitResult.Location.Z)
				);
		//}
	}




}

