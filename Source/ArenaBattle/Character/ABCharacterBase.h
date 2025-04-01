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

//Combo Action Section : ��Ÿ�ָ� ���
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

	int32 CurrentCombo = 0; //���ο����� ���, �޺� ������ �Դ���. Uproperty �� ����, 0�� ���� �޺� ���� �� �ߴ�.
	FTimerHandle ComboTimerHandle; //�𸮾󿡼� �����ϴ� Ÿ�̸�
	bool HasNextComboCommand = false;//�ߵ��� Ÿ�̸� ������ �Է� Ŀ�ǵ尡 ���Դ����� �����غ��� ��, �׷��� integer�� ������ �ʿ����
};
