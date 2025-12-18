// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResume); // делегат продолжения игры

UCLASS()
class LECTION2_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget,  AllowPrivateAccess = "true"))
	UTextBlock* StatusText;
	UPROPERTY(meta = (BindWidget,  AllowPrivateAccess = "true"))
	UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget,  AllowPrivateAccess = "true"))
	UButton* RestartButton;
	UPROPERTY(meta = (BindWidget,  AllowPrivateAccess = "true"))
	UButton* MenuButton;

protected:
	virtual void NativeConstruct() override; // переопределяем функцию конструктора виджета

	UFUNCTION()
	void ResumeGame(); // функция продолжения игры
	UFUNCTION()
	void RestartGame(); // функция перезапуска уровня
	UFUNCTION()
	void BackToMenu(); // функция возврата в главное меню

public:
	UPROPERTY(BlueprintAssignable, Category = "PauseWidget")
	FOnGameResume OnGameResume; // событие продолжения игры
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseWidget")
	USoundBase* WinSound = nullptr; // звук победы
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PauseWidget")
	USoundBase* LooseSound = nullptr; // звук поражения

	
	void SetWinStatus(const bool bWinStatus); // функция установки статуса победы или поражения

};
