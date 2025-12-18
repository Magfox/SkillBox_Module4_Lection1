// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidPC.h"

#include "Framework/ArkanoidHUD.h"

void AArkanoidPC::ExitButtonPressed()
{
	const auto CurrentHUD = Cast<AArkanoidHUD>(GetHUD());
	if (!CurrentHUD)
	return;

	if (IsPaused())
	{
		SetPause(false);
		CurrentHUD->HidePauseWidget();
	}
	else
	{
		SetPause(true);
		CurrentHUD->ShowPauseWidget();
	}
}

void AArkanoidPC::ShowGameEndMenu(const bool bWinStatus)
{
	const auto CurrentHUD = Cast<AArkanoidHUD>(GetHUD());
	if (CurrentHUD)
		CurrentHUD->ShowGameEndWidget(bWinStatus);
	SetPause(true);
}
