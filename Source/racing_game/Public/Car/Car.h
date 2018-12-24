#pragma once
#include "WheeledVehicle.h" //PhysXVehicles
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "Weapon.h"
#include "Car.generated.h"

UCLASS()
class RACING_GAME_API ACar : public AWheeledVehicle {
	GENERATED_BODY()

protected:
	float health;
	float max_health;
	bool is_alive;
	float armor;
	float weapon_damage;

	FTimerHandle invincibility_timer;
	bool is_invincible;
public:
	ACar();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User")
	FName name = TEXT("Unnamed");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent *MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UChildActorComponent *Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UChildActorComponent *DestroyedCarEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HealthBarClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidgetComponent *HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget *PauseWidget;

	void MoveForward(float value);
	void MoveRight(float value);
	void HandbrakeOn();
	void HandbrakeOff();
	void StartFire();
	void StopFire();
	void Pause();

	void ApplyDamage(float value);
	void Die();

	UFUNCTION()
	void OnEffectFinished();

	UFUNCTION()
	void OnInvincibilityEnd();

	UFUNCTION()
	void OnHit(AActor *SelfActor, AActor *OtherActor,
			   FVector NormalImpulse, FHitResult const& Hit);

	virtual void virtual_on_hit(AActor *SelfActor, AActor *OtherActor,
								FVector NormalImpulse, FHitResult const& Hit) {}
};