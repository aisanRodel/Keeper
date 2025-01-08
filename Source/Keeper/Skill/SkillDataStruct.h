// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataStruct.generated.h"


class KEEPER_API SkillDataStruct
{
public:
	SkillDataStruct();
	~SkillDataStruct();
};

// ��ų���� ����, ������� ��ų�� ��� ��ų�¿� ���ԵǾ����� ������ ����.
UENUM(BlueprintType)
enum class ESkillSetType : uint8
{
	DefalutSet	UMETA(DisplayName = "Defalut"),
	BeastSet	UMETA(DisplayName = "Beast")
};

// ��ų�� ���� ���, �ش� ��ų�� ������ ��������, ���Ÿ����� ������ ����.
UENUM(BlueprintType)
enum class ESkillAttackType : uint8
{
	Melee	UMETA(DisplayName = "Melee"),
	Ranged	UMETA(DisplayName = "Ranged")
};

USTRUCT(Atomic, BlueprintType)
struct FSkillDataStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	void Use(class AKeeperCharacter* player);
	uint8 IsCooldown() { return bIsCooldown; }
	void StartCooldown() { bIsCooldown = true; }
	void EndCooldown() { bIsCooldown = false; }

public:
	// ---------- ��ų���� ���� ----------
	// ��ų�� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name; 
	// ��ų ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;	
	// ��ų�� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;	
	// ��ų�� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondToCooldown;	
	// ��Ÿ�� Ȱ��ȭ ����
	UPROPERTY()
	uint8 bIsCooldown : 1;	
	// ��ų�� ����(��Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;	
	// ��ų Ÿ��(�ӽ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillAttackType SkillType;	
	// ���Ÿ� ��ų�� ����ü
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> Projectile;	

	// ��ų �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* SkillAnimMontage;	

	// <��ų ������ �߰��Ǿ�� �ϴ� ����>
	//  - ��ų �ε���, ��ų ����(����(����, ����), ���Ÿ�(����, ����), ������, ����, Ʈ����), ��ų�� ������ġ����(QWER �� ��� ��ġ����), ��ų�� ��������(� ��ų������)
	//  - ���Ÿ� ��ų�� ��� ��ų�� �ʿ��� ����ü ���Ͱ� �ʿ�.
	//  - ������ ��ų�� ��� �ش� ��ų�� ���ӽð� ���� �ʿ�.
	//  - ��ų�� ������ ��Ÿ��� �и� �ʿ� >>> ���������� ���Ǵ� ��찡 ����, ex) �����ϸ� ����, �������� ���� �� �ֺ��� ������ ���� ������ ��
	//  - ��ų�� ������ ���� ���� �ʿ�(��ų�� �⺻������, �÷��̾��� ���ݷ��� ������� �������� �δ���, �߰� ��ġ�� �־����� ��찡 �ִ����� ���)
	//  - (����, ����) ������ �ǰݵ� ��(��)���� �����̻��� �ο��ؾ� �ϴ� ��찡 �־ ���� �ʿ�.
	//  - ��ų ���ӿ� �ǹ̿� ���� �̾߱Ⱑ �ʿ��� ���Դϴ�. 
	//		��ų �ߵ� �� ���ӽð��� �帣�� ������ ������ ��Ÿ��(������) / ��ų �ߵ� ���� ���ӽð��� �����ϰ� �ٷ� ��Ÿ��(���� �ο�)
	//		������ �÷��̾� ĳ���Ϳ��� '����'�� ����ǰ� UI���� ǥ���Ѵٰ� �ߴµ� ������ ��ų�� ���� ��ų�� ���̴�?


	// ---------- �÷��̾��� ���� ----------
	// �÷��̾��� ��ġ
	UPROPERTY()
	FVector PlayerPosition;			
	// ���콺�� ��ġ
	UPROPERTY()
	FVector MouseCursorPosition;	
	// �÷��̾��� �ִ� ü��
	//UPROPERTY()
	//float MaxHp;				
	// �÷��̾��� ���� ü��
	//UPROPERTY()
	//float CurrentHp;			
	// �÷��̾��� ���ݷ�
	//UPROPERTY()
	//float AttackPower;			
	// �÷��̾��� �̵��ӵ�
	//UPROPERTY()
	//float MovementSpeed;		
	// �÷��̾��� ü��ȸ����
	//UPROPERTY()
	//float GenerationHp;			
	// ���� ������ �ڽ�Ʈ, �� ���� ������ ���� ������ ��
	//int32 CurrentStackedCost;	

	// [��ų ������ �÷��̾� ������ �ʿ��Ѱ�? �÷��̾� ���ݰ� ���õ� ������ �ϴ� �Լ��� ĳ�����ʿ��� �����޾� ����ϴ°� ����� �� ������...]

	// <�÷��̾� ������ �߰��Ǿ�� �ϴ� ����>
	//  - ���� ����� ���� ���� ����, �÷��̾��� ���� ��üü��
	//  - �÷��̾��� ���� ������ ����� �ʿ��Ѱ���?
	//		'��ų ��뿡 ���� ������ ����' �����̶�� [�÷��̾� ĳ���� �ڵ�]���� '���⸦ ������Ű�� �Լ�'�� ����� ȣ���ϴ°� ������ �մϴ�.
	//		���⸦ ���̹����ִ� ��ų������ �ִ°Ŷ�� ��ų �ߵ� ���� '����'�� �ο��ϰ� óġ �� �ش� ������ �Ҹ��Ͽ� ���⸦ ���ߴ� �� ���..

	// ---------- �ڽ�Ʈ ----------
	// ��ų�� �ڽ�Ʈ, ��� �� ��� ������ ���� �ǹ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;	


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

	// <��ų ������ ���� ����>
	// ��ų ������ ��ȭ�� ���� ��ų�� ������ ��ų ������ ��Ʈ�� ���� ����� �����Ѵ�.
	// �׸��� ���� ����� ��ų�� ������ ������ �� �� ��ų ������ŭ�� ���� �迭�� ���� ��
	// ��ų���� ���� �ε����� �ο��ϰ� �ش� �ε����� ũ�⸦ ��ȭ��Ű�� ������� �����Ѵ�.
	// �� �� ��ų ������ ��Ʈ������ 
	// [ (��ų �ε���) * (��ų �ִ� ����) + {(��ų�� ���� ����) - 1} ]
	// ������ ���� �ش� ��ų�� ������ �´� �����͸� ȣ���� �� �� �ְ� �Ѵ�.
	// � ��ų�� ���������� ���� ��� -1�� �Ҵ��Ͽ� �����Ѵ�.
	// �ִϸ��̼��� ��� �ش� �ִϸ��̼��� ��θ� �����Ѵ�.(������)
};