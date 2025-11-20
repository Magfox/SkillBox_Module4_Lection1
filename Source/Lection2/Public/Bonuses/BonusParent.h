// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusParent.generated.h"

class APaddle;

UCLASS(Blueprintable, Abstract)// чтобы можно было наследоваться от этого класса
class LECTION2_API ABonusParent : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))	
	UStaticMeshComponent* BonusMesh = nullptr;
	
public:
	
	ABonusParent();

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	void Move(const float DeltaTime);
	//UFUNCTION(BlueprintNativeEvent) Чтобы можно было вызывать в блупринт
	virtual void BonusAction(APaddle* Paddle);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ToolTip = "Направление движения"))
	FVector Direction = FVector(-1.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ToolTip = "Время действия бонуса"))
	float Duration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ToolTip = "Скорость падения бонуса"))
	float Speed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ToolTip = "Сила бонуса"))
	float Value = 0.5f; 

	void InitScale(const FVector& NewScale);
};
