#pragma once
#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"

#include "TrackSpline.generated.h"

class UStaticMesh;
struct FVector;

UCLASS()
class RACING_GAME_API ATrackSpline : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "MeshData")
	UStaticMesh *road_mesh;
	UPROPERTY(EditAnywhere, Category = "MeshData")
	UStaticMesh *left_rail_mesh;
	UPROPERTY(EditAnywhere, Category = "MeshData")
	UStaticMesh *right_rail_mesh;

	bool is_ready;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SplineData")
	USplineComponent *m_spline;

public:
	ATrackSpline();
	void generate(int points, float min_dist, float max_dist);

	virtual void BeginPlay() override;
	void generate_component(std::string name, UStaticMesh *mesh,
							FVector &start_location, FVector &start_tangent,
							FVector &end_location, FVector &end_tangent);

	bool ready() const { return is_ready; }

	UFUNCTION()
	void randomize();
};
