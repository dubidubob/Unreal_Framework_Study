// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	//초기화에서는 object에 대한, movement, owner에 대한 초기값을 지정
	Owner = Cast<ACharacter>(GetOwningActor());//actor 반환, acharacter로 형변환, header include
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement) //프레임마다 업데이트
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); //x,y 값만 가져온다 (√(X²+Y²))
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling(); //캐릭터가 지면에 닿아있지 않으면 → Falling으로 간주됨.
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould); //위로 상승 중일 때
	}
}
