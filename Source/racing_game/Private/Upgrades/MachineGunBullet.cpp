#include "MachineGunBullet.h"
AMachineGunBullet::AMachineGunBullet() {
	PrimaryActorTick.bCanEverTick = false;
}
void AMachineGunBullet::BeginPlay() {
	Super::BeginPlay();	
}
void AMachineGunBullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}