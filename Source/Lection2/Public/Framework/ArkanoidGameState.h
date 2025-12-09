// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ArkanoidGameState.generated.h"


UCLASS()
class LECTION2_API AArkanoidGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	float GameTime = 0.0f;
	bool bGameStarted = false;

protected:
	// Обновление игрового времени каждый тик
	virtual void Tick(float DeltaTime) override;

public:
	AArkanoidGameState(); // Конструктор класса

	void StartGame(); // Функция начала игры
	void StopGame(); // Функция остановки игры
	// Функция получения игрового времени
	UFUNCTION(BlueprintPure, Category = "GameState")
	void GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const; 
};
