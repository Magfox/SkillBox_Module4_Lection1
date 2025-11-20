// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusBallPower.h"

#include "Framework/Paddle.h"


ABonusBallPower::ABonusBallPower()
{
	Value = 1.0f; // Сила
	Duration = 10.0f; // Время действия
}

void ABonusBallPower::BonusAction(APaddle* Paddle)
{
	Paddle->BonusChangeBallPower(Value, Duration);
	Super::BonusAction(Paddle);
}



