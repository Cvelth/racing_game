#pragma once
#include "CoreMinimal.h"
#include "Car/Car.h"
#include "TrackSpline.h"
#include "Save.h"
#include "CarAI.generated.h"

UCLASS()
class RACING_GAME_API ACarAI : public ACar {
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "TrackData")
	ATrackSpline *track;
	float near_wall;
public:
	ACarAI();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void virtual_on_hit(AActor *SelfActor, AActor *OtherActor,
								FVector NormalImpulse, FHitResult const& Hit) override;

	void set_track(ATrackSpline *_track) { track = _track; }

	static EEquipementLevel current_level;
};
