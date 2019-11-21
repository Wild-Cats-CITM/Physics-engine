#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "eulerIntegrator.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	test = App->physics->world->AddObject(5.0f, { 800,200 }, 20, 20);
	floor = App->physics->world->AddObject(5.0f, { 0,700 }, 1050, 20);
	floor->isdynamic = false;
	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) 
	{
		test->force.y = -200;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		test->force.y = 200;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{

		test->force.x = -200;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		test->force.x = 200;
	}

	
	return UPDATE_CONTINUE;
}
