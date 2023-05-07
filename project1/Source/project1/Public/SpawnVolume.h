// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"



UCLASS()
class PROJECT1_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UBoxComponent* SpawnBox;

	UFUNCTION(BlueprintPure)
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintCallable)//À¶Í¼¿Éµ÷ÓÃ
	FVector GetSpawnPointDummy(FVector Value);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class AActor> PawnToSpawn;

	//UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	//void SpawnMyPawn(UClass*PawnClass,FVector const&Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
