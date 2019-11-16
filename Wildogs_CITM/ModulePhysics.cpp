#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "eulerIntegrator.h"
#include "p2Point.h"
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
	test = world->AddObject(5.0f,{800,200}, 20, 20);
	//world->AddObject(5.0f, iPoint{ 30,19 }, 100, 20);
	return true;
}

// 
update_status ModulePhysics::PreUpdate(float dt)
{
	//TODO 1 
	p2List_item<WcObject*>* Objects = world->Objects.getFirst();
	while (Objects != NULL)
	{

		Objects->data->updateAcc();
	
		Objects->data->eulerIntegrator(App->dt);
		LOG("%f", Objects->data->acc.y);
		
		Objects = Objects->next;
	}
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
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

