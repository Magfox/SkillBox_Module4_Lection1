// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PlayingBoard.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Bonuses/BonusParent.h"
#include "DSP/MidiNoteQuantizer.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Block.h"


void APlayingBoard::CreatePreviewComponents()
{
	if (GridSizeX <= 0 || GridSizeY <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Размер сетки должен быть положительным числом")); // Логирование ошибки, если размер сетки равен нулю
		return;
	}

	const float BlockWidth = BlockScale.X * 100.0f; // Ширина блока с учётом масштаба
	const float BlockHeight = BlockScale.Y * 100.0f; // Высота блока с учётом масштаба
	const float BlockDepth = BlockScale.Z * 100.0f; // Глубина блока с учётом масштаба

	const float TotalWidth = GridSizeX * BlockWidth + (GridSizeX - 1) * SpacingX; // Общая ширина доски
	const float TotalHeight = GridSizeY * BlockHeight + (GridSizeY - 1) * SpacingY; // Общая высота доски
	// Смещение для центрирования доски
	const FVector CenterOffset = FVector((TotalWidth - BlockWidth) / 2.0f, (TotalHeight - BlockHeight) / 2.0f, 0.0f);
	// Получаем текущую трансформацию объекта (позиция и поворот)
	const FTransform ActorTransform = GetActorTransform();

	for (int32 x = 0; x < GridSizeX; x++) // Проходим по оси X
	{
		for (int32 y = 0; y < GridSizeY; y++) // Проходим по оси Y
		{
			if (PreviewMesh) // Если меш для превью установлен
			{
				// Вычисляем позицию блока с учетом отступов от края
				const float XOffset = x * (BlockWidth + SpacingX);
				const float YOffset = y * (BlockHeight + SpacingY);
				const FVector PreviewLocation = FVector(XOffset, YOffset, 0.0f) - CenterOffset; // Позиция превью блока до трансформации
				// Преобразуем локальную позицию в мировую с учетом позиции и поворота актора
				const FVector WorldPreviewLocation = ActorTransform.TransformPosition(PreviewLocation);

				// проверяем есть ли что то на месте превью компонента
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this); // Игнорируем сам актор доски

				// Создаем превью компонент
				const FVector BoxExtents = FVector(BlockWidth * 0.5f, BlockHeight * 0.5f, BlockDepth * 0.5f); 
				// Полуразмеры коробки для проверки коллизий
				const bool bIsBlocked = GetWorld()->OverlapBlockingTestByChannel( // Проверка на коллизию в месте превью
					WorldPreviewLocation, ActorTransform.GetRotation(), // Ротация актора
					ECC_Visibility, // Канал коллизии
					FCollisionShape::MakeBox(BoxExtents),CollisionParams); // Форма коллизии - коробка
				
				if (bIsBlocked) // Если место занято
					{ 
						DrawDebugBox(GetWorld(), WorldPreviewLocation, BoxExtents, ActorTransform.GetRotation(), 
							FColor::Red, false, 10.0f); // Рисуем красную коробку для отладки
						continue;
					}
				else
				{
					// Создаем превью меш компонент и настраиваем его
					UStaticMeshComponent* PreviewMeshComponent = NewObject<UStaticMeshComponent>(this); // Создание нового компонента
					PreviewMeshComponent->SetStaticMesh(PreviewMesh); // Установка меша для превью
					PreviewMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);// Привязка к корневому компоненту доски
					PreviewMeshComponent->SetRelativeScale3D(BlockScale);// Установка масштаба превью
					PreviewMeshComponent->SetRelativeLocation(PreviewLocation);// Установка локальной позиции превью
					PreviewMeshComponent->RegisterComponent();// Регистрация компонента в мире
					PreviewComponents.Add(PreviewMeshComponent); // Добавление компонента в массив превью компонентов
				}
			}
		}
	}
	
	
}

void APlayingBoard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ClearPreviewComponents(); // Очистка предыдущих превью компонентов
	CreatePreviewComponents(); // Создание превью компонентов при конструировании объекта
}


void APlayingBoard::ClearPreviewComponents()
{
	for (UStaticMeshComponent* PreviewComponent : PreviewComponents) // Проходим по всем превью компонентам
	{
		if (PreviewComponent)// Проверка валидности компонента
		{
			PreviewComponent->DestroyComponent(); // Уничтожение компонента
		}
	}
	PreviewComponents.Empty();// Очистка массива превью компонентов
}

void APlayingBoard::SpawnBlockActors()
{
	for (UStaticMeshComponent* PreviewComponent : PreviewComponents)
	{
		if (PreviewComponent)
		{
			const FTransform SpawnTransform = PreviewComponent->GetComponentTransform(); // Получение трансформации превью компонента
			// Если класс блока для спавна установлен и мир валиден
			if (auto CurrentBlock = GetWorld()->SpawnActor<ABlock>(BlockClassForSpawn, SpawnTransform))
			{
				// Определение количества жизней блока на основе сложности игры
				const int32 Life = UKismetMathLibrary::RandomBoolWithWeight(GameDifficulty) ? 2 : 1;
				// определяем будет ли куб содержать бонус на основе BonusChance
				const auto BonusClass = UKismetMathLibrary::RandomBoolWithWeight(BonusChance)
				? GetBonusClass() : nullptr;
				CurrentBlock->Init(BlockScale, Life, BonusClass); // Инициализация блока
				// Привязка блока к корневому компоненту доски
				CurrentBlock->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepWorldTransform);
				CurrentBlock->OnDestroyed.AddDynamic(this, &APlayingBoard::OnBlockDestroyed); // Подписка на событие уничтожения блока
				BlockActors.Add(CurrentBlock); // Добавление блока в массив блоков доски
			}
		}
	}
}

void APlayingBoard::OnBlockDestroyed(AActor* DestroyedBlock)
{
	BlockActors.Remove(Cast<ABlock>(DestroyedBlock));// Удаление уничтоженного блока из массива блоков доски
}

APlayingBoard::APlayingBoard()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));// Создание корневого компонента сцены
	SetRootComponent(SceneRoot); // Установка корневого компонента сцены

}

void APlayingBoard::BeginPlay()
{
	Super::BeginPlay();
	// Вызов функций при старте игры
	SpawnBlockActors();
	ClearPreviewComponents();
}

TSubclassOf<ABonusParent> APlayingBoard::GetBonusClass()
{
	if (BonusTypeByChances.Num() == 0 || !BonusTypeByChances[0].BonusClass) // Если массив настроек шанса пуст
	{
		return nullptr; // Возвращаем null
	}

	int32 TotalWeight = 0;
	for (const auto& CurrentBonus : BonusTypeByChances) // Вычисление общей суммы весов
	{
		TotalWeight += CurrentBonus.DropChance * 100; // Умножение на 100 для работы с целыми числами
	}
	// Генерация случайного веса в диапазоне от 0 до TotalWeight
	int32 RandomWeight = FMath::RandHelper(TotalWeight);
	for (const auto& CurrentBonus : BonusTypeByChances)
	{
		if (RandomWeight > CurrentBonus.DropChance * 100) // Проверка, если случайный вес больше веса текущего бонуса
		{
			RandomWeight -= CurrentBonus.DropChance * 100; // Вычитаем вес текущего бонуса из случайного веса
		}
		else
		{
			return CurrentBonus.BonusClass; // Возвращаем класс бонуса, если условие выполнено
		}
	}
	return nullptr; // Возвращаем null, если ни один бонус не был выбран
}

void APlayingBoard::BonusDestroyCubes(const int32 Amount)
{
	if (Amount <= 0)// Если больше и равно 0 количество кубов
	{
		return;
	}
	// Определяем что количество блоков которые хотим уничтожить не выходит за количество живых блоков
	const int32 NumToDestroy = FMath::Min(Amount, BlockActors.Num());
	for (int32 i = 0; i < NumToDestroy; i++)
	{
		const int32 RandomIndex = FMath::RandHelper(BlockActors.Num());
		if (BlockActors.IsValidIndex(RandomIndex))
		{
			BlockActors[RandomIndex]->Destroy();
		}
	}
}

