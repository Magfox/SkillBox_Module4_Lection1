// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidGameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SaveFiles/RecordsSaveGame.h"

void UArkanoidGameInstance::Init()
{
	Super::Init();

	SetGameSettings();
	LoadRecords();
}

void UArkanoidGameInstance::SetGameSettings() const
{
	if (!GEngine)// Проверка на существование движка
		return;
	
	GEngine->GameUserSettings->SetVSyncEnabled(true);// Включение вертикальной синхронизации
	GEngine->GameUserSettings->ApplySettings(true);// Применение настроек игры
	GEngine->GameUserSettings->SaveSettings();// Сохранение настроек игры
	GEngine->Exec(GetWorld(), TEXT("T.MaxFPS 60"));// Ограничение частоты кадров до 60
}

void UArkanoidGameInstance::SaveRecords() const
{
	// Создание объекта для сохранения рекордов
	auto SaveGameFile = Cast<URecordsSaveGame>(UGameplayStatics::LoadGameFromSlot(NameSaveFile, 0));

	if (!SaveGameFile)// Если файл сохранения не существует, создаем новый
		SaveGameFile = Cast<URecordsSaveGame>(UGameplayStatics::CreateSaveGameObject(URecordsSaveGame::StaticClass()));

	if (SaveGameFile)
	{
		SaveGameFile->SavedRecords = LevelRecords;// Копирование текущих рекордов в объект сохранения
		UGameplayStatics::SaveGameToSlot(SaveGameFile, NameSaveFile, 0);// Сохранение объекта в слот
	}

}

void UArkanoidGameInstance::LoadRecords()
{
	// Загрузка объекта сохранения из слота
	const auto LoadedSaveGame = UGameplayStatics::LoadGameFromSlot(NameSaveFile, 0);
	// Проверка успешной загрузки и приведение к типу URecordsSaveGame
	if (const auto SaveGameFile = Cast<URecordsSaveGame>(LoadedSaveGame))
		LevelRecords = SaveGameFile->SavedRecords;// Копирование сохраненных рекордов в текущие рекорды
}

void UArkanoidGameInstance::DeleteRecords()
{
	if (UGameplayStatics::DoesSaveGameExist(NameSaveFile, 0))// Проверка существования файла сохранения
	{
		UGameplayStatics::DeleteGameInSlot(NameSaveFile, 0);// Удаление файла сохранения
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
	-1, // Уникальный ключ сообщения
	30.0f, // Время отображения сообщения на экране
	FColor::Green, // Цвет сообщения
	FString::Printf(
		TEXT("Удаление файла сохранения (ArkanoidGameInstance) %s"),
		*NameSaveFile));// Вывод сообщения об удалении файла сохранения
	}
}

void UArkanoidGameInstance::SetLevelRecords(const FString& LevelName, const int32 NewRecord)
{
	if (NewRecord > GetLevelRecords(LevelName)) // Если новый рекорд лучше текущего
	{
		LevelRecords.Add(LevelName, NewRecord);// Обновление рекорда для уровня
		SaveRecords();// Сохранение обновленных рекордов
	}
}

int32 UArkanoidGameInstance::GetLevelRecords(const FString& LevelName) const
{
	return LevelRecords.FindRef(LevelName);// Возвращение рекорда для указанного уровня 
}
