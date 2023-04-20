// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	if (!Pawn) { 
		Pawn = TryGetPawnOwner();
		if (!Pawn)
		{
			return;
		}
	}
	


}

void UMyAnimInstance::UpdateAnimationProperties()
{
	if (!Pawn) { 
		Pawn = TryGetPawnOwner();
		if (!Pawn)
		{
			return;
		}
	}
	
	FVector Speed = Pawn->GetVelocity();//获取主角的速度
	FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0);
	MovementSpeed = LateralSpeed.Size();//更新速度
	IsJumping = Pawn->GetMovementComponent()->IsFalling();

}

