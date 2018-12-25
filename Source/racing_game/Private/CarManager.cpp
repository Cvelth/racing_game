#include "CarManager.h"
#include "GameData.h"
#include "Engine/World.h"
#include "CarAI.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Trees.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/OutputDeviceDebug.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TrackSpline.h"

ACarManager::ACarManager() {
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	sphere->SetSphereRadius(1000.0f);
	sphere->SetCollisionProfileName("Start");
	sphere->OnComponentBeginOverlap.AddDynamic(this, &ACarManager::OnOverlap);
	sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	static ConstructorHelpers::FClassFinder<UUserWidget> HUD_Finder(TEXT("WidgetBlueprint'/Game/Menu/HUDWidget.HUDWidget_C'"));
	HUD = CreateWidget<UUserWidget>(GetWorld(), HUD_Finder.Class);
}
FVector location_switch(int index) {
	switch (index) {
		case 0: return FVector(-350, +000, 0);
		case 1: return FVector(+350, +900, 0);
		case 2: return FVector(-350, +600, 0);
		case 3: return FVector(+350, +300, 0);
		case 4: return FVector(+350, -300, 0);
		case 5: return FVector(-350, -600, 0);
		default: return FVector(0, 0, 0);
	}
}
void ACarManager::BeginPlay() {
	Super::BeginPlay();
	track->generate();
	trees->generate();

	m_data = Cast<UGameData>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (m_data) {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto car = GetWorld()->SpawnActor<ACar>(sphere->GetComponentLocation() + location_switch(0),
											   FRotator(0, 90, 0), params); 
		car->PauseWidget = PauseWidget;
		car->track = track;
		car->EnableManagement(this);
		cars.Emplace(car, m_data->lap_number);
		for (int i = 0; i < m_data->AI_car_number; i++) {
			auto car = GetWorld()->SpawnActor<ACarAI>(sphere->GetComponentLocation() + location_switch(i + 1),
													  FRotator(0, 90, 0), params);
			car->name = *(TEXT("AI_") + FString::FromInt(i));
			car->track = track;
			car->EnableManagement(this);
			car->SpawnDefaultController();
			cars.Emplace(car, m_data->lap_number);
		}
		if (m_data->time_limit != 0.f)
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACarManager::OutOfTime, m_data->time_limit, false);

		GetWorld()->GetFirstPlayerController()->UnPossess();
		GetWorld()->GetFirstPlayerController()->Possess(car);
	
		m_data->current_time = 0;
		m_data->laps_left = m_data->lap_number;
	}

	HUD->AddToViewport();
	start_time = std::chrono::high_resolution_clock::now();
}
void ACarManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (m_data) {
		m_data->current_time = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
	USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
	Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
	if (!Savefile)
		Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

	const FString command = FString::Printf(TEXT("update %f %f %d %d %f"), 
											m_data->current_time / 1000, 
											Savefile->record / 1000, 
											m_data->laps_left,
											cars[0].Get<0>()->get_gear(),
											cars[0].Get<0>()->get_speed());
	static FOutputDeviceDebug temp;
	HUD->CallFunctionByNameWithArguments(*command, temp, this, true);
}

void ACarManager::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (m_data->type != RaceType::Survival) {
		auto found = cars.FindByPredicate([OtherActor](auto const& tuple) {
			return OtherActor == tuple.Key;
		});
		if (found) {
			found->Get<1>()--;
			if (found->Get<1>() == 0)
				if (found->Get<0>() == cars[0].Get<0>())
					Win(found->Get<0>());
				else
					Lose();
			if (found->Get<0>() == cars[0].Get<0>() && m_data)
				m_data->laps_left = found->Get<1>();
		}
	}
}
void ACarManager::OutOfTime() {
	if (m_data->type == RaceType::Time)
		Lose();
}

void ACarManager::Win(ACar *car) {
	auto finish_time = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start_time).count();
	if (car == cars[0].Get<0>()) {
		USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
		Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
		if (!Savefile)
			Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

		Savefile->Money += 400;
		if (finish_time < Savefile->record) {
			Savefile->record = finish_time;
			Savefile->Money += 200;
		}

		UGameplayStatics::SaveGameToSlot(Savefile, Savefile->SaveSlotName, Savefile->UserIndex);
		HUD->RemoveFromParent();
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenuMap");
		WinEvent();
	}
	else
		Lose();
}
void ACarManager::Lose() {
	HUD->RemoveFromParent();
	LoseEvent();
}
void ACarManager::has_died(ACar *car) {
	if (car == cars[0].Get<0>())
		Lose();
	else if (m_data->type == RaceType::Survival || m_data->type == RaceType::Duel) {
		auto found = cars.FindByPredicate([car](auto const& tuple) {
			return car == tuple.Key;
		});
		if (found) {
			//cars.Remove(*found);
			if (cars.Num() <= 1)
				Win(cars[0].Get<0>());
		}
	}
}