#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "eulerIntegrator.h"
#include "p2Point.h"
#include "ModuleScene.h"

#include <stdlib.h>
#include <time.h>
#include<iostream>


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

	MonteCarlo = true;
	world->coefAero = 0.5f;
	debug = true;
	MonteCarloCount = 0;
	return true;
}

// All movement logic, set in preupdate, before anything in the loop happens
update_status ModulePhysics::PreUpdate(float dt)
{
	int initposx, initposy, initspeedx, initspeedy, initaccx, initaccy, initforcex, initforcey, speedx, speedy;
	mousex = App->input->GetMouseX(), mousey = App->input->GetMouseY();
	
	//iterate all world objects
	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	while (Objects != NULL)
	{
		initposx = Objects->data->pos.x;
		initposy = Objects->data->pos.y;
		initspeedx = Objects->data->speed.x;
		initspeedy = Objects->data->speed.y;

		initaccx = Objects->data->acc.x;
		initaccy = Objects->data->acc.y;
		initforcex = Objects->data->force.x;
		initforcey = Objects->data->force.y;

		srand(time(NULL));
		if (!MonteCarlo)
		{
			if (Objects->data->isdynamic) {
				
				for (int i = 0; i < 400; i++) 
				{
					if (initposx < mousex)
						{ 
						speedx = Objects->data->speed.x = 0 + rand() % 30;
						}
					else if (initposx > mousex)
						speedx = Objects->data->speed.x = - rand() % 30;

					if (initposy < mousey)
						speedy = Objects->data->speed.y = 0 + rand() % 30;

					else if (initposy > mousey)
						speedy = Objects->data->speed.y = -rand() % 30;

					for (int j = 0; j < 120; j++) {
						Objects->data->updateAcc();
						Objects->data->aerodinamics(world->density, Objects->data->speed.x, Objects->data->speed.y, Objects->data->h, Objects->data->w, world->coefAero, dt);
						Objects->data->eulerIntegrator(dt);
						if (Objects->data->pos.x > mousex && Objects->data->pos.x < mousex +10 && Objects->data->pos.y > mousey&& Objects->data->pos.y < mousey +10) {
							MonteCarlo = true;
						}

					}

					Objects->data->speed.x = initspeedx;
					Objects->data->speed.y = initspeedy;
					Objects->data->pos.x = initposx;
					Objects->data->pos.y = initposy;
					Objects->data->acc.x = initaccx;
					Objects->data->acc.y = initaccy;
					Objects->data->force.x = initforcex;
					Objects->data->force.y = initforcey;
					
					if (MonteCarlo){
						Objects->data->speed.x = speedx;
						Objects->data->speed.y = speedy;

						LOG("velocity X: %i velocity Y: %i ", speedx, -speedy);

						break;
					}
					
				}
				MonteCarloCount++;
			}
		}
		if (MonteCarloCount > 10)
		{
			LOG("Path not found");
			MonteCarloCount = 0;
			MonteCarlo = true;
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

