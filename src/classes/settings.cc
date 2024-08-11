#include "settings.h"

Settings& Settings::Get() {
	static Settings instance;

	return instance;
}

Settings::Settings() {}