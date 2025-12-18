// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
		// подписываемся на событие нажатия кнопки продолжения игры
		ResumeButton->OnReleased.AddDynamic(this, &UPauseWidget::ResumeGame);
	if (RestartButton)
			RestartButton->OnReleased.AddDynamic(this, &UPauseWidget::RestartGame);
	if (MenuButton)
		MenuButton->OnReleased.AddDynamic(this, &UPauseWidget::BackToMenu);
}

void UPauseWidget::ResumeGame()
{
	OnGameResume.Broadcast();// вызываем событие продолжения игры 
}

void UPauseWidget::RestartGame()
{
	// получаем имя текущего уровня
	const auto LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(this, FName(*LevelName)); // перезапускаем уровень
}

void UPauseWidget::BackToMenu()
{
	// загружаем главное меню карту которая называется "Menu"
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void UPauseWidget::SetWinStatus(const bool bWinStatus)
{
	if (!StatusText)
		return;
	// воспроизводим звук победы или поражения
	UGameplayStatics::PlaySound2D(this, bWinStatus ? WinSound : LooseSound); 
	
	if (ResumeButton)
	{
		ResumeButton->SetIsEnabled(false); // отключаем кнопку продолжения игры
		ResumeButton->SetVisibility(ESlateVisibility::Hidden); // скрываем кнопку продолжения игры
	}

	if (bWinStatus)
	{
		StatusText->SetText(FText::FromString(TEXT("Победа")));
		StatusText->SetColorAndOpacity(FColor::Green);
	}
	else
	{
		StatusText->SetText(FText::FromString(TEXT("Поражение")));
		StatusText->SetColorAndOpacity(FColor::Red);
	}
}
