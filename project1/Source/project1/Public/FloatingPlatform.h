// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class PROJECT1_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent * Mesh;

	UPROPERTY(EditAnywhere)
	FVector StartPoint;

	UPROPERTY(EditAnywhere,meta=(MakeEditWidget = "true"))
	FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WanderSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WanderTime;

	FTimerHandle WanderTimer;//计时器，用来控制浮动时间

	bool bWanderingUp;//是否向上浮动

	void ToggleWandering();//切换浮动方向

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
