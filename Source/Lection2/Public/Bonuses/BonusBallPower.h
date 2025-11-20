// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusBallPower.generated.h"

UCLASS()
class LECTION2_API ABonusBallPower : public ABonusParent
{
	GENERATED_BODY()

public:
	
	ABonusBallPower();

protected:
	virtual void BonusAction(APaddle* Paddle);

};
