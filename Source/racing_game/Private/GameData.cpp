#include "GameData.h"
UGameData::UGameData() {
	AI_car_number = 0;
	lap_number = 1;
	time_limit = 0.f;
	current_time = 0.f;
}

#include "Save.h"
#include "Kismet/GameplayStatics.h"
void UGameData::Init() {
	/*
	USave* Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
	Savefile = Cast<USave>(UGameplayStatics::LoadGameFromSlot(Savefile->SaveSlotName, Savefile->UserIndex));
	if (!Savefile)
		Savefile = Cast<USave>(UGameplayStatics::CreateSaveGameObject(USave::StaticClass()));
	player_name = Savefile->PlayerName;
	money = Savefile->Money;
	*/
}