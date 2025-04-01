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
	FString MontageSectionNamePrefix;//몽타주 섹션 이름 지정

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount;//최대 콤보 개수

	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;//프레임의 기준 재생 속도

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EffectiveFrameCount;//프레임 안에 들어왔는지
};
