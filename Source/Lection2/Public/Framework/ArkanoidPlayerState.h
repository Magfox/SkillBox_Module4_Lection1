// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPlayerState.generated.h"
// Делегат изменения очков игрока
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, int32, PlayerScore);

UCLASS()
class LECTION2_API AArkanoidPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	int32 PlayerScore = 0;

public:
	// Делегат изменения очков игрока
	UPROPERTY(BlueprintAssignable, Category = "PlayerState") // Позволяет подписываться на событие в блюпринтах
	FOnPlayerScoreChanged OnPlayerScoreChanged;
	// Получение текущих очков игрока
	UFUNCTION(BlueprintPure, Category = "PlayerState")
	FORCEINLINE int32 GetPlayerScore() const {return PlayerScore;}
	// Изменение очков игрока на заданное значение
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void ChangePlayerScore(const int32 Amount);
};

