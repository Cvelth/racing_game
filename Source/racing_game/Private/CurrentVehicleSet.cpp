#include "CurrentVehicleSet.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Brushes/SlateImageBrush.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Misc/Paths.h"
#include "Save.h"
#include <stdexcept>

TSharedRef<SWidget> UCurrentVehicleSet::RebuildWidget() {
	UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
	if (!root)
		WidgetTree->RootWidget = update_root();

	auto ret = Super::RebuildWidget();
	update_widgets();
	return ret;
}
UCanvasPanel* UCurrentVehicleSet::update_root() {
	auto root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
	auto slot = Cast<UCanvasPanelSlot>(root->Slot);
	if (slot)
		slot->SetOffsets(FMargin(100, 100));
	return root;
}
void UCurrentVehicleSet::update_widgets() {
	UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
	if (root && WidgetTree) {
		USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
		Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
		if (!Savefile)
			Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

		int i = 0;
		buttons.Add(item(root, i++, "rpm", "Engine RPM", Savefile->EngineRPM, switch_EEquipementLevel(Savefile->CurrentEngineRPM)));
		buttons.Add(item(root, i++, "gear", "Gear Switch Time", Savefile->GearSwitchTime, switch_EEquipementLevel(Savefile->CurrentGearSwitchTime)));
		buttons.Add(item(root, i++, "mass", "Mass", Savefile->Mass, switch_EEquipementLevel(Savefile->CurrentMass)));
		buttons.Add(item(root, i++, "drag", "Drag Coefficient", Savefile->DragCoefficient, switch_EEquipementLevel(Savefile->CurrentDragCoefficient)));
		buttons.Add(item(root, i++, "steer", "Maximum Steering Angle", Savefile->MaximumSteerAngle, switch_EEquipementLevel(Savefile->CurrentMaximumSteerAngle)));
		buttons.Add(item(root, i++, "tire", "Tire Friction", Savefile->FrictionScale, switch_EEquipementLevel(Savefile->CurrentFrictionScale)));
		buttons.Add(item(root, i++, "stiff", "Lateral Stiffness", Savefile->LatStiffness, switch_EEquipementLevel(Savefile->CurrentLatStiffness)));
		buttons.Add(item(root, i++, "arm", "Armor", Savefile->Armor, switch_EEquipementLevel(Savefile->CurrentArmor)));
		buttons.Add(item(root, i++, "dam", "Damage", Savefile->Damage, switch_EEquipementLevel(Savefile->CurrentDamage)));
		buttons.Add(item(root, i++, "hp", "Maximum Health", Savefile->MaxHealth, switch_EEquipementLevel(Savefile->CurrentMaxHealth)));
	}
}
void UCurrentVehicleSet::update(bool full) {
	UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
	if (full || !root)
		WidgetTree->RootWidget = update_root();
	update_widgets();
}

UCurrentVehicleSet::ButtonHandle UCurrentVehicleSet::button(UPanelWidget *panel, button_type type, FString name, int number, int row) {
	name.AppendInt(number);
	switch (type) {
		case button_type::active: 
			name.AppendChar('a');
			break;
		case button_type::unavailable:
			name.AppendChar('d');
			break;
	}
	auto ret = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(*name));
	auto slot = Cast<UHorizontalBoxSlot>(panel->AddChild(ret));
	slot->SetSize(ESlateSizeRule::Fill);
	slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	slot->SetPadding(FMargin(0));

	switch (type) {
		case button_type::active:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			ret->WidgetStyle.SetNormal(n);
			ret->WidgetStyle.SetHovered(h);
			ret->WidgetStyle.SetPressed(p);
			break;
		}
		case button_type::inactive:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/n_empty.n_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/h_empty.h_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			ret->WidgetStyle.SetNormal(n);
			ret->WidgetStyle.SetHovered(h);
			ret->WidgetStyle.SetPressed(p);
			break;
		}
		case button_type::unavailable:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/n_disabled.n_disabled'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/h_disabled.h_disabled'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			ret->WidgetStyle.SetNormal(n);
			ret->WidgetStyle.SetHovered(h);
			ret->WidgetStyle.SetPressed(p);
			break;
		}
	}
	enable_events(ret, row, number);
	return MakeTuple(ret, slot);
}

void UCurrentVehicleSet::update_button(ButtonHandle b, button_type new_type) {
	switch (new_type) {
		case button_type::active:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			b.Get<0>()->WidgetStyle.SetNormal(n);
			b.Get<0>()->WidgetStyle.SetHovered(h);
			b.Get<0>()->WidgetStyle.SetPressed(p);
			break;
		}
		case button_type::inactive:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/n_empty.n_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/h_empty.h_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			b.Get<0>()->WidgetStyle.SetNormal(n);
			b.Get<0>()->WidgetStyle.SetHovered(h);
			b.Get<0>()->WidgetStyle.SetPressed(p);
			break;
		}
		case button_type::unavailable:
		{
			FSlateImageBrush n(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/n_disabled.n_disabled'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush h(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/h_disabled.h_disabled'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			FSlateImageBrush p(Cast<UObject>(LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'"), NULL, LOAD_None, NULL)), FVector2D(75, 75));
			b.Get<0>()->WidgetStyle.SetNormal(n);
			b.Get<0>()->WidgetStyle.SetHovered(h);
			b.Get<0>()->WidgetStyle.SetPressed(p);
			break;
		}
	}
}

TArray<UCurrentVehicleSet::ButtonHandle> UCurrentVehicleSet::row(UPanelWidget *panel, TArray<bool> availability, int current, FString name, int number) {
	TArray<ButtonHandle> ret;
	if (current == 0)
		ret.Add(button(panel, button_type::active, name, 0, number));
	else
		ret.Add(button(panel, button_type::inactive, name, 0, number));

	for (int i = 1; i < availability.Num() + 1; i++)
		if (current == i)
			ret.Add(button(panel, button_type::active, name, i, number));
		else if (availability[i - 1])
			ret.Add(button(panel, button_type::inactive, name, i, number));
		else
			ret.Add(button(panel, button_type::unavailable, name, i, number));
	return ret;
}

TArray<UCurrentVehicleSet::ButtonHandle> UCurrentVehicleSet::item(UPanelWidget *panel, int index, FString name, FString title, TArray<bool> availability, int current) {
	auto box = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), FName(*name));
	auto box_slot = Cast<UCanvasPanelSlot>(panel->AddChild(box));
	box_slot->SetSize(FVector2D(375, 75));
	box_slot->SetPosition(FVector2D(1920 - 100, index * 80 + 150));

	auto ret = row(box, availability, current, name + TEXT("_"), index);

	auto text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(*(name + TEXT("_text"))));
	auto text_slot = Cast<UCanvasPanelSlot>(panel->AddChild(text));
	text_slot->SetSize(FVector2D(400 - 15, 75));
	text_slot->SetPosition(FVector2D(1920 - 100 - 375, index * 80 + 150 + 25));

	text->SetText(FText::FromString(title + TEXT(": ")));
	text->SetJustification(ETextJustify::Right);

	return ret;
}

void UCurrentVehicleSet::button_event(int row, int item) {
	USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
	Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
	if (!Savefile)
		Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

	if (switch_EEquipementLevel(Savefile->CurrentByID(row)) == item)
		return; //Already selected.

	auto level = make_EEquipementLevel(item);
	auto old = switch_EEquipementLevel(Savefile->CurrentByID(row));
	if (item == 0)
		Savefile->CurrentByID(row) = EEquipementLevel::L0;
	else if (Savefile->AvailabilityByID(row)[item - 1])
		Savefile->CurrentByID(row) = level;
	else
		if (Savefile->Money >= Savefile->Price(level)) {
			Savefile->AvailabilityByID(row)[item - 1] = true;
			Savefile->CurrentByID(row) = level;
			Savefile->Money -= Savefile->Price(level);
		} else {
			NotEnoughMoneyEvent();
			return;
		}
	update_button(buttons[row][old], button_type::inactive);
	update_button(buttons[row][item], button_type::active);
	UGameplayStatics::SaveGameToSlot(Savefile, Savefile->SaveSlotName, Savefile->UserIndex);
	PurchaseEvent();
}

void UCurrentVehicleSet::enable_events(UButton *b, int row, int item) {
	switch (row) {
		case 0:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_0_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_0_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_0_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_0_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_0_4);
			}
		case 1:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_1_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_1_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_1_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_1_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_1_4);
			}
		case 2:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_2_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_2_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_2_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_2_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_2_4);
			}
		case 3:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_3_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_3_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_3_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_3_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_3_4);
			}
		case 4:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_4_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_4_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_4_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_4_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_4_4);
			}
		case 5:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_5_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_5_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_5_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_5_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_5_4);
			}
		case 6:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_6_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_6_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_6_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_6_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_6_4);
			}
		case 7:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_7_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_7_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_7_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_7_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_7_4);
			}
		case 8:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_8_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_8_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_8_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_8_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_8_4);
			}
		case 9:
			switch (item) {
				case 0: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_9_0);
				case 1: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_9_1);
				case 2: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_9_2);
				case 3:	return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_9_3);
				case 4: return b->OnClicked.AddDynamic(this, &UCurrentVehicleSet::button_9_4);
			}
	}
	throw std::runtime_error("Unknown button event");
}

void UCurrentVehicleSet::button_0_0() { button_event(0, 0); }
void UCurrentVehicleSet::button_0_1() { button_event(0, 1); }
void UCurrentVehicleSet::button_0_2() { button_event(0, 2); }
void UCurrentVehicleSet::button_0_3() { button_event(0, 3); }
void UCurrentVehicleSet::button_0_4() { button_event(0, 4); }

void UCurrentVehicleSet::button_1_0() { button_event(1, 0); }
void UCurrentVehicleSet::button_1_1() { button_event(1, 1); }
void UCurrentVehicleSet::button_1_2() { button_event(1, 2); }
void UCurrentVehicleSet::button_1_3() { button_event(1, 3); }
void UCurrentVehicleSet::button_1_4() { button_event(1, 4); }

void UCurrentVehicleSet::button_2_0() { button_event(2, 0); }
void UCurrentVehicleSet::button_2_1() { button_event(2, 1); }
void UCurrentVehicleSet::button_2_2() { button_event(2, 2); }
void UCurrentVehicleSet::button_2_3() { button_event(2, 3); }
void UCurrentVehicleSet::button_2_4() { button_event(2, 4); }

void UCurrentVehicleSet::button_3_0() { button_event(3, 0); }
void UCurrentVehicleSet::button_3_1() { button_event(3, 1); }
void UCurrentVehicleSet::button_3_2() { button_event(3, 2); }
void UCurrentVehicleSet::button_3_3() { button_event(3, 3); }
void UCurrentVehicleSet::button_3_4() { button_event(3, 4); }

void UCurrentVehicleSet::button_4_0() { button_event(4, 0); }
void UCurrentVehicleSet::button_4_1() { button_event(4, 1); }
void UCurrentVehicleSet::button_4_2() { button_event(4, 2); }
void UCurrentVehicleSet::button_4_3() { button_event(4, 3); }
void UCurrentVehicleSet::button_4_4() { button_event(4, 4); }

void UCurrentVehicleSet::button_5_0() { button_event(5, 0); }
void UCurrentVehicleSet::button_5_1() { button_event(5, 1); }
void UCurrentVehicleSet::button_5_2() { button_event(5, 2); }
void UCurrentVehicleSet::button_5_3() { button_event(5, 3); }
void UCurrentVehicleSet::button_5_4() { button_event(5, 4); }

void UCurrentVehicleSet::button_6_0() { button_event(6, 0); }
void UCurrentVehicleSet::button_6_1() { button_event(6, 1); }
void UCurrentVehicleSet::button_6_2() { button_event(6, 2); }
void UCurrentVehicleSet::button_6_3() { button_event(6, 3); }
void UCurrentVehicleSet::button_6_4() { button_event(6, 4); }
								
void UCurrentVehicleSet::button_7_0() { button_event(7, 0); }
void UCurrentVehicleSet::button_7_1() { button_event(7, 1); }
void UCurrentVehicleSet::button_7_2() { button_event(7, 2); }
void UCurrentVehicleSet::button_7_3() { button_event(7, 3); }
void UCurrentVehicleSet::button_7_4() { button_event(7, 4); }

void UCurrentVehicleSet::button_8_0() { button_event(8, 0); }
void UCurrentVehicleSet::button_8_1() { button_event(8, 1); }
void UCurrentVehicleSet::button_8_2() { button_event(8, 2); }
void UCurrentVehicleSet::button_8_3() { button_event(8, 3); }
void UCurrentVehicleSet::button_8_4() { button_event(8, 4); }

void UCurrentVehicleSet::button_9_0() { button_event(9, 0); }
void UCurrentVehicleSet::button_9_1() { button_event(9, 1); }
void UCurrentVehicleSet::button_9_2() { button_event(9, 2); }
void UCurrentVehicleSet::button_9_3() { button_event(9, 3); }
void UCurrentVehicleSet::button_9_4() { button_event(9, 4); }