#include "BigGun.h"
#include "BulletSpawnEffect.h"
ABigGun::ABigGun() {
	PrimaryActorTick.bCanEverTick = true;
}
void ABigGun::BeginPlay() {
	Super::BeginPlay();
	reload_time = .72f;
}
void ABigGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

float ABigGun::damage() const {
	return USave::ConvertDamage(level()) * damage_coefficient;
}

#include "BulletInterface.h"
ABulletInterface* ABigGun::create_next_bullet() {
	auto ret = ABulletInterface::factory_method(EBulletType::big, level(), 0, this);
	return ret;
}