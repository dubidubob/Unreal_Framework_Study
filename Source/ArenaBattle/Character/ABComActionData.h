// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABComActionData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABComActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UABComActionData();

	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix;//��Ÿ�� ���� �̸� ����

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount;//�ִ� �޺� ����

	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;//�������� ���� ��� �ӵ�

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EffectiveFrameCount;//������ �ȿ� ���Դ���
};
