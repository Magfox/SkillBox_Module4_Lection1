// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusParent.h"

#include "Framework/Paddle.h"


// Sets default values
ABonusParent::ABonusParent()
{
	
	PrimaryActorTick.bCanEverTick = true;

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	SetRootComponent(BonusMesh);

	BonusMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);// колизия уведомляет, но проходит сквозь объекты
	BonusMesh->SetCollisionObjectType(ECC_WorldDynamic);
	BonusMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		BonusMesh->SetStaticMesh(MeshAsset.Object);
	}
}


void ABonusParent::BeginPlay()
{
	Super::BeginPlay();

	Direction = Direction.GetSafeNormal();// нормализуем вектор
}


void ABonusParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Move(DeltaTime);
}

void ABonusParent::NotifyActorBeginOverlap(class AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		if (auto Paddle = Cast<APaddle>(OtherActor))
		{
			BonusAction(Paddle);
		}
	}
}

void ABonusParent::Move(const float DeltaTime)
{
	const FVector Offset = Direction * Speed * DeltaTime;
	AddActorLocalOffset(Offset);
}

void ABonusParent::BonusAction(APaddle* Paddle)
{
	Destroy();
}


void ABonusParent::InitScale(const FVector& NewScale)
{
	SetActorScale3D(NewScale);
}

