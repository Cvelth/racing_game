#pragma once
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

UCLASS()
class RACING_GAME_API ABullet : public AActor {
	GENERATED_BODY()

public:
	ABullet();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Material")
	UMaterialInstanceDynamic* DynamicInstance;

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
