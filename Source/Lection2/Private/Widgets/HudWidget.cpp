// Fill out your copyright notice in the Description page of Project Settings.
#include "Widgets/HudWidget.h"
#include "Components/TextBlock.h"
#include "Framework/ArkanoidGameInstance.h"
#include "Framework/ArkanoidGameState.h"
#include "Framework/ArkanoidPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayer())
	{
		PlayerState = GetOwningPlayer()->GetPlayerState<AArkanoidPlayerState>();// получаем ссылку на PlayerState
		if (PlayerState)
			PlayerState->OnPlayerScoreChanged.AddDynamic(this, &UHudWidget::UpdateScore);// подписываемся на делегат изменения очков игрока
	}
	if (GetWorld())
		GameState = Cast<AArkanoidGameState>(GetWorld()->GetGameState());// Заполняем ссылку на GameState

	UpdateRecordOnScreen();
}

void UHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTime();// обновляем время игры каждый тик
}

void UHudWidget::UpdateScore(const int32 NewScore)
{
	if (CurrentScore)
	{
		const FString ScoreString = FString::Printf(TEXT("Счет %03d"), NewScore); // формируем строку с новым счетом
		CurrentScore->SetText(FText::FromString(ScoreString)); // обновляем текст виджета с очками

		if (ShakeAnimation)
		{
			PlayAnimation(ShakeAnimation, // воспроизводим анимацию тряски при получении урона
				0.0f, // начальный кадр
				3, // количество повторов
				EUMGSequencePlayMode::Forward, // режим воспроизведения
				1.0f); // скорость воспроизведения
		}
	}
	UpdateRecordOnScreen();
}

void UHudWidget::UpdateTime()
{
	if (GameTime && GameState)
	{
		int32 Minutes = 0;
		int32 Seconds = 0;
		int32 Milliseconds = 0;
		GameState->GetGameTime(Minutes, Seconds, Milliseconds); // получаем текущее время игры из GameState

		const FString TimeString = FString::Printf(TEXT("Время %02d:%02d:%02d"), Minutes, Seconds, Milliseconds); // формируем строку с временем в формате MM:SS
		GameTime->SetText(FText::FromString(TimeString));// обновляем текст виджета с временем игры
	}
}

void UHudWidget::UpdateRecordOnScreen()
{
	if (LevelRecord)
	{
		if (const auto Gi = Cast<UArkanoidGameInstance>(GetGameInstance()))
		{
			// Получаем текущий рекорд для уровня
			const int32 CurrentRecords = Gi->GetLevelRecords(UGameplayStatics::GetCurrentLevelName(this));
			// Форматируем строку с рекордом уровня
			const FString ScoreText = FString::Printf(TEXT("Рекорд уровня: %03d"), CurrentRecords);
			// Обновляем текст виджета с рекордом уровня
			LevelRecord->SetText(FText::FromString(*ScoreText));
		}
	}
}
