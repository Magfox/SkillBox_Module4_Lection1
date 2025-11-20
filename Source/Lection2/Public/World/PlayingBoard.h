// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayingBoard.generated.h"

class ABonusParent;
class ABlock;

// Структура для шанса выпадения типов бонусов
USTRUCT(BlueprintType)
struct FBonusTypeChance
{
	GENERATED_BODY()
	// Тип бонуса
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABonusParent> BonusClass = nullptr; // Класс бонуса
	// Шанс выпадения бонуса
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float DropChance = 0.2f; // Шанс выпадения бонуса
		
	
};

UCLASS()
class LECTION2_API APlayingBoard : public AActor
{
	GENERATED_BODY()

	private:
	// Компоненты актора
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, Categoty="Components"))
	USceneComponent* SceneRoot = nullptr; // Корневой компонент сцены
	// Компоненты превью бонусов на доске
	UPROPERTY() // Чтобы не удалялись сборщиком мусора
	TArray<UStaticMeshComponent*> PreviewComponents; // Массив компонентов превью бонусов
	// Акторы блоков на доске
	UPROPERTY()
	TArray<ABlock*> BlockActors; // Массив акторов блоков на доске


	void CreatePreviewComponents(); // Функция создания компонентов превью бонусов
	void ClearPreviewComponents(); // Функция очистки компонентов превью бонусов
	void SpawnBlockActors(); // Функция спавна блоков на доске
	// Настройки шанса выпадения бонусов
	UFUNCTION()
	void OnBlockDestroyed(AActor* DestroyedBlock); // Функция вызова при уничтожении блока
	
public:	
	// Sets default values for this actor's properties
	APlayingBoard();

protected:
	// Вызов при конструировании объекта в редакторе или при спавне в игре
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	// Функция получения класса бонуса на основе шанса выпадения
	TSubclassOf<ABonusParent> GetBonusClass();

public:
// Настройки доски и игры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Блупринт кубика"))
	TSubclassOf<ABlock> BlockClassForSpawn = nullptr; // Класс блока для спавна
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Меш для превью"))
	UStaticMesh* PreviewMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Масштаб блока"))
	FVector BlockScale = FVector(0.5f, 0.5f, 0.5f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Размер сетки по X"))
	int32 GridSizeX = 5; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Размер сетки по Y"))
	int32 GridSizeY = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Расстояние между блоками по X"))
	int32 SpacingX = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base", meta = (ToolTip = "Расстояние между блоками по Y"))
	int32 SpacingY = 60;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Game", meta = (ToolTip = "Сложность игры от 0.0 до 1.0",
	ClampMin = "0.0", ClampMax = "1.0"))
	float GameDifficulty = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Game", meta = (ToolTip = "Шанс выпадения бонуса от 0.0 до 1.0",
	ClampMin = "0.0", ClampMax = "1.0"))
	float BonusChance = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Game", meta = (ToolTip = "Массив настроек шанса выпадения типов бонусов",
	ClampMin = "0.0", ClampMax = "1.0"))
	TArray<FBonusTypeChance> BonusTypeByChances;


	void BonusDestroyCubes(const int32 Amount);
	
};
