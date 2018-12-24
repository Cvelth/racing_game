#include "Save.h"
#include <stdexcept>
USave::USave() : USave(EEquipementLevel::L0) {}
USave::USave(EEquipementLevel default_level) {
	//Money = 0;
	Money = 99999; //Temporary measure

	record = 9999;

	CurrentEngineRPM         = default_level;
	CurrentGearSwitchTime	 = default_level;
	CurrentMass				 = default_level;
	CurrentDragCoefficient	 = default_level;
	CurrentMaximumSteerAngle = default_level;
	CurrentFrictionScale	 = default_level;
	CurrentLatStiffness		 = default_level;
	CurrentArmor			 = default_level;
	CurrentDamage			 = default_level;
	CurrentMaxHealth		 = default_level;

	EngineRPM.Init(false, 4);
	GearSwitchTime.Init(false, 4);
	Mass.Init(false, 4);
	DragCoefficient.Init(false, 4);
	MaximumSteerAngle.Init(false, 4);
	FrictionScale.Init(false, 4);
	LatStiffness.Init(false, 4);
	Armor.Init(false, 4);
	Damage.Init(false, 4);
	MaxHealth.Init(false, 4);

	SaveSlotName = TEXT("Savefile");
	UserIndex = 0;
}
float USave::ConvertEngineRPM(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 5000.f;
		case EEquipementLevel::L1:
			return 5500.f;
		case EEquipementLevel::L2:
			return 6000.f;
		case EEquipementLevel::L3:
			return 6500.f;
		case EEquipementLevel::L4:
			return 7000.f;
		case EEquipementLevel::L5:
			return 7500.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertGearSwitchTime(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 1.f;
		case EEquipementLevel::L1:
			return 0.9f;
		case EEquipementLevel::L2:
			return 0.75f;
		case EEquipementLevel::L3:
			return 0.6f;
		case EEquipementLevel::L4:
			return 0.5f;
		case EEquipementLevel::L5:
			return 0.3f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertMass(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 2000.f;
		case EEquipementLevel::L1:
			return 1800.f;
		case EEquipementLevel::L2:
			return 1600.f;
		case EEquipementLevel::L3:
			return 1400.f;
		case EEquipementLevel::L4:
			return 1200.f;
		case EEquipementLevel::L5:
			return 1000.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertDragCoefficient(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 0.5;
		case EEquipementLevel::L1:
			return 0.45f;
		case EEquipementLevel::L2:
			return 0.4f;
		case EEquipementLevel::L3:
			return 0.35f;
		case EEquipementLevel::L4:
			return 0.3f;
		case EEquipementLevel::L5:
			return 0.25f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertMaximumSteerAngle(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 40.f;
		case EEquipementLevel::L1:
			return 45.f;
		case EEquipementLevel::L2:
			return 50.f;
		case EEquipementLevel::L3:
			return 55.f;
		case EEquipementLevel::L4:
			return 60.f;
		case EEquipementLevel::L5:
			return 65.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertFrictionScale(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 5.f;
		case EEquipementLevel::L1:
			return 4.5f;
		case EEquipementLevel::L2:
			return 4.f;
		case EEquipementLevel::L3:
			return 3.5f;
		case EEquipementLevel::L4:
			return 3.f;
		case EEquipementLevel::L5:
			return 2.5f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertLatStiffness(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 16.f;
		case EEquipementLevel::L1:
			return 17.f;
		case EEquipementLevel::L2:
			return 18.f;
		case EEquipementLevel::L3:
			return 19.f;
		case EEquipementLevel::L4:
			return 20.f;
		case EEquipementLevel::L5:
			return 21.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertArmor(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 1.f;
		case EEquipementLevel::L1:
			return 1.5f;
		case EEquipementLevel::L2:
			return 2.f;
		case EEquipementLevel::L3:
			return 2.5f;
		case EEquipementLevel::L4:
			return 3.f;
		case EEquipementLevel::L5:
			return 3.5f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertDamage(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 5.f;
		case EEquipementLevel::L1:
			return 15.f;
		case EEquipementLevel::L2:
			return 30.f;
		case EEquipementLevel::L3:
			return 40.f;
		case EEquipementLevel::L4:
			return 50.f;
		case EEquipementLevel::L5:
			return 80.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::ConvertMaxHealth(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 100.f;
		case EEquipementLevel::L1:
			return 150.f;
		case EEquipementLevel::L2:
			return 200.f;
		case EEquipementLevel::L3:
			return 250.f;
		case EEquipementLevel::L4:
			return 300.f;
		case EEquipementLevel::L5:
			return 500.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}
float USave::Price(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0:
			return 0.f;
		case EEquipementLevel::L1:
			return 300.f;
		case EEquipementLevel::L2:
			return 500.f;
		case EEquipementLevel::L3:
			return 800.f;
		case EEquipementLevel::L4:
			return 1000.f;
		case EEquipementLevel::L5:
			return 1000000.f;
		default:
			throw std::runtime_error("Unsupported enum value.");
	}
}

int switch_EEquipementLevel(EEquipementLevel level) {
	switch (level) {
		case EEquipementLevel::L0: return 0;
		case EEquipementLevel::L1: return 1;
		case EEquipementLevel::L2: return 2;
		case EEquipementLevel::L3: return 3;
		case EEquipementLevel::L4: return 4;
		case EEquipementLevel::L5: return 5;
		default: return -1;
	}
}
EEquipementLevel make_EEquipementLevel(int level) {
	switch (level) {
		case 0: return EEquipementLevel::L0;
		case 1: return EEquipementLevel::L1;
		case 2: return EEquipementLevel::L2;
		case 3: return EEquipementLevel::L3;
		case 4: return EEquipementLevel::L4;
		case 5: return EEquipementLevel::L5;
	}
	throw std::runtime_error("Unknown button event");
}

float USave::GetByID(int id) {
	switch (id) {
		case 0: return GetEngineRPM();
		case 1: return GetGearSwitchTime();
		case 2: return GetMass();
		case 3: return GetDragCoefficient();
		case 4: return GetMaximumSteerAngle();
		case 5: return GetFrictionScale();
		case 6: return GetLatStiffness();
		case 7: return GetArmor();
		case 8: return GetDamage();
		case 9: return GetMaxHealth();
	}
	throw std::runtime_error("Unknown button event");
}
EEquipementLevel& USave::CurrentByID(int id) {
	switch (id) {
		case 0: return CurrentEngineRPM;
		case 1: return CurrentGearSwitchTime;
		case 2: return CurrentMass;
		case 3: return CurrentDragCoefficient;
		case 4: return CurrentMaximumSteerAngle;
		case 5: return CurrentFrictionScale;
		case 6: return CurrentLatStiffness;
		case 7: return CurrentArmor;
		case 8: return CurrentDamage;
		case 9: return CurrentMaxHealth;
	}
	throw std::runtime_error("Unknown button event");
}
TArray<bool>& USave::AvailabilityByID(int id) {
	switch (id) {
		case 0: return EngineRPM;
		case 1: return GearSwitchTime;
		case 2: return Mass;
		case 3: return DragCoefficient;
		case 4: return MaximumSteerAngle;
		case 5: return FrictionScale;
		case 6: return LatStiffness;
		case 7: return Armor;
		case 8: return Damage;
		case 9: return MaxHealth;
	}
	throw std::runtime_error("Unknown button event");
}