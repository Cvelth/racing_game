#pragma once
#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "BigGun.generated.h"

UCLASS()
class RACING_GAME_API ABigGun : public AWeaponInterface {
	GENERATED_BODY()	
public:
	ABigGun();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
