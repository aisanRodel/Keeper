// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/BaseSkillDamageField.h"
#include "Components/SphereComponent.h"
#include "Monster/MonsterBase.h"

// Sets default values
ABaseSkillDamageField::ABaseSkillDamageField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CachedRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(CachedRootComponent);
}

void ABaseSkillDamageField::CreateDamageField_Sphere(float Radius, float Damage)
{
	SetDamage(Damage);

	HitSphereComponent = NewObject<USphereComponent>(this);
	HitSphereComponent->SetSphereRadius(Radius);

	HitSphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HitSphereComponent->SetGenerateOverlapEvents(true);

	HitSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSkillDamageField::OnOverlapBegin);

	HitSphereComponent->RegisterComponent();
	HitSphereComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HitSphereComponent->SetLineThickness(10.0f);
}

void ABaseSkillDamageField::SetDamage(float ActualDamage)
{
	DamageAmount = ActualDamage;
}

// Called when the game starts or when spawned
void ABaseSkillDamageField::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseSkillDamageField::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AMonsterBase* Monster = Cast<AMonsterBase>(OtherActor);
		if (Monster)
		{
			Monster->TakeDamage(DamageAmount);

			UE_LOG(LogTemp, Warning, TEXT("Damage %f applied to Monster: %s"), DamageAmount, *OtherActor->GetName());
		}
	}
}
