#pragma once
#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "save.h"
#include "MultiGun.generated.h"

UCLASS()
class RACING_GAME_API AMultiGun : public AWeaponInterface {
	GENERATED_BODY()
protected:
	size_t counter;
public:
	AMultiGun();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float const damage_coefficient = 0.4f;

	virtual class ABulletInterface* create_next_bullet() override;
	virtual float damage() const;
};
