﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Melee UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged")
};

USTRUCT(Atomic, BlueprintType)
struct FSkillCustomData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FSkillCustomData();

public:
	void Use(class AKeeperCharacter* player);
	uint8 IsCooldown() { return bIsCooldown; }
	void StartCooldown() { bIsCooldown = true; }
	void EndCooldown() { bIsCooldown = false; }
	
public:
	// ---------- 스킬만의 정보 ----------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name; // 스킬 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;	// 스킬 설명
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;	// 스킬의 현재 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondToCooldown;	// 스킬의 쿨타임
	uint8 bIsCooldown : 1;	// 쿨타임 활성화 유무
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;	// 스킬의 범위(사거리)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType SkillType;	// 스킬 타입(임시)
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> Projectile;	// 원거리 스킬의 투사체

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UAnimMontage* SkillMontage;	// 스킬 애니메이션 몽타주

	// <스킬 정보에 추가되어야 하는 내용>
	//  - 스킬 인덱스, 스킬 종류(근접(단일, 광역), 원거리(단일, 광역), 지속형, 재사용, 트리거), 스킬의 지정위치정보(QWER 중 어느 위치인지), 스킬의 집합정보(어떤 스킬셋인지)
	//  - 원거리 스킬의 경우 스킬에 필요한 투사체 액터가 필요.
	//  - 지속형 스킬의 경우 해당 스킬의 지속시간 정보 필요.
	//  - 스킬의 범위와 사거리의 분리 필요 >>> 복합적으로 사용되는 경우가 존재, ex) 전진하며 공격, 전방으로 도약 후 주변의 적에게 광역 데미지 등
	//  - 스킬의 데미지 공식 구상 필요(스킬의 기본데미지, 플레이어의 공격력을 어느정도 비중으로 두는지, 추가 수치가 주어지는 경우가 있는지를 고려)
	//  - (단일, 광역) 구분은 피격된 적(들)에게 상태이상을 부여해야 하는 경우가 있어서 구분 필요.
	//  - 스킬 지속에 의미에 대해 이야기가 필요해 보입니다. 
	//		스킬 발동 후 지속시간이 흐르고 지속이 끝나면 쿨타임(지속형) / 스킬 발동 직후 지속시간과 무관하게 바로 쿨타임(버프 부여)
	//		이전에 플레이어 캐릭터에게 '버프'가 적용되고 UI에도 표시한다고 했는데 지속형 스킬과 버프 스킬의 차이는?


	// ---------- 플레이어의 정보 ----------
	FVector PlayerPosition;			// 플레이어의 위치
	FVector MouseCursorPosition;	// 마우스의 위치

	//float MaxHp;				// 플레이어의 최대 체력
	//float CurrentHp;			// 플레이어의 현재 체력
	//float AttackPower;			// 플레이어의 공격력
	//float MovementSpeed;		// 플레이어의 이동속도
	//float GenerationHp;			// 플레이어의 체력회복량
	//int32 CurrentStackedCost;	// 현재 누적된 코스트, 즉 현재 누적된 광기 게이지 량

	// <플레이어 정보에 추가되어야 하는 내용>
	//  - 현재 적용된 버프 누적 정보, 플레이어의 현재 대체체력
	//  - 플레이어의 현재 누적된 광기는 필요한가요?
	//		'스킬 사용에 따른 광기의 증가' 때문이라면 [플레이어 캐릭터 코드]에서 '광기를 증가시키는 함수'를 만들어 호출하는게 나을듯 합니다.
	//		광기를 페이백해주는 스킬때문에 있는거라면 스킬 발동 직후 '버프'를 부여하고 처치 시 해당 버프를 소모하여 광기를 낮추는 게 어떨지..

	// ---------- 코스트 ----------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Cost;	// 스킬의 코스트, 사용 시 얻는 광기의 양을 의미


	/*FSkillCustomData& operator=(const FSkillCustomData& Other) {
		if (this == &Other) return *this;

		Name = Other.Name;
		Description = Other.Description;
		CurrentLevel = Other.CurrentLevel;
		Range = Other.Range;
		Cost = Other.Cost;
		SecondToCooldown = Other.SecondToCooldown;

		return *this;
	}*/

	// <스킬 레벨에 대한 구상>
	// 스킬 레벨의 변화에 따른 스킬의 정보는 스킬 데이터 시트를 따로 만들어 관리한다.
	// 그리고 현재 적용된 스킬의 레벨을 저장할 때 총 스킬 개수만큼의 정수 배열을 만든 후
	// 스킬에게 각각 인덱스를 부여하고 해당 인덱스의 크기를 변화시키는 방법으로 저장한다.
	// 이 때 스킬 데이터 시트에서는 
	// [ (스킬 인덱스) * (스킬 최대 레벨) + {(스킬의 현재 레벨) - 1} ]
	// 공식을 통해 해당 스킬의 레벨에 맞는 데이터를 호출해 올 수 있게 한다.
	// 어떤 스킬도 지정되있지 않은 경우 -1을 할당하여 구분한다.
	// 애니메이션의 경우 해당 애니메이션의 경로를 저장한다.(생각중)
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEEPER_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

	//FSkillCustomData* GetSkillCustomData(int32 index);

private:
	//class UDataTable* KeeperSkillData;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FSkillCustomData SkillToQ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FSkillCustomData SkillToW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FSkillCustomData SkillToE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FSkillCustomData SkillToR;

	//스킬 인덱스로 정보줘서 키 맵핑하기
	//설정한 키를 입력했을 때 정상적으로 정보를 출력하는지 확인
	//스킬에 필요한 정보 다시 정리해서 구조체 재작성하기

	//스킬 UI, 아이템 UI 등을 위한 Slot 작성
	//스킬이 Slot을 통해 스왑되게 하기

};