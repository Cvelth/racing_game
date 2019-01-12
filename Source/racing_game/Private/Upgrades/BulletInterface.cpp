#include "BulletInterface.h"

ABulletInterface::ABulletInterface() {
	PrimaryActorTick.bCanEverTick = true;
}
void ABulletInterface::BeginPlay() {
	Super::BeginPlay();	
}
void ABulletInterface::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

#include "Car.h"
void ABulletInterface::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	AActor* weaponOwner = GetOwner();
	AActor* vehicleOwner = weaponOwner->GetOwner();

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics() && (OtherActor != vehicleOwner)) {
		if (OtherActor->IsA(ACar::StaticClass())) {
			ACar* carHit = Cast<ACar>(OtherActor);
			carHit->ApplyDamage(damage);
		}
		OtherComp->AddImpulseAtLocation(GetVelocity() * 10.0f, GetActorLocation());
		Destroy();
	}
}

#include <stdexcept>
#include "MultiGunBullet.h"
#include "MachineGunBullet.h"
#include "BigGunBullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
ABulletInterface* ABulletInterface::factory_method(EBulletType type, EEquipementLevel level, size_t counter, AActor* owner) {
	FActorSpawnParameters bulletParams = FActorSpawnParameters();
	bulletParams.Owner = owner;

	FVector position;
	switch (type) {
		case EBulletType::small: {
			auto next_position = AMultiGunBullet::next_position(owner->GetActorLocation(), owner->GetActorRotation(), counter);
			return owner->GetWorld()->SpawnActor<AMultiGunBullet>(AMultiGunBullet::StaticClass(), next_position.first, FRotator(next_position.second.Pitch, next_position.second.Yaw, 0.f), bulletParams);
		}
		case EBulletType::machine_gun: {
			auto next_position = AMachineGunBullet::next_position(owner->GetActorLocation(), owner->GetActorForwardVector(), bool(counter));
			return owner->GetWorld()->SpawnActor<AMachineGunBullet>(AMachineGunBullet::StaticClass(), next_position, FRotator(owner->GetActorRotation().Pitch, owner->GetActorRotation().Yaw, 0.f), bulletParams);
		}
		case EBulletType::big: {
			return owner->GetWorld()->SpawnActor<ABigGunBullet>(ABigGunBullet::StaticClass(), owner->GetActorLocation(), FRotator(owner->GetActorRotation().Pitch, owner->GetActorRotation().Yaw, 0.f), bulletParams);
		}
		default:
			throw std::runtime_error("Unknown enum value.");
	}
}