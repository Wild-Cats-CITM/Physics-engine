#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "eulerIntegrator.h"
#include "p2Point.h"
#include "ModuleScene.h"
#include "math.h"

//This module is used to call euler and other physics functions, has to be be set by the user

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
//Create a world and set it's density
	world = new WcWorld();
	world->density = AIRDENSITY;
	world->coefAero = 0.5f;
	debug = true;
	return true;
}

// All movement logic, set in preupdate, before anything in the loop happens
update_status ModulePhysics::PreUpdate(float dt)
{
	int initposx, initposy, initspeedx, initspeedy, speedx, speedy;

	//iterate all world objects
	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	while (Objects != NULL)
	{
		initposx = Objects->data->pos.x;
		initposy = Objects->data->pos.y;
		initspeedx = Objects->data->speed.x;
		initspeedy = Objects->data->speed.y;

		for (int i = 0; i < 1000; i++) {
			if (Objects->data->isdynamic) {
				
				speedx = Objects->data->speed.x = rand() % 100;
				speedy = Objects->data->speed.y = rand() % 100;

				for (int j = 0; j < 120; j++) {
					Objects->data->updateAcc();
					Objects->data->aerodinamics(world->density, Objects->data->speed.x, Objects->data->speed.y, Objects->data->h, Objects->data->w, world->coefAero, dt);
					Objects->data->eulerIntegrator(dt);
					if (Objects->data->pos.x == App->input->GetMouseX() && Objects->data->pos.y == App->input->GetMouseY()) {
						
					}

				}
				Objects->data->speed.x = initspeedx;
				Objects->data->speed.y = initspeedy;
				Objects->data->pos.x = initposx;
				Objects->data->pos.y = initposy;
			}
		}
		//If object is dynamic, use all physics functions
		if(Objects->data->isdynamic)
		{
			//Update acceleration
			Objects->data->updateAcc();
			//Modify acceleration with aerodynamics
			Objects->data->aerodinamics(world->density, Objects->data->speed.x, Objects->data->speed.y, Objects->data->h, Objects->data->w, world->coefAero, dt);
			//Modify speed and position with euler
			Objects->data->eulerIntegrator(dt);
			//Now iterate all objects gain to check if there is a collision
			p2List_item<WcObject*>* walls = world->Objects.getFirst();
			while (walls != NULL)
				{
				Objects->data->CheckCollision(Objects->data, walls->data, dt);
				walls = walls->next;
				}
			//Call after collision
			Objects->data->AfterCollision(Objects->data->collider);
			//restart some variables after all collision calculaitons are done
			Objects->data->collided = false;
			Objects->data->initpos = Objects->data->pos;
		
		}
		
		Objects = Objects->next;
	}
	return UPDATE_CONTINUE;
}

//Print world objects after update logic
update_status ModulePhysics::PostUpdate(float dt)
{
	//If draw is active, print the objects
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;
	if (!debug)
		return UPDATE_CONTINUE;
	//iterate all game objects, and print them
	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	while(Objects != NULL)
	{
		if(debug)
		App->renderer->DrawQuad({ (int)Objects->data->pos.x, (int)Objects->data->pos.y, Objects->data->w, Objects->data->h }, 255, 211, 0, 255);
		Objects = Objects->next;
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	if (world != nullptr)
		delete world;
	return true;
}

