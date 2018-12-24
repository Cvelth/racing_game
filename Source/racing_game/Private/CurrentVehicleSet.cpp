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

TSharedRef<SWidget> UCurrentVehicleSet::RebuildWidget() {
	UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
	if (!root) {
		root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
		auto slot = Cast<UCanvasPanelSlot>(root->Slot);
		if (slot) {
			//slot->SetAlignment(FVector2D(1, 0));
			//slot->SetAnchors(FAnchors(375, 0, 0, 75));
			slot->SetOffsets(FMargin(100, 100));
		}
	}
	WidgetTree->RootWidget = root;

	auto ret = Super::RebuildWidget();

	if (root && WidgetTree) {

		USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
		Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
		if (!Savefile)
			Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

		auto box = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), TEXT("rpm"));
		auto box_slot = Cast<UCanvasPanelSlot>(root->AddChild(box));
		//box_slot->SetAlignment(FVector2D(1, 0));
		box_slot->SetSize(FVector2D(375, 75));
		box_slot->SetPosition(FVector2D(1920 - 100, 200));

		auto _row = row(box, Savefile->EngineRPM, switch_EEquipementLevel(Savefile->CurrentEngineRPM), TEXT("rpm_"));

		auto text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("rpm_text"));
		auto text_slot = Cast<UCanvasPanelSlot>(root->AddChild(text));
		//text_slot->SetAlignment(FVector2D(1, 0));
		text_slot->SetSize(FVector2D(400 - 15, 75));
		text_slot->SetPosition(FVector2D(1920 - 100 - 375, 200 + 25));

		text->SetText(FText::FromString("Engine RPM: "));
		text->SetJustification(ETextJustify::Right);
	}
	return ret;
}

class UButton* UCurrentVehicleSet::button(UPanelWidget *panel, button_type type, FString name, int number) {
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

	FButtonStyle style;
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
	return ret;
}

TArray<class UButton*> UCurrentVehicleSet::row(UPanelWidget *panel, TArray<bool> availability, int current, FString name) {
	TArray<class UButton*> ret;
	if (current == 0)
		ret.Add(button(panel, button_type::active, name, 0));
	else
		ret.Add(button(panel, button_type::inactive, name, 0));

	for (int i = 1; i < availability.Num() + 1; i++)
		if (current == i)
			ret.Add(button(panel, button_type::active, name, i));
		else if (availability[i - 1])
			ret.Add(button(panel, button_type::inactive, name, i));
		else
			ret.Add(button(panel, button_type::unavailable, name, i));
	return ret;
}
