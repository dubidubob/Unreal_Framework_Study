// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "ABComActionData.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
 	//Pawn 회전
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    //Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    //Movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    //Mesh
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/ Script / Engine.SkeletalMesh'/Game/ParagonMorigesh/Characters/Heroes/Morigesh/Meshes/Morigesh.Morigesh'"));
    if (CharacterMeshRef.Object)
    {
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/ArenaBattle/Animations/ABP_ABCharacter.ABP_ABCharacter_C"));
    if(AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }
    
    static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
    if (ShoulderDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
    }

    static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quater.ABC_Quater'"));
    if (QuaterDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
    }
}

void AABCharacterBase::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
    //pawn
    bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

    //character movement
    GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
    GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
    GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AABCharacterBase::ProcessComboCommand()//Combo Action Section : 몽타주를 재생
{
    if (CurrentCombo == 0)
    {
        ComboActionBegin();
        return;
    }
    if (!ComboTimerHandle.IsValid())//이미 타이머가 발동돼서 시기를 놓쳤거나, 더이상 발동될 필요가 없다
    {
        HasNextComboCommand = false;
    }
    else
    {
        HasNextComboCommand = true;
    }
}

void AABCharacterBase::ComboActionBegin()
{
    //combo status
    CurrentCombo = 1;

    //movement setting
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//아무 이동도 하게 되지 않음

    //animation setting
    const float AttackSpeedRate = 1.0f;

    //몽타주 재생
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate); //기본 1.0초로 재생

    FOnMontageEnded EndDelegate; //구조체같은 걸 선언
    EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);//바인드시켜줌
    AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);//몽타주 종료될 때 아래 함수 선언

    ComboTimerHandle.Invalidate();
    SetComboCheckTimer();
}

void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropelyEnded)
{
    ensure(CurrentCombo != 0); //0이면 출력 로그에 에러 나옴
    CurrentCombo = 0;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); //다시 걷기 모드로

}

void AABCharacterBase::SetComboCheckTimer()
{
    int32 ComboIndex = CurrentCombo - 1;
    ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

    const float AttackSpeedRate = 1.0f;
    float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate)/AttackSpeedRate;
    if (ComboEffectiveTime > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false); //현재 클래스에 있는 combocheck, 루프는 끈다.
    }
}


void AABCharacterBase::ComboCheck()
{
    ComboTimerHandle.Invalidate(); //더 이상 발동되면 안 되니까 비활성화
    if (HasNextComboCommand)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        
        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
        FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
        AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);//해당 세션으로 바로 점프
        SetComboCheckTimer();
        HasNextComboCommand = false;
    }
}

