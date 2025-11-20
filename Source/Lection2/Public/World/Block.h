// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

class ABonusParent;
class ULifeComponent;

UCLASS()
class LECTION2_API ABlock : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr; // Статик меш для блока
	// Компонент жизней блока
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	ULifeComponent* LifeComponent = nullptr;

	TSubclassOf<ABonusParent> BonusClass = nullptr; // Класс бонуса, который может спавниться из блока
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	protected:

	virtual void BeginPlay() override;
	
	// Функция вызова при столкновении с другим компонентом
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other,
		class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
		FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Функция инициализации блока
	void Init(const FVector NewScale, const int32 LifeAmount,
		const TSubclassOf<ABonusParent> NewBonusClass = nullptr);
	// Материалы блока в зависимости от количества жизней
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<UMaterialInterface*> LifeMaterials; 
};
