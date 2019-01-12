#pragma once
#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "MachineGun.generated.h"

UCLASS()
class RACING_GAME_API AMachineGun : public AWeaponInterface {
	GENERATED_BODY()	
public:	
	AMachineGun();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
