#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentVehicleSet.generated.h"

UCLASS()
class RACING_GAME_API UCurrentVehicleSet : public UUserWidget {
	GENERATED_BODY()
	
public:
	//UCurrentVehicleSet(FObjectInitializer const& oi);
	virtual TSharedRef<SWidget> RebuildWidget() override;

	enum class button_type {
		active, inactive, unavailable
	};
	class UButton* button(UPanelWidget *panel, button_type type, FString name, int number);
	TArray<class UButton*> row(UPanelWidget *panel, TArray<bool> availability, int current, FString name);
	TArray<class UButton*> item(UPanelWidget *panel, int index, FString name, FString title, TArray<bool> availability, int current);
};
