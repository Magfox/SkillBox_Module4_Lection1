// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusPaddleSize.h"

#include "Framework/Paddle.h"


// Sets default values
ABonusPaddleSize::ABonusPaddleSize()
{
	Duration = 10.0f; // Время действия бонуса
}

void ABonusPaddleSize::BonusAction(APaddle* Paddle)
{

	Paddle->BonusChangeSize(Value, Duration);
	
	Super::BonusAction(Paddle);
}


