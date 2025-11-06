// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Spawner.h"

#include "Components/ArrowComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Создание компонентов актора 
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Toot"));
	SetRootComponent(SceneRoot);
	// Стрелка направления спавна
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(SceneRoot);
	ForwardArrow->SetAbsolute(false,false, true); // Только ротация будет абсолютной
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnActor(); // Вызов функции спавна актора при старте игры
}

void ASpawner::SpawnActor()
{	
	if (SpawnedClass) // Если класс для спавна установлен
	{
		if (const auto World = GetWorld()) // Получение мира
		{
			World->SpawnActor<AActor>(SpawnedClass, ForwardArrow->GetComponentLocation(), ForwardArrow->GetComponentRotation());// Спавн актора в позиции и ротации стрелки
		}
	}
	

	

}



