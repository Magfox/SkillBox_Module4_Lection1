// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

class AArkanoidGameState;
class AArkanoidPlayerState;
class UTextBlock;

UCLASS()
class LECTION2_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// Свойства для привязки виджетов из UMG через BindWidget
	UPROPERTY(meta = (BindWidget,  AllowPrivateAccess = "true"))
	UTextBlock* CurrentScore = nullptr; // очки игрока
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* GameTime = nullptr; // время игры
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* LevelRecord = nullptr; // рекорд уровня
	UPROPERTY(Transient,meta = ( BindWidgetAnim, AllowPrivateAccess = "true"))
	UWidgetAnimation* ShakeAnimation = nullptr;// анимация тряски при получении урона

	UPROPERTY()
	AArkanoidPlayerState* PlayerState = nullptr; // ссылка на PlayerState
	UPROPERTY()
	AArkanoidGameState* GameState = nullptr; // ссылка на GameState

protected:
	// переопределяем функцию конструктора виджета
	virtual void NativeConstruct() override;
	// переопределяем функцию тика виджета
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override; 

	UFUNCTION()
	// функция обновления очков игрока
	void UpdateScore(const int32 NewScore);
	// функция обновления времени игры
	void UpdateTime();

	void UpdateRecordOnScreen();
};
