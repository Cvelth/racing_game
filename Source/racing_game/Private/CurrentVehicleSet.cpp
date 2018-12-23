#include "CurrentVehicleSet.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Brushes/SlateImageBrush.h"
#include "Kismet/GameplayStatics.h"
#include "Components/HorizontalBox.h"
#include "Save.h"

void UCurrentVehicleSet::Construct() {
	USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
	Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
	if (!Savefile)
		Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));

	auto _row = row(Savefile->EngineRPM, switch_EEquipementLevel(Savefile->CurrentEngineRPM), TEXT("RPM"));
	auto box = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass(), "RPM");
	for (auto b : _row)
		box->AddChild(b);
	box->SetRenderTranslation(FVector2D(200, 200));
}

class UButton* UCurrentVehicleSet::button(button_type type, FName name, int number) {
	auto temp = FString::FromInt(number);
	name.AppendString(temp);
	switch (type) {
		case button_type::active: 
			temp = "a";
			name.AppendString(temp);
			break;
		case button_type::unavailable:
			temp = "d";
			name.AppendString(temp);
			break;
	}
	auto ret = NewObject<UButton>(this, UButton::StaticClass(), name);

	FButtonStyle style;
	switch (type) {
		case button_type::active:
		{
			FSlateImageBrush n(FName(TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'")), FVector2D(75, 75));
			FSlateImageBrush h(FName(TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'")), FVector2D(75, 75));
			FSlateImageBrush p(FName(TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'")), FVector2D(75, 75));
			style.SetNormal(n);
			style.SetHovered(h);
			style.SetPressed(p);
		}
		case button_type::inactive:
		{
			FSlateImageBrush n(FName(TEXT("Texture2D'/Game/Menu/Images/n_empty.n_empty'")), FVector2D(75, 75));
			FSlateImageBrush h(FName(TEXT("Texture2D'/Game/Menu/Images/h_empty.h_empty'")), FVector2D(75, 75));
			FSlateImageBrush p(FName(TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'")), FVector2D(75, 75));
			style.SetNormal(n);
			style.SetHovered(h);
			style.SetPressed(p);
		}
		case button_type::unavailable:
		{
			FSlateImageBrush n(FName(TEXT("Texture2D'/Game/Menu/Images/n_disabled.n_disabled'")), FVector2D(75, 75));
			FSlateImageBrush h(FName(TEXT("Texture2D'/Game/Menu/Images/h_disabled.h_disabled'")), FVector2D(75, 75));
			FSlateImageBrush p(FName(TEXT("Texture2D'/Game/Menu/Images/p_empty.p_empty'")), FVector2D(75, 75));
			style.SetNormal(n);
			style.SetHovered(h);
			style.SetPressed(p);
		}
	}
	ret->SetStyle(style);
	return ret;
}

TArray<class UButton*> UCurrentVehicleSet::row(TArray<bool> availability, int current, FName name) {
	TArray<class UButton*> ret;
	for (int i = 0; i < availability.Num(); i++) {
		if (current == i)
			ret.Add(button(button_type::active, name, i));
		else if (availability[i])
			ret.Add(button(button_type::inactive, name, i));
		else
			ret.Add(button(button_type::unavailable, name, i));
		//ret.Last()->SetRenderTranslation(FVector2D)
	}
	return ret;
}
