#pragma once
#include "CoreMinimal.h"
#include "BulletInterface.h"
#include "MachineGunBullet.generated.h"

UCLASS()
class RACING_GAME_API AMachineGunBullet : public ABulletInterface {
	GENERATED_BODY()	
public:	
	AMachineGunBullet();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
