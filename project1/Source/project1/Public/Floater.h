// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class PROJECT1_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector InitialLocation;// = FVector(0);

	//ʵ�����ڿɼ�����ͼ�ɶ�д
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector PlacedLocation;

	//ʵ�����ڿɼ�����ͼ�ɶ�д
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	FVector InitialDirection;

	//���ⴰ�ڿɱ༭����ͼֻ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	bool bShouldFloat;

	//��ͼ���ڿɼ�����ͼ�ɶ�д
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bInitializeFloaterLocation;

	//�Ƿ�ʹ�þֲ�����
	UPROPERTY(EditAnywhere, Category = "Floater Variables")
	bool bIsLocal;


	UPROPERTY(EditAnywhere, Category = "Floater Variables")
	FRotator InitialRotator;


	UPROPERTY(EditAnywhere, Category = "Floater Variables")
		FVector InitialForce;

	UPROPERTY(EditAnywhere, Category = "Floater Variables")
		FVector InitialTorque;

	UPROPERTY(EditAnywhere, Category = "Floater Variables")
		float A;

	UPROPERTY(EditAnywhere, Category = "Floater Variables")
		float B;

private:
	float RunningTime;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
