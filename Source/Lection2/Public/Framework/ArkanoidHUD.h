// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArkanoidHUD.generated.h"

class UPauseWidget;
class UHudWidget;
class UWidget;

UCLASS()
class LECTION2_API AArkanoidHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UHudWidget* HudWidget = nullptr;
	UPROPERTY()
	UPauseWidget* PauseWidget = nullptr;

	void ChangeInputMode(UWidget* Widget = nullptr) const;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UHudWidget> HudWidgetClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UPauseWidget> PauseWidgetClass = nullptr;

	void ShowPauseWidget();
	UFUNCTION()
	void HidePauseWidget();
	void ShowGameEndWidget(const bool bWinStatus);
};
