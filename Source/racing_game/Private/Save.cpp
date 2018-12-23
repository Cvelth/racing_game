#include "Save.h"
#include <stdexcept>
USave::USave() : USave(EEquipementLevel::L0) {}
USave::USave(EEquipementLevel default_level) {
	Money = 0;

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

	SaveSlotName = TEXT("SaveSlot");
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
			return 6000.f;
		case EEquipementLevel::L5:
			return 6500.f;
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
