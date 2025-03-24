// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	//GENERATED_BODY() �� ���ؼ�
	//this declaration has no storage class or type specifier �̷� ������ ��
	//uproperty�� ; ���̸� �� �Ǵµ� �ٿ���.
	GENERATED_BODY()
	
public:
	AABCharacterPlayer();

protected:
	virtual void BeginPlay() override; //mapping context ó���� �������ִ� ����, Ű���忡�� ������ Ű�е带 ���ؼ� �������� ���⼭ mapping context�� ���� ������ �ȴ�.

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//�𸮾� �Է� �ý��۰� �Ʒ� ���� �ý����� �̸� ����

//Character control section
protected:
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType); //������ change ����
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData) override;

//Camera Section // Meta, allowprivateaccess�� �������Ʈ������ access�ϰ� ���ִ� Ư���� ������.
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//Input Section //���� �ý���, �̺�Ʈ �׼��� ���� ������Ʈ. �����Ӱ� �ٱ� �� �ֵ��� Edit Anywhere ����.
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);

	void QuaterMove(const FInputActionValue& Value);

	//���� � �� �������� Ȯ���ϱ� ���ؼ�
	ECharacterControlType CurrentCharacterControlType;
};
