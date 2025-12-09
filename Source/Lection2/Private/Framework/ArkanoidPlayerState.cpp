// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidPlayerState.h"

void AArkanoidPlayerState::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);// Обновление очков игрока, не позволяя им стать отрицательными
	OnPlayerScoreChanged.Broadcast(PlayerScore); // Вызов делегата изменения очков игрока
	UE_LOG(LogTemp, Log, TEXT("PlayerScore Changed = %d"), PlayerScore);// Логирование изменения очков игрока
}
