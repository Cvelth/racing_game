#include "MultiGun.h"
#include "BulletSpawnEffect.h"
AMultiGun::AMultiGun() {
	PrimaryActorTick.bCanEverTick = true;
}
void AMultiGun::BeginPlay() {
	Super::BeginPlay();
	counter = 0;
	reload_time /= switch_EEquipementLevel(level()) + 3;
}
void AMultiGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

float AMultiGun::damage() const {
	return USave::ConvertDamage(level()) * damage_coefficient;
}

#include "BulletInterface.h"
ABulletInterface* AMultiGun::create_next_bullet() {
	auto ret = ABulletInterface::factory_method(EBulletType::small, level(), counter, this);
	if (counter++ >= switch_EEquipementLevel(level()) + 3)
		counter = 0;
	return ret;
}