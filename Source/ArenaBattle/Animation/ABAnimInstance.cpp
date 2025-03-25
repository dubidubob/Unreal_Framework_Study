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
	
	//�ʱ�ȭ������ object�� ����, movement, owner�� ���� �ʱⰪ�� ����
	Owner = Cast<ACharacter>(GetOwningActor());//actor ��ȯ, acharacter�� ����ȯ, header include
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement) //�����Ӹ��� ������Ʈ
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); //x,y ���� �����´� (��(X��+Y��))
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling(); //ĳ���Ͱ� ���鿡 ������� ������ �� Falling���� ���ֵ�.
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould); //���� ��� ���� ��
	}
}
