#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"


class PhysBody;
class WcObject;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	WcObject* test;
	WcObject* test2;

	WcObject* floor;
	WcObject* LWall;
	WcObject* RWall;

};
