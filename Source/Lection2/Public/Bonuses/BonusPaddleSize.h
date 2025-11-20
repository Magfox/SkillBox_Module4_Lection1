// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusPaddleSize.generated.h"

UCLASS()
class LECTION2_API ABonusPaddleSize : public ABonusParent
{
	GENERATED_BODY()

public:
	
	ABonusPaddleSize();

protected:
	virtual void BonusAction(APaddle* Paddle) override; 	

};
