// Fill out your copyright notice in the Description page of Project Settings.


#include "World/MyKillZone.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyKillZone::AMyKillZone()
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
	// Коллизия зоны убийства
	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Box"));
	KillBox->SetupAttachment(SceneRoot);
	KillBox->SetBoxExtent(FVector(50, 500, 50));
}

void AMyKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this) // Проверка валидности и что актор не сам себя
	{
		OtherActor->Destroy(); // Уничтожение перекрывающегося актора
	}
}





