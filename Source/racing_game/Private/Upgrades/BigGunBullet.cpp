#include "BigGunBullet.h"
ABigGunBullet::ABigGunBullet() {
	PrimaryActorTick.bCanEverTick = false;
}
void ABigGunBullet::BeginPlay() {
	Super::BeginPlay();	
}
void ABigGunBullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}