#include "settings.h"

Settings& Settings::GetInstance() {
	static Settings instance;

	return instance;
}

Settings::Settings() {}