#pragma once

#include "Globals.h"
#include "p2SString.h"

class Application;
struct Collider;

class Module
{
private :
	bool enabled;

public:
	Application* App;

	Module(Application* parent, bool start_enabled = true) : App(parent), enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return enabled;
	}

	void Enable()
	{
		if(enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if(enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt = 0)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt = 0)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt = 0)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void OnCollision(Collider* c1, Collider* c2) {}

public:
	
	p2SString	name;
	bool		active;
	
};