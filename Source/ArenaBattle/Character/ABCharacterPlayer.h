// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	//GENERATED_BODY() 에 대해서
	//this declaration has no storage class or type specifier 이런 오류가 떠
	//uproperty에 ; 붙이면 안 되는데 붙여서.
	GENERATED_BODY()
	
public:
	AABCharacterPlayer();

protected:
	virtual void BeginPlay() override; //mapping context 처음에 매핑해주는 역할, 키보드에서 받을지 키패드를 통해서 받을지는 여기서 mapping context를 통해 받으면 된다.

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//언리얼 입력 시스템과 아래 매핑 시스템을 미리 매핑

//Character control section
protected:
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType); //실제로 change 진행
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData) override;

//Camera Section // Meta, allowprivateaccess는 블루프린트에서도 access하게 해주는 특별한 지시자.
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//Input Section //매핑 시스템, 이벤트 액션을 위한 오브젝트. 자유롭게 바굴 수 있도록 Edit Anywhere 설정.
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

	//현재 어떤 뷰 상태인지 확인하기 위해서
	ECharacterControlType CurrentCharacterControlType;
};
