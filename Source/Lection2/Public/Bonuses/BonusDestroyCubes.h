// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusParent.h"
#include "BonusDestroyCubes.generated.h"

UCLASS()
class LECTION2_API ABonusDestroyCubes : public ABonusParent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABonusDestroyCubes();

protected:
	virtual void BonusAction(APaddle* Paddle) override;
};
