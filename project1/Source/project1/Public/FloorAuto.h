// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorAuto.generated.h"

UCLASS()
class PROJECT1_API AFloorAuto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorAuto();

	//�����������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* TriggerBox;

	//����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* StoreSwitch;
	 
	//ʯͷ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Store1;

	//ʯͷ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Store2;

	//ʯͷ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Store3;

	//����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Effigy;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor *actor,
			UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,
			bool bFormSweep,const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* actor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
