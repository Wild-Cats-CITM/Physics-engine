#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "eulerIntegrator.h"
#include "ModuleColliders.h"
#include "p2Point.h"
#include "ModuleScene.h"
#include "math.h"



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
	world = new WcWorld();
	//world->AddObject(5.0f, iPoint{ 30,19 }, 100, 20);
	return true;
}

// 
update_status ModulePhysics::PreUpdate(float dt)
{
	//LOG("DT: %f", dt);
	//TODO 1 
	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	while (Objects != NULL)
	{
		if(Objects->data->isdynamic){
		Objects->data->updateAcc();
		Objects->data->eulerIntegrator(dt);

		Objects->data->CheckCollision(Objects->data, App->scene_intro->floor, dt);
	/*	p2List_item<WcObject*>* walls = world->Objects.getFirst();
		while (walls != NULL)
		{
			Objects->data->CheckCollision(Objects->data, walls->data, dt);
			walls = walls->next;
		}
		*/
		}
		
		Objects = Objects->next;
	}
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	
	while(Objects != NULL)
	{
		if(debug)
		App->renderer->DrawQuad({ (int)Objects->data->pos.x, (int)Objects->data->pos.y, Objects->data->w, Objects->data->h }, 255, 211, 0, 255);
		Objects = Objects->next;

	}
	//App->renderer->Blit(NULL, )

	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	return true;
}

