// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Creature.generated.h"

UCLASS()
class PROJECT1_API ACreature : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//玩家输入（键盘或者鼠标输入）
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;


	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SprintArmComp;

	UPROPERTY(VisibleAnywhere)
	class UMyPawnMovementComponent* MovementComp;

	
	virtual UPawnMovementComponent* GetMovementComponent() const override;








private:

	void MoveForward(float Value);
	void MoveRight(float Value);



};
