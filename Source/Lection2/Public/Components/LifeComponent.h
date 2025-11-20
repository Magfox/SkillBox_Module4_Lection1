// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LECTION2_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULifeComponent();

	protected:
	// Вызов при старте игры
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
	int32 Life = 1;

	public:
	// Установка количества жизней
	UFUNCTION(BlueprintCallable)
	void SetLife(const int32 NewLife);
	// Получение количества жизней
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetLife() const { return Life; } 
	// Функция получения урона
	UFUNCTION(BlueprintCallable)
	void TakeDamage(const int32 Damage = 1);
	// Проверка, жив ли актор
	UFUNCTION(BlueprintPure)
	bool IsAlive() const;
		
};
