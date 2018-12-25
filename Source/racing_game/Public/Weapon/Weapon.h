#pragma once
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Weapon.generated.h"

UCLASS()
class RACING_GAME_API AWeapon : public AActor {
	GENERATED_BODY()

private:
	bool bTimerRunning = false;
	
	bool is_active;
	bool left_or_right;

public:	
	AWeapon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void Activate();
	void Deactivate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USphereComponent* LeftGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USphereComponent* RightGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UChildActorComponent* BulletSpawnEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	float reload_time;

	FTimerHandle TimerHandle;

	UFUNCTION(Category = "Behavior")
	virtual void PerformFireWeapon();

protected:
	void TimerCallback();
};
