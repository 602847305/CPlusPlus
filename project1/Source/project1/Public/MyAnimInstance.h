// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;// �ƶ��ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsJumping;//�Ƿ�����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;//����ָ��

	virtual void NativeInitializeAnimation()override;//��д��ʼ��

	UFUNCTION(BlueprintCallable, Category = AnimationProperty)
	void UpdateAnimationProperties();// ���¶���������

	

};
