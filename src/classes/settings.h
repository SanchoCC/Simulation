#ifndef SIMULATION_CLASSES_SETTINGS_H_
#define SIMULATION_CLASSES_SETTINGS_H_

class Settings {
public:
	static Settings& GetInstance();
	Settings(Settings const&) = delete;
	void operator=(Settings const&) = delete;

	struct Screen {
		int width = 1366;
		int height = 768;
		float koef_screen = static_cast<float>(width) / height;
		bool fullscreen = false;
		bool vsync = true;
	};
	struct WorldParameters {
		float gravity = -0.98f;
		float restitution = 0.5f;
		float simulation_speed = 1.f;
	};

	Screen screen_;
	WorldParameters world_parameters_;

private:
	Settings();
};

#endif  // SIMULATION_CLASSES_SETTINGS_H_