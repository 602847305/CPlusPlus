// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Man.generated.h"

UCLASS()
class PROJECT1_API AMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMan();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent *Camera;


	float BaseTurnRate;
	float BaseLookupRate;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void TurnLookupRate(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input 输入组件设置
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
