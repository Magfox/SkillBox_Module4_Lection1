// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyKillZone.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class LECTION2_API AMyKillZone : public AActor
{
	GENERATED_BODY()
	
private:
	// Компоненты актора 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneRoot = nullptr;
	// Стрелка направления спавна
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	UArrowComponent* ForwardArrow = nullptr;
	// Коллизия зоны убийства
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	UBoxComponent* KillBox = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AMyKillZone();
	
protected:
	// Функция вызова при начале перекрытия актора
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
	

