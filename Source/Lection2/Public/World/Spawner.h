// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UArrowComponent;


UCLASS()
class LECTION2_API ASpawner : public AActor
{
	GENERATED_BODY()
private:
	// Компоненты актора 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneRoot = nullptr;
	// Стрелка направления спавна
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UArrowComponent* ForwardArrow = nullptr;

	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Класс актора для спавна
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	TSubclassOf<AActor> SpawnedClass = nullptr;

	// Функция спавна актора
	UFUNCTION(BlueprintCallable, Category="Spawner")
	void SpawnActor();

	

};
