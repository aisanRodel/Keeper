// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillDataStruct.h"
#include "Character/KeeperCharacter.h"

#include "Animation/AnimInstance.h"

SkillDataStruct::SkillDataStruct()
{
}

SkillDataStruct::~SkillDataStruct()
{
}

void FSkillDataStruct::Use(AKeeperCharacter* player)
{
	UE_LOG(LogTemp, Log, TEXT("Activated Skill :: %s"), *Name.ToString());

	// ��ų ��� �� �÷��̾��� ��ġ�� ���콺�� ��ġ�� �ʱ�ȭ
	PlayerPosition = player->GetActorLocation();
	APlayerController* MyPlayerController;
	MyPlayerController = player->GetWorld()->GetFirstPlayerController();
	if (MyPlayerController)
	{
		FHitResult Hit;
		MyPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			MouseCursorPosition = Hit.ImpactPoint;
		}

		UE_LOG(LogTemp, Log, TEXT("PlayerPos	:: %f, %f, %f"), PlayerPosition.X, PlayerPosition.Y, PlayerPosition.Z);
		UE_LOG(LogTemp, Log, TEXT("MousePos		:: %f, %f, %f"), MouseCursorPosition.X, MouseCursorPosition.Y, MouseCursorPosition.Z);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Not Found PlayerController!"));

	player->IncreasedMadness(Cost);

	// �ش� �κп��� ��ų ��� �� �ִϸ��̼ǰ� ����Ʈ ���� ó��(����)
	// Ÿ�Ժ��� �����ؼ� ����ü ���� �Էµ� ������ ���� ��ų�� Ȱ��ȭ(Notify���� ó���ؾ�������)
	switch (SkillType)
	{
	case ESkillAttackType::Melee:
	{
		UE_LOG(LogTemp, Log, TEXT("Melee Skill"));

		UAnimInstance* AnimInstance = player->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			if (SkillAnimMontage)
				AnimInstance->Montage_Play(SkillAnimMontage);
			else
				DrawDebugSphere(player->GetWorld(), PlayerPosition + player->GetActorForwardVector() * 100.0f, Range, 26, FColor::Red, false, 3.0f, 0, 2);
		}

		break;
	}
	case ESkillAttackType::Ranged:
	{
		UE_LOG(LogTemp, Log, TEXT("Ranged Skill"));
		//static ConstructorHelpers::FClassFinder<AActor>ProjectileRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Skills/BP_CTestProjectile.BP_CTestProjectile'"));
		FVector newDir = MouseCursorPosition - PlayerPosition;
		newDir.Z = 0.0f;
		//if (Projectile) {
		//	FVector PlayerLocation = FVector(PlayerPosition.X, PlayerPosition.Y, 60.0f);
		//	TObjectPtr<ASkillProjectile> TempProjectile = Cast<ASkillProjectile>(player->GetWorld()->SpawnActor(Projectile, &PlayerLocation));
		//	if (TempProjectile) TempProjectile->ShootProjectile(newDir);
		//}
		break;
	}

	default:
		break;
	}
}
