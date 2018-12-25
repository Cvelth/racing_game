#include "Weapon.h"
#include "Bullet.h"
#include "BulletSpawnEffect.h"
#include "UObject/ConstructorHelpers.h"

AWeapon::AWeapon() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//ConstructorHelpers::FObjectFinder<UStaticMesh> machineGunMesh(TEXT("StaticMesh'/Game/Mesh/MachineGun/MachineGunMesh.MachineGunMesh'"));
	//WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineGunMesh"));
	//WeaponMesh->SetStaticMesh(machineGunMesh.Object);
	//WeaponMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	//WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RootComponent = WeaponMesh;
	//
	//ConstructorHelpers::FObjectFinder<UStaticMesh> leftGunMesh(TEXT("StaticMesh'/Game/Mesh/MachineGun/MachineGunMesh.MachineGunMesh'"));
	LeftGun = CreateDefaultSubobject<USphereComponent>(TEXT("LeftGun"));
	//LeftGun->SetStaticMesh(leftGunMesh.Object);
	//LeftGun->SetRelativeScale3D(FVector(4.0f, 0.1f, 1.0f));
	LeftGun->SetRelativeLocation(FVector(250.0f, -55.0f, 0.0f));
	LeftGun->SetSphereRadius(50.0f);
	//LeftGun->SetCollisionProfileName(TEXT("OverlapAll"));
	LeftGun->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = LeftGun;
	//LeftGun->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//
	//ConstructorHelpers::FObjectFinder<UStaticMesh> rightGunMesh(TEXT("StaticMesh'/Game/Mesh/MachineGun/MachineGunMesh.MachineGunMesh'"));
	RightGun = CreateDefaultSubobject<USphereComponent>(TEXT("RightGun"));
	//RightGun->SetStaticMesh(rightGunMesh.Object);
	//RightGun->SetRelativeScale3D(FVector(4.0f, 0.1f, 1.0f));
	RightGun->SetRelativeLocation(FVector(250.0f, 55.0f, 0.0f));
	RightGun->SetSphereRadius(50.0f);
	//RightGun->SetCollisionProfileName(TEXT("OverlapAll"));
	RightGun->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightGun->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BulletSpawnEffect = CreateDefaultSubobject<UChildActorComponent>(TEXT("BulletSpawnEffect"));
	BulletSpawnEffect->SetChildActorClass(ABulletSpawnEffect::StaticClass());
	BulletSpawnEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	damage = 20.f;
	reload_time = 0.12f;
}
void AWeapon::BeginPlay() {
	Super::BeginPlay();	
	SetActorTickEnabled(true);
	is_active = false;
	left_or_right = true;
}
void AWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (is_active && !bTimerRunning)
	{
		bTimerRunning = true;
		PerformFireWeapon();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWeapon::TimerCallback, reload_time, false);
	}
}
void AWeapon::Activate() {
	is_active = true;
}
void AWeapon::Deactivate() {
	is_active = false;
}
void AWeapon::TimerCallback() {
	bTimerRunning = false;
}
void AWeapon::Destroyed() {
	Super::Destroyed();
}

void AWeapon::PerformFireWeapon() {
	FVector position = left_or_right ? LeftGun->GetComponentLocation() : RightGun->GetComponentLocation();

	FActorSpawnParameters bulletParams = FActorSpawnParameters();
	bulletParams.Owner = this;
	auto rotation = GetActorRotation();
	GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), position, FRotator(rotation.Pitch, rotation.Yaw, 0.f), bulletParams);

	ABulletSpawnEffect* bulletSpawnEffect = Cast<ABulletSpawnEffect>(BulletSpawnEffect->GetChildActor());
	bulletSpawnEffect->SetActorLocation(position);
	bulletSpawnEffect->ActivateEffect();

	left_or_right = !left_or_right;
}
