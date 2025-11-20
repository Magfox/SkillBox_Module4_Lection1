// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ball.h"

#include "Components/ArrowComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh")); // Создание компонента статик меш
	SetRootComponent(StaticMesh);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow")); // Создание компонента стрелки
	ForwardArrow->SetupAttachment(StaticMesh); 

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere")); // Загрузка меша сферы из движка
	if (SphereMeshAsset.Succeeded()) // Если меш успешно загружен
	{
		StaticMesh->SetStaticMesh(SphereMeshAsset.Object); // Установка меша для статик меша
	}
}
// Вызов при конструировании объекта в редакторе или при спавне в игре 
void ABall::OnConstruction(const FTransform& Transform)
{
	// Вызов родительской реализации
	Super::OnConstruction(Transform);
	
	SetActorScale3D(FVector(InitParameters.Scale)); // Установка масштаба мяча
	Power = InitParameters.Power; // Инициализация силы мяча
	Speed = InitParameters.Speed; // Инициализация скорости мяча
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	Direction = GetActorForwardVector().GetSafeNormal(); // Инициализация направления мяча
	// Базовй материал
	if (StaticMesh)
	{
		DefaultMaterial = StaticMesh->GetMaterial(0);
	}
	UpdateBallMaterial();
	SetBallState(EState::moving); // Установка состояния мяча в движение
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Логика в зависимости от состояния мяча
	switch (State)
	{
	case EState::idle: // В покое
		break;
	case EState::moving: // В движении
		Move(DeltaTime);// Вызов функции движения мяча
		break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("ABall::Tick: Unknown State")); // Логирование неизвестного состояния
		break;
	}
	
	
}

void ABall::Destroyed()
{
	OnDeadEvent.Broadcast();
	Super::Destroyed();
	
}

void ABall::Move(const float DeltaTime)
{
	const FVector Offset = Direction * Speed * DeltaTime; // Вычисление смещения мяча
	FHitResult HitResult; // Результат столкновения
	AddActorWorldOffset(Offset, true, &HitResult); // Перемещение мяча

	if (HitResult.bBlockingHit)
	{
		Direction = Direction - 2 * (FVector::DotProduct(Direction,
			HitResult.Normal)) * HitResult.Normal; // Вычисление нового направления мяча после столкновения
		Direction.Z = 0; // Обнуление вертикальной составляющей направления
		Direction = Direction.GetSafeNormal(); // Нормализация направления

		if (Speed < InitParameters.MaxSpeed)
		{
			Speed += InitParameters.Speed * 0.1f; // Увеличение скорости мяча после столкновения
			Speed = FMath::Min(Speed, InitParameters.MaxSpeed); // Ограничение скорости максимальным значением
		}
		UE_LOG(LogTemp, Warning, TEXT("Ball name %s is speed %f"), *GetName(), Speed); // Логирование текущей скорости мяча
	}
}

void ABall::SetBallState(const EState NewState)
{
	State = NewState; // Установка нового состояния мяча
}

void ABall::UpdateBallMaterial()
{
	if (!StaticMesh)
	{
		return;
	}
	if (Power > 1)
	{
		if (PowerMaterial) // Установлен ли материал в БП 
		{
			StaticMesh->SetMaterial(0, PowerMaterial);
		}
	}
	else
	{
		StaticMesh->SetMaterial(0, DefaultMaterial);
	}
}

void ABall::ResetBallPower()
{
	Power = InitParameters.Power; //Возвращаем базовое значения из конструктора
	UpdateBallMaterial();
}

void ABall::ChangeSpeed(const float Amount)
{
	if (Amount < 0)
	{
		Speed = FMath::Min(Speed - Speed * Amount, InitParameters.Speed);// Чтобы скорость не стала ниже минимума
	}
	else if (Amount > 0)
	{
		Speed = FMath::Max(Speed + Speed * Amount, InitParameters.MaxSpeed);// Чтобы скорость не стала больше максимума
	}
}

void ABall::ChangeBallPower(const int32 Amount, const float BonusTime)
{
	if (Amount != 0 && BonusTime > 0)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerBallPower))// Проверяем активен ли таймер
		{
			Power = FMath::Max(Power + Amount, 1); // Сила не может быть меньше 1
			UpdateBallMaterial();
		}
		GetWorld()->GetTimerManager().SetTimer( // Запускаем таймер
			TimerBallPower,
			this,
			&ABall::ResetBallPower,
			BonusTime,
			true);
	}
}

