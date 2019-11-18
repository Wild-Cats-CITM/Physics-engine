#pragma once

#include "p2List.h"
#include "Globals.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleScene;
class ModulePhysics;
class ModuleColliders;

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleScene* scene_intro;
	ModulePhysics* physics;
	ModuleColliders* collisions;

private:

	p2List<Module*> list_modules;
	
public:

	Application();
	~Application();

	bool Init();
	bool CleanUp();

	void PrepareUpdate();
	update_status Update();
	void FinishUpdate();
	
	float				dt;
private:
	
	void AddModule(Module* mod);
	
	j1PerfTimer			ptimer;
	j1PerfTimer			timewaits;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	uint32				framerate;
	
};

extern Application* App;
