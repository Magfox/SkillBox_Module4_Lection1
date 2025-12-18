// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Block.h"

#include "Bonuses/BonusParent.h"
#include "Components/LifeComponent.h"
#include "Framework/ArkanoidPlayerState.h"
#include "World/Ball.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh); // Установка статик меша в корневой компонент

	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent")); // Создание компонента жизней
	

}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
	// Установка материала в зависимости от оставшихся жизней при старте игры
	if (LifeMaterials.IsValidIndex(LifeComponent->GetLife() - 1)) // Проверка валидности индекса материала
		StaticMesh->SetMaterial(0, LifeMaterials[LifeComponent->GetLife() - 1]); // Установка материала в зависимости от оставшихся жизней
}

// Функция вызова при столкновении с другим компонентом
void ABlock::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (const auto Ball = Cast<ABall>(Other)) // Проверка, что столкнувшийся актор - мяч
	{
		if (IsValid(LifeComponent)) // Проверка валидности компонента жизней
		{
			LifeComponent->TakeDamage(Ball->GetPower()); // Нанесение урона блоку
			if (!LifeComponent->IsAlive()) // Проверка, жив ли блок после урона
			{
				if (BonusClass && GetWorld()) // Если класс бонуса установлен и мир валиден
				{
					const auto CurrentBonus = GetWorld()->SpawnActor<ABonusParent>
					(BonusClass, GetActorLocation(), GetActorRotation()); // Спавн бонуса в позиции и ротации блока
					//auto CurrentBonus = GetWorld()->SpawnActor<ABonusParent>(
					//	BonusClass, GetActorLocation(), GetActorRotation()); // Спавн бонуса в позиции и ротации блока
				}

				if (const auto Pawn = Cast<APawn>(Other->GetOwner())) // Получение владельца мяча и проверка, что это Pawn
				{
					if (auto PlayerState = Cast<AArkanoidPlayerState>(Pawn->GetPlayerState())) // Получение состояния игрока и проверка его валидности
						PlayerState->ChangePlayerScore(ScoreByLife * MaxLife); // Начисление очков игроку за разрушение блока
				}
				
				Destroy(); // Уничтожение блока после столкновения
			}
			else
			{
				if (LifeMaterials.IsValidIndex(LifeComponent->GetLife() - 1)) // Проверка валидности индекса материала
					StaticMesh->SetMaterial(0, LifeMaterials[LifeComponent->GetLife() - 1]); // Установка материала в зависимости от оставшихся жизней
			}
		}	
	}
}

void ABlock::Init(const FVector NewScale, const int32 LifeAmount, const TSubclassOf<ABonusParent> NewBonusClass)
{
	SetActorScale3D(NewScale); // Установка масштаба блока
	BonusClass = NewBonusClass; // Инициализация класса бонуса
	LifeComponent->SetLife(LifeAmount); // Установка количества жизней блока
	MaxLife = LifeAmount;// Установка максимального количества жизней блока
	
	if (LifeMaterials.IsValidIndex(LifeComponent->GetLife() - 1)) // Проверка валидности индекса материала
		StaticMesh->SetMaterial(0, LifeMaterials[LifeComponent->GetLife() - 1]); // Установка материала в зависимости от оставшихся жизней
}





