#include "BigGun.h"
ABigGun::ABigGun() {
	PrimaryActorTick.bCanEverTick = false;
}
void ABigGun::BeginPlay() {
	Super::BeginPlay();
}
void ABigGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
