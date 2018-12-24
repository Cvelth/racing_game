#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Templates/Tuple.h"
#include "CurrentVehicleSet.generated.h"

UCLASS()
class RACING_GAME_API UCurrentVehicleSet : public UUserWidget {
	GENERATED_BODY()

	using ButtonHandle = TTuple<class UButton*, class UHorizontalBoxSlot*>;
protected:
	TArray<TArray<ButtonHandle>> buttons;
public:
	//UCurrentVehicleSet(FObjectInitializer const& oi);
	virtual TSharedRef<SWidget> RebuildWidget() override;
	class UCanvasPanel* update_root();
	void update_widgets();
	void update(bool full = false);

	enum class button_type {
		active, inactive, unavailable
	};
	ButtonHandle button(UPanelWidget *panel, button_type type, FString name, int number, int row);
	TArray<ButtonHandle> row(UPanelWidget *panel, TArray<bool> availability, int current, FString name, int number);
	TArray<ButtonHandle> item(UPanelWidget *panel, int index, FString name, FString title, TArray<bool> availability, int current);

	void button_event(int row, int item);

	void enable_events(UButton *b, int row, int item);

	void update_button(ButtonHandle b, button_type new_type);

	UFUNCTION(BlueprintImplementableEvent)
	void PurchaseEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void NotEnoughMoneyEvent();

	UFUNCTION() void button_0_0();
	UFUNCTION() void button_0_1();
	UFUNCTION() void button_0_2();
	UFUNCTION() void button_0_3();
	UFUNCTION() void button_0_4();

	UFUNCTION() void button_1_0();
	UFUNCTION() void button_1_1();
	UFUNCTION() void button_1_2();
	UFUNCTION() void button_1_3();
	UFUNCTION() void button_1_4();

	UFUNCTION() void button_2_0();
	UFUNCTION() void button_2_1();
	UFUNCTION() void button_2_2();
	UFUNCTION() void button_2_3();
	UFUNCTION() void button_2_4();

	UFUNCTION() void button_3_0();
	UFUNCTION() void button_3_1();
	UFUNCTION() void button_3_2();
	UFUNCTION() void button_3_3();
	UFUNCTION() void button_3_4();

	UFUNCTION() void button_4_0();
	UFUNCTION() void button_4_1();
	UFUNCTION() void button_4_2();
	UFUNCTION() void button_4_3();
	UFUNCTION() void button_4_4();

	UFUNCTION() void button_5_0();
	UFUNCTION() void button_5_1();
	UFUNCTION() void button_5_2();
	UFUNCTION() void button_5_3();
	UFUNCTION() void button_5_4();

	UFUNCTION() void button_6_0();
	UFUNCTION() void button_6_1();
	UFUNCTION() void button_6_2();
	UFUNCTION() void button_6_3();
	UFUNCTION() void button_6_4();

	UFUNCTION() void button_7_0();
	UFUNCTION() void button_7_1();
	UFUNCTION() void button_7_2();
	UFUNCTION() void button_7_3();
	UFUNCTION() void button_7_4();

	UFUNCTION() void button_8_0();
	UFUNCTION() void button_8_1();
	UFUNCTION() void button_8_2();
	UFUNCTION() void button_8_3();
	UFUNCTION() void button_8_4();

	UFUNCTION() void button_9_0();
	UFUNCTION() void button_9_1();
	UFUNCTION() void button_9_2();
	UFUNCTION() void button_9_3();
	UFUNCTION() void button_9_4();
};
