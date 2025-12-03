// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusLife.h"

#include "Framework/Paddle.h"


ABonusLife::ABonusLife()
{
	// Добавление количества жизней
	Value = 1.0f; 
}

void ABonusLife::BonusAction(APaddle* Paddle)
{
	Paddle->BonusChangeLife(Value);// Добавляем жизни
	Paddle->BonusChangeSpawnBall();
	Super::BonusAction(Paddle);
}



