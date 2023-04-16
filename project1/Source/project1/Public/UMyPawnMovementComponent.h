// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "UMyPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UUMyPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	

public:
	virtual void TickComponent();
};
