// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArkanoidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LECTION2_API UArkanoidGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	// Инициализация экземпляра игрового приложения
	virtual void Init() override;
	// Сохарнение рекорда уровня
	TMap<FString, int32> LevelRecords;
	// Название файла для сохранения рекордов
	FString NameSaveFile = "RecordsSaveGame";

	void SetGameSettings() const;
	void SaveRecords() const;
	void LoadRecords();
	void DeleteRecords();

public:
	// Установка рекорда уровня по его имени
	UFUNCTION(BlueprintCallable, Category="SaveRecords")
	void SetLevelRecords(const FString& LevelName,const int32 NewRecord);
	// Получение рекорда уровня по его имени
	UFUNCTION(BlueprintPure, Category="SaveRecords")
	int32 GetLevelRecords(const FString& LevelName) const;
	

	
	
	
};
