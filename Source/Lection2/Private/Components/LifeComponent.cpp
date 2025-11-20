// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LifeComponent.h"

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULifeComponent::SetLife(int32 NewLife)
{
	Life = FMath::Abs(NewLife); // Установка количества жизней с проверкой на неотрицательное значение
}

void ULifeComponent::TakeDamage(const int32 Damage)
{
	Life = FMath::Max(Life - Damage, 0); // Уменьшение количества жизней с проверкой на минимум 0
}

bool ULifeComponent::IsAlive() const
{
	return Life > 0; // Актор жив, если количество жизней больше нуля
}







