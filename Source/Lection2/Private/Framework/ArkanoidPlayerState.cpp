// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidPlayerState.h"

#include "Framework/ArkanoidGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidPlayerState::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);// Обновление очков игрока, не позволяя им стать отрицательными
	// Получение ссылки на игровой экземпляр для возможного использования
	if (const auto Gi = Cast<UArkanoidGameInstance>(GetGameInstance()))
		// Установка рекорда уровня в игровом экземпляре
		Gi->SetLevelRecords(UGameplayStatics::GetCurrentLevelName(this), PlayerScore);


	OnPlayerScoreChanged.Broadcast(PlayerScore); // Вызов делегата изменения очков игрока
	UE_LOG(LogTemp, Log, TEXT("PlayerScore Changed = %d"), PlayerScore);// Логирование изменения очков игрока
}
