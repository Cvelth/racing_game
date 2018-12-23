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

	UGameData* data = Cast<UGameData>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (data) {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto car = GetWorld()->SpawnActor<ACar>(sphere->GetComponentLocation() + location_switch(0),
											   FRotator(0, 90, 0), params);
		cars.Emplace(car, data->lap_number);
		for (int i = 0; i < data->AI_car_number; i++) {
			auto car = GetWorld()->SpawnActor<ACarAI>(sphere->GetComponentLocation() + location_switch(i + 1),
													  FRotator(0, 90, 0), params);
			car->set_track(track);
			car->SpawnDefaultController();
			cars.Emplace(car, data->lap_number);
		}
		if (data->time_limit != 0.f)
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACarManager::OutOfTime, data->time_limit, false);

		GetWorld()->GetFirstPlayerController()->UnPossess();
		GetWorld()->GetFirstPlayerController()->Possess(car);
	}
}
void ACarManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ACarManager::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	auto found = cars.FindByPredicate([OtherActor](auto const& tuple) {
		return OtherActor == tuple.Key;
	});
	if (found) {
		found->Value--;
		if (found->Value <= 0)
			Win(found->Key);
	}
}
void ACarManager::OutOfTime() {
	Lose(cars[0].Key);
	//Game over.
}