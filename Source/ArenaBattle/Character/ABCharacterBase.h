// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta=(AllowPrivateAccess="true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

//Combo Action Section : 몽타주를 재생
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropelyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0; //내부에서만 사용, 콤보 어디까지 왔는지. Uproperty 안 붙임, 0일 때는 콤보 시작 안 했다.
	FTimerHandle ComboTimerHandle; //언리얼에서 제공하는 타이머
	bool HasNextComboCommand = false;//발동한 타이머 이전에 입력 커맨드가 들어왔는지를 점검해보는 값, 그래서 integer로 선언할 필요벗다
};
