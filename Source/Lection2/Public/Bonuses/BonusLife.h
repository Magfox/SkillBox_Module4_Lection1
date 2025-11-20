// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusLife.generated.h"

UCLASS()
class LECTION2_API ABonusLife : public ABonusParent
{
	GENERATED_BODY()

public:

	ABonusLife();

protected:
	virtual void BonusAction(APaddle* Paddle) override;	

};
