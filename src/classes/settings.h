#ifndef SIMULATION_CLASSES_SETTINGS_H_
#define SIMULATION_CLASSES_SETTINGS_H_

class Settings
{
public:
	static Settings& GetInstance();
	Settings(Settings const&) = delete;
	void operator=(Settings const&) = delete;

	struct Screen {
		int width = 1280;
		int height = 720;
		bool fullscreen = false;
		bool vsync = true;
	};
	struct WorldParameters {
		float gravity = -0.98f;
		float restitution = 1.5f;
	};

	Screen screen_;
	WorldParameters world_parameters_;

private:
	Settings();	
};

#endif //SIMULATION_CLASSES_SETTINGS_H_