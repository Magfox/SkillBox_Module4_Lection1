// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusSetDefaultPositionBall.generated.h"

UCLASS()
class LECTION2_API ABonusSetDefaultPositionBall : public ABonusParent
{
	GENERATED_BODY()

public:
	ABonusSetDefaultPositionBall();

protected:
	virtual void BonusAction(APaddle* Paddle) override;

};
