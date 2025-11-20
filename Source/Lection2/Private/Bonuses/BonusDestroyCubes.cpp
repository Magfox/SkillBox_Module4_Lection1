// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusDestroyCubes.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "World/PlayingBoard.h"


// Sets default values
ABonusDestroyCubes::ABonusDestroyCubes()
{
	Value = 3.0f;
}

void ABonusDestroyCubes::BonusAction(APaddle* Paddle)
{
	//TArray<AActor*> PlayingBoard;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayingBoard::StaticClass(),PlayingBoard);

	for (TActorIterator<APlayingBoard> It(GetWorld()); It; ++It)// Проходим по всем элементам APlayingBoard
	{
		/*
		const auto CurrentBoard = *It
		if (CurrentBoard && FMath::RandBool())// Если несколько плей бордов то выберет 1
		*/
		
		if (const auto CurrentBoard = *It)
		{
			CurrentBoard->BonusDestroyCubes(Value);
			return;
		}
	}
	Super::BonusAction(Paddle);
}



