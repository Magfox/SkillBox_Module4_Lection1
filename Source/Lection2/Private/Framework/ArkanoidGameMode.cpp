// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidGameMode.h"

#include "Framework/ArkanoidGameState.h"
#include "Framework/ArkanoidPC.h"
#include "Framework/ArkanoidPlayerState.h"

AArkanoidGameMode::AArkanoidGameMode()
{
	GameStateClass = AArkanoidGameState::StaticClass();// Установка класса состояния игры
	PlayerStateClass = AArkanoidPlayerState::StaticClass(); // Установка класса состояния игрока
}

void AArkanoidGameMode::BeginPlay()
{
	Super::BeginPlay(); 

	GameStarted();
}

void AArkanoidGameMode::GameStarted()
{
	
	auto ArkanoidGameState = Cast<AArkanoidGameState>(GameState);
	if (ArkanoidGameState)
		ArkanoidGameState->StartGame();
}

void AArkanoidGameMode::GameEnded(const bool bIsWinner)
{
	auto ArkanoidGameState = Cast<AArkanoidGameState>(GameState);
	if (ArkanoidGameState)
		ArkanoidGameState->StopGame();

	UE_LOG(LogTemp, Warning, TEXT("GameEnded"));

	for (APlayerState* PlayerState : GameState->PlayerArray)
	{
		if (PlayerState)
		{
			const auto Player = Cast<AArkanoidPC>(PlayerState->GetPlayerController());
			if (Player)
			{
				Player->ShowGameEndMenu(bIsWinner);
			}
		}
			
		
	}
}
