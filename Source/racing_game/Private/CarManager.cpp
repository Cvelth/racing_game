#include "CarManager.h"
#include "GameData.h"
#include "Engine/World.h"
#include "CarAI.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Trees.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"

ACarManager::ACarManager() {
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	sphere->SetSphereRadius(1000.0f);
	sphere->SetCollisionProfileName("Start");
	sphere->OnComponentBeginOverlap.AddDynamic(this, &ACarManager::OnOverlap);
	sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}
FVector location_switch(int index) {
	switch (index) {
		case 0: return FVector(-200, +000, 0);
		case 1: return FVector(+200, +900, 0);
		case 2: return FVector(-200, +600, 0);
		case 3: return FVector(+200, +300, 0);
		case 4: return FVector(+200, -300, 0);
		case 5: return FVector(-200, -600, 0);
		default: return FVector(0, 0, 0);
	}
}
void ACarManager::BeginPlay() {
	Super::BeginPlay();
	track->randomize();
	trees->randomize();

	m_data = Cast<UGameData>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (m_data) {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto car = GetWorld()->SpawnActor<ACar>(sphere->GetComponentLocation() + location_switch(0),
											   FRotator(0, 90, 0), params);
		car->PauseWidget = PauseWidget;
		cars.Emplace(car, m_data->lap_number);
		for (int i = 0; i < m_data->AI_car_number; i++) {
			auto car = GetWorld()->SpawnActor<ACarAI>(sphere->GetComponentLocation() + location_switch(i + 1),
													  FRotator(0, 90, 0), params);
			car->set_track(track);
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
	start_time = std::chrono::high_resolution_clock::now();
}
void ACarManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (m_data) {
		m_data->current_time = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
}

void ACarManager::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	auto found = cars.FindByPredicate([OtherActor](auto const& tuple) {
		return OtherActor == tuple.Key;
	});
	if (found) {
		found->Get<1>()--;
		if (found->Get<1>() <= 0)
			Win(found->Get<0>());
		if (found->Get<0>() == cars[0].Get<0>() && m_data)
			m_data->laps_left = found->Get<1>();
	}
}
void ACarManager::OutOfTime() {
	Lose();
}

void ACarManager::Win(ACar *car) {
	if (car == cars[0].Get<0>()) {

		WinEvent();
	}
	else
		Lose();
}
void ACarManager::Lose() {
	LoseEvent();
}