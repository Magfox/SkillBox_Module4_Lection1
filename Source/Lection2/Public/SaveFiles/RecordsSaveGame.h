// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RecordsSaveGame.generated.h"



UCLASS()
class LECTION2_API URecordsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TMap<FString, int32> SavedRecords; // Карта для сохранения рекордов 
};
