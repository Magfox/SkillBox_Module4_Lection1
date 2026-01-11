// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class ABall;
class UArrowComponent;
class UBoxComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class LECTION2_API APaddle : public APawn
{
	GENERATED_BODY()

private:
	// Компоненты каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Category="Components"))
	UBoxComponent* BoxCollider = nullptr; // Коллайдер каретки для обработки столкновений
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Category="Components"))
	UStaticMeshComponent* StaticMesh = nullptr; // Статик меш каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Category="Components"))
	UStaticMeshComponent* LeftStaticMesh = nullptr; // Левый статик меш каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Category="Components"))
	UStaticMeshComponent* RightStaticMesh = nullptr; // Правый статик меш каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true", Category="Components"))
	UArrowComponent* Arrow = nullptr; // Стрелка направления движения каретки

	// Ссылка на мяч, с которым взаимодействует каретка чтобы сборщик мусора его не удалил
	UPROPERTY()
	ABall* CurrentBall = nullptr;
	
	// Контекст ввода для каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;
	// Действие ввода для выхода из игры
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EscapeAction = nullptr;
	// Действие ввода для спавна мяча
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SpawnBallAction = nullptr;
	// Действие ввода для движения каретки
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	// Для визуализации шариков жизни под кареткой
	UPROPERTY()
	TArray<UStaticMeshComponent*> BallLives; // Количество шариков жизни
	void SpawnBallLives();//Спавн шариков под кареткой
	void UpdateBallLivesLocation();//Расположение шариков


public:
	APaddle();

protected:
	// Вызов при конструировании объекта в редакторе или при спавне в игре
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Функция выхода из игры
	UFUNCTION()
	void ExitGame();
	// Функция спавна мяча
	UFUNCTION()
	void StartGame();
	// Функция движения каретки
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	//Спавн шара
	UFUNCTION()
	void SpawnBall();
	// Смерть шара
	UFUNCTION()
	void BallIsDead();

public:
	// Класс меча для спавна
	UPROPERTY(EditAnywhere, Category = "Settings|Game", meta = (ToolTip="Класс меча для спавна"))
	TSubclassOf<ABall> BallClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Game", meta = (ToolTip="Количество жизней игрока"))
	int32 Lives = 3; // Количество жизней игрока
	UPROPERTY(EditAnywhere, Category = "Settings|Game", meta = (ToolTip="Масштаб каретки по умолчанию"))
	FVector DefaultScale = FVector(0.4f, 2.4f, 0.5f); // Масштаб каретки по умолчанию
	// Скорость движения каретки
	UPROPERTY(EditAnywhere, Category = "Settings|Game", meta = (ToolTip="Скорость движения каретки"))
	float Speed = 2000.0f;

	//Работа с бонусами
protected:
	FTimerHandle TimerForBonusSize;
	UFUNCTION()
	void SetDefaultSize();
public:
	void BonusChangeSize(const float AdditionalSize, const float BonusTime);// Функция изменения размера каретки
	void BonusChangeLife(const int32 Amount);// Функция изменения жизней
	void BonusChangeBallSpeed(const float Amount);// Функция изменения скорости шаров
	void BonusChangeBallPower(const int32 Amount, const float BonusTime);// Функция изменения мощности шаров
	void BonusSetDefaultPositionBallArrow(); // Функция Возвращения мяча к каретке
};
