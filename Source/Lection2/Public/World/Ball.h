// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"
// Объявляем делегат ивента
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadEvent); 


class UArrowComponent;


// Перечисление состояний мяча
UENUM(BlueprintType) 
enum class EState : uint8
{
	idle, // В покое
	moving, // В движении
};

// Структура для инициализационных параметров мяча
USTRUCT(BlueprintType)
struct FInitParameters 
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Стартовый размер"))
	float Scale;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Начальная сила"))
	int32 Power;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Начальная скорость"))
	float Speed;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Максимальная скорость"))
	float MaxSpeed;
	// Конструктор структуры по умолчанию
	FInitParameters()
	{
		Scale = 0.50f;
		Power = 1;
		Speed = 500.0f;
		MaxSpeed = 2500.0f;
	}
};

UCLASS()
class LECTION2_API ABall : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr; // Статик меш для мяча
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr; // Стрелка направления вперёд
	// Инициализационные параметры мяча
	int32 Power = 1;
	float Speed = 500.0f;
	FVector Direction = FVector::ZeroVector;
	EState State = EState::idle;
	
public:	
	ABall();
	
	UPROPERTY(BlueprintAssignable)
	FOnDeadEvent OnDeadEvent;
	// Материал который будет зависеть от силы шара и задаем его в БП
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UMaterialInterface* PowerMaterial = nullptr;
	
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	FInitParameters InitParameters; // Инициализационные параметры мяча

	// Функция движения мяча
	UFUNCTION(BlueprintCallable, Category = Ball)
	void Move(const float DeltaTime);
public:
	FORCEINLINE int32 GetPower() const { return Power; } // Получение силы мяча
	// Функция установки направления движения мяча
	void SetBallState(const EState NewState);

	
// Бонусная секция
	FTimerHandle TimerBallPower;
	UPROPERTY()
	UMaterialInterface* DefaultMaterial = nullptr;
	// Установка дефолтного материала
	void UpdateBallMaterial();
	// Возвращаем базовую скорость шара
	void ResetBallPower();

	
public:
	// Функция изменения скорости шара
	void ChangeSpeed(const float Amount);
	// Функция изменения силы шара
	void ChangeBallPower(const int32 Amount, const float BonusTime);
	
};
