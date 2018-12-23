#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentVehicleSet.generated.h"

UCLASS()
class RACING_GAME_API UCurrentVehicleSet : public UUserWidget {
	GENERATED_BODY()
	
public:
	//UCurrentVehicleSet(FObjectInitializer const& oi);
	void Construct();

	enum class button_type {
		active, inactive, unavailable
	};
	class UButton* button(button_type type, FName name, int number);
	TArray<class UButton*> row(TArray<bool> availability, int current, FName name);
};
