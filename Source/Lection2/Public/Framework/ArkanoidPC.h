// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPC.generated.h"



UCLASS()
class LECTION2_API AArkanoidPC : public APlayerController
{
	GENERATED_BODY()
public:
	void ExitButtonPressed();
	void ShowGameEndMenu(const bool bWinStatus);
};
