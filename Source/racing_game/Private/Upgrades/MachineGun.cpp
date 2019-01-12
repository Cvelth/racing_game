#include "MachineGun.h"
AMachineGun::AMachineGun() {
	PrimaryActorTick.bCanEverTick = false;
}
void AMachineGun::BeginPlay() {
	Super::BeginPlay();	
}
void AMachineGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
