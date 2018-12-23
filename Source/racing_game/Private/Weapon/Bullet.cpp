#include "Bullet.h"
#include "Weapon.h"
#include "Car.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> bulletMesh(TEXT("StaticMesh'/Game/Props/Bullet/762x51_bullet_Bullet.762x51_bullet_Bullet'"));
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetStaticMesh(bulletMesh.Object);
	BulletMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	BulletMesh->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BulletMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = BulletMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(150.0f);
	CollisionSphere->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionSphere->SetCollisionProfileName("Projectile");
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	CollisionSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 4000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.1f;

	//Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}
void ABullet::BeginPlay() {
	Super::BeginPlay();
	if (GetOwner()->IsA(AWeapon::StaticClass())) {
		AWeapon* weapon = Cast<AWeapon>(GetOwner());
		damage = weapon->damage;
		BulletMesh->SetRelativeRotation(weapon->GetOwner()->GetActorRotation() + FRotator(0, -90, 0));
	}
}
void ABullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);	
}

void ABullet::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	AActor* weaponOwner = GetOwner();
	AActor* vehicleOwner = weaponOwner->GetOwner();

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics() && (OtherActor != vehicleOwner)) {
		if (OtherActor->IsA(ACar::StaticClass())) {
			ACar* carHit = Cast<ACar>(OtherActor);
			carHit->ApplyDamage(damage);
		}
		OtherComp->AddImpulseAtLocation(GetVelocity() * 10.0f, GetActorLocation());
		Destroy();
	}
}