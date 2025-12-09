// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidGameState.h"



AArkanoidGameState::AArkanoidGameState()
{
	PrimaryActorTick.bCanEverTick = true; // Включение тика для обновления игрового времени
	
}

void AArkanoidGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameStarted) // Проверка, начата ли игра
	{
		GameTime += DeltaTime; // Обновление игрового времени
	}
}

void AArkanoidGameState::StartGame()
{
	bGameStarted = true; // Установка флага начала игры
}

void AArkanoidGameState::StopGame()
{
	bGameStarted = false; // Установка флага остановки игры
}

void AArkanoidGameState::GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const
{
	Minutes = static_cast<int32>(GameTime) / 60; // Вычисление минут
	Seconds = static_cast<int32>(GameTime) % 60; // Вычисление секунд
	Milliseconds = static_cast<int32>(GameTime - FMath::Floor(GameTime)) * 1000; // Вычисление миллисекунд
	
}
