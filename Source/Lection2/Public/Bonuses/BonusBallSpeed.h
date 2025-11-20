// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusBallSpeed.generated.h"

UCLASS()
class LECTION2_API ABonusBallSpeed : public ABonusParent
{
	GENERATED_BODY()

public:
	
	ABonusBallSpeed();

protected:
	virtual void BonusAction(APaddle* Paddle) override;
};
