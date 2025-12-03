// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusSetDefaultPositionBall.h"

#include "Framework/Paddle.h"


ABonusSetDefaultPositionBall::ABonusSetDefaultPositionBall()
{
	
}


void ABonusSetDefaultPositionBall::BonusAction(APaddle* Paddle)
{
	Paddle->BonusSetDefaultPositionBallArrow();
	Super::BonusAction(Paddle);
}
