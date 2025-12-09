// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameMode.generated.h"


UCLASS()
class LECTION2_API AArkanoidGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArkanoidGameMode();// Конструктор класса	
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "ArkanoidGameMode")
	void GameStarted(); 
	UFUNCTION(BlueprintCallable, Category = "ArkanoidGameMode")
	void GameEnded();
};
