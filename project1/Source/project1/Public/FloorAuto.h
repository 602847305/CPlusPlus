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

	//触发开关组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* TriggerBox;

	//开关
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* StoneSwitch;
	 

	//雕像
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Effigy;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialStoneSwitchLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialEffigyLocation;

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

	UFUNCTION(BlueprintImplementableEvent)
	void EffigyUp();

	UFUNCTION(BlueprintImplementableEvent)
	void EffigyLower();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StoneSwitchUp();

	UFUNCTION(BlueprintImplementableEvent)
	void StoneSwitchLower();

	UFUNCTION(BlueprintCallable)
	void  updateSwitchLocation(float z);

	UFUNCTION(BlueprintCallable)
	void updateEffigyLocation(float z);

};
