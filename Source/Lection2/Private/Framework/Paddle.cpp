// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Paddle.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/Ball.h"

// Спавн шариков жизни на каретке
void APaddle::SpawnBallLives()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green, TEXT("Создаю шар жизни"));
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/Materials/BasicMaterial"));

	if (!Mesh )
	{
		return;
	}
	// Уничтожаем текущие шары и спавним заново
	for (auto BallLive : BallLives)
	{
		BallLive->DestroyComponent();
	}
	BallLives.Empty();
	
	for (int8 i = 0; i < Lives - 1; i++) //Создаем стакик меш компонент шара в количестве жизней
	{
		auto NewMeshComponent = NewObject<UStaticMeshComponent>
		(this, *FString::Printf(TEXT("Lives %d"), i + 1));
		if (NewMeshComponent)
		{
			
			
			NewMeshComponent->SetStaticMesh(Mesh);
			NewMeshComponent->SetMaterial(0, Material);
			NewMeshComponent->SetAbsolute(false, false, true);
			NewMeshComponent->SetWorldScale3D(FVector(0.5f));
			NewMeshComponent->SetupAttachment(StaticMesh);
			NewMeshComponent->RegisterComponent();

			BallLives.Add(NewMeshComponent);
		}
	}
	UpdateBallLivesLocation();
}
// Размещение шариков под кареткой
void APaddle::UpdateBallLivesLocation()
{
	constexpr float BallSpacing = 30.0f; //Расстояния между шариками
	const int8 NumBalls = BallLives.Num(); // Количество шариков

	const float TotalWidth = (NumBalls - 1) * BallSpacing;//Общая ширина расположения шариков
	const float StartOffset = TotalWidth / 2;// Начальное смещение для первого шарика
	//Расставляем ширики семметрично относительно центра
	for (int8 i = 0; i < NumBalls; ++i)
	{
		const float Offset = StartOffset + i * BallSpacing;
		if (IsValid(BallLives[i]))
		{
			BallLives[i]->SetRelativeLocation(FVector(-100, Offset -100, 0));// Не корректный расчет Y расстновки шаров под кареткой
		}
	}
}

APaddle::APaddle()
{
	
	PrimaryActorTick.bCanEverTick = false;
	// Компоненты каретки
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));// Коллайдер каретки для обработки столкновений
	BoxCollider->SetBoxExtent(FVector(25.0f, 50.0f, 25.0f));// Установка размеров коробки коллайдера
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);// Установка реакции коллизии на блокировку для всех каналов
	SetRootComponent(BoxCollider);// Установка коллайдера в корневой компонент
	
	// Центральный Статик меш каретки
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));// Статик меш каретки
	StaticMesh->SetupAttachment(BoxCollider);// Привязка статик меша к коллайдеру

	// Левый Статик меш каретки
	LeftStaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Static Mesh")); // Левый статик меш каретки
	LeftStaticMesh->SetupAttachment(StaticMesh);// Привязка левого статик меша к центральному статик мешу
	LeftStaticMesh->AddRelativeLocation(FVector(0.0f,-50.0f,0.0f));// Смещение левого статик меша влево относительно центрального статик меша
	LeftStaticMesh->SetAbsolute(false, false, true);// Только ротация будет абсолютной

	// Правый Статик меш каретки
	RightStaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Static Mesh"));// Правый статик меш каретки
	RightStaticMesh->SetupAttachment(StaticMesh);// Привязка правого статик меша к центральному статик мешу
	RightStaticMesh->AddRelativeLocation(FVector(0.0f,50.0f,0.0f));// Смещение правого статик меша вправо относительно центрального статик меша
	RightStaticMesh->SetAbsolute(false, false, true);// Только ротация будет абсолютной
	
	// Стрелка направления движения каретки
	Arrow=CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh); // Привязка стрелки к статик мешу
	Arrow->AddRelativeLocation(FVector(150.0f,0.0f,0.0f));// Смещение стрелки вперёд относительно статик меша
	Arrow->SetAbsolute(false, false, true);
}
// вызов при конструировании объекта в редакторе или при спавне в игре
void APaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	SetActorScale3D(DefaultScale); // Установка масштаба каретки
	BoxCollider->SetBoxExtent(FVector(25.0f, 50.0f + 20.0f / DefaultScale.Y, 25.0f)); // Установка размеров коробки коллайдера с учётом масштаба по оси Y
	const FVector TempScale = FVector(GetActorScale().X, GetActorScale().X, GetActorScale().Z); // Временный вектор масштаба для статик мешей
	LeftStaticMesh->SetWorldScale3D(TempScale); // Установка масштаба левого статик меша с учётом масштаба по оси X и Z
	RightStaticMesh->SetWorldScale3D(TempScale);// Установка масштаба правого статик меша с учётом масштаба по оси X и Z


}


void APaddle::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) // Получение контроллера игрока 
	{
		const auto Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()); // Получение подсистемы ввода игрока
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);// Добавление контекста ввода для каретки
		}
	}

	SpawnBall();
	SpawnBallLives();
	UpdateBallLivesLocation();
}


void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Получение расширенного компонента ввода
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &APaddle::ExitGame); // Привязка действия выхода из игры
		EnhancedInputComponent->BindAction(SpawnBallAction, ETriggerEvent::Started, this, &APaddle::StartGame);// Привязка действия спавна мяча
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APaddle::Move);
	}
}

void APaddle::ExitGame()
{
	UGameplayStatics::OpenLevel(GetWorld(),"Menu", true);
}
// Начало игры при нажатии кнопки
void APaddle::StartGame()
{
	if (CurrentBall)
	{
		CurrentBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Отцепляем мяч от каретки
		CurrentBall->SetBallState(EState::moving);
	}
}

void APaddle::Move(const FInputActionValue& Value)
{
	const FVector2D AxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const float CurrentSpeed = AxisVector.X * Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		AddActorWorldOffset(FVector(0.0f, CurrentSpeed, 0.0f), true);
	}
}

void APaddle::SpawnBall()
{
	if (BallClass && !CurrentBall)
	{
		const FVector SpawnLocation = Arrow->GetComponentLocation();// получаем координаты стрелки
		const FRotator SpawnRotation = Arrow->GetComponentRotation(); // Получаем поворот стрелки

		CurrentBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);//Спавним мяч в этих координатах

		if (CurrentBall)
		{
			CurrentBall->SetOwner(this);
			CurrentBall->SetBallState(EState::idle);
			CurrentBall->OnDeadEvent.AddDynamic(this, &APaddle::BallIsDead);
			//CurrentBall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);//Аттачим мяч к коретке
			// Атачим мяч к стрелке этот метод лучше чем выше так как мяч не будет искажаться при изменении размера каретки 
			CurrentBall->AttachToComponent(Arrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void APaddle::BallIsDead()
{
	CurrentBall = nullptr; // Очищаем переменную
	Lives = FMath::Max(Lives-1, 0); //Вычитаем жизнь

	if (Lives)
	{
		SpawnBall();
		BallLives[Lives - 1]->DestroyComponent();// Уничтожаем 1 шарик показывающий сколько жизней
		BallLives.RemoveAt(Lives - 1);// Удаляем из массива
		UpdateBallLivesLocation();//обновляем расположение шариков
	}
}

void APaddle::SetDefaultSize()
{
	SetActorScale3D(DefaultScale);// Ставим дефолт размер каретки
	BoxCollider->SetBoxExtent(FVector(25.0f, 50.0f + 20.0f / DefaultScale.Y, 25.0f));
}

// Бонус изменения размера каретки
void APaddle::BonusChangeSize(const float AdditionalSize, const float BonusTime)
{
	if (AdditionalSize && BonusTime)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerForBonusSize))// Активен ли таймер
		{
			FVector TempScale = GetActorScale3D();
			TempScale.Y = TempScale.Y + TempScale.Y * AdditionalSize; //Рассчет размера каретки
			SetActorScale3D(TempScale);// Ставим новый размер
			BoxCollider->SetBoxExtent(FVector(25.0f, 50.0f + 20.0f / TempScale.Y, 25.0f));
		}
		GetWorld()->GetTimerManager().SetTimer(
			TimerForBonusSize, // Пердаем таймер
			this,// Кто заводит таймер
			&APaddle::SetDefaultSize,// Вызов функции
			BonusTime, // Частота срабатывания
			false);// Нужно ли повторять
	}
}

void APaddle::BonusChangeLife(const int32 Amount)
{
	Lives += Amount;
	SpawnBallLives();
}

void APaddle::BonusChangeBallSpeed(const float Amount)
{
	if (IsValid(CurrentBall))
	{
		CurrentBall->ChangeSpeed(Amount);
	}
}

void APaddle::BonusChangeBallPower(const int32 Amount, const float BonusTime)
{
	if (IsValid(CurrentBall))
	{
		CurrentBall->ChangeBallPower(Amount, BonusTime);
	}
}

void APaddle::BonusSetDefaultPositionBallArrow()
{
	GEngine->AddOnScreenDebugMessage(
			-1,// ключ сообщения (-1 = всегда новое сообщение)
			5.0f,          // сколько секунд показывать
			FColor::Green, // цвет текста
			TEXT("BonusChangeSpawnBall called!"));

	if (IsValid(CurrentBall))
	{
		CurrentBall->SetBallState(EState::idle); // Останавливаем мяч
		CurrentBall->AttachToComponent(Arrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

