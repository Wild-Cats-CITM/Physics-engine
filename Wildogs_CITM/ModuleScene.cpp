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
	test = App->physics->world->AddObject(5.0f, { 800,100 }, 20, 20);
	test2 = App->physics->world->AddObject(5.0f, { 700,200 }, 20, 20);
//	App->physics->world->AddObject(5.0f, { 800,50 }, 20, 20);
	

	floor = App->physics->world->AddObject(5.0f, { 0,700 }, 1050, 20);
	floor->isdynamic = false;
	roof = App->physics->world->AddObject(5.0f, { 0,0 }, 1050, 20);
	roof->isdynamic = false;
	LWall = App->physics->world->AddObject(5.0f, { SCREEN_WIDTH-20,0 }, 20, 1050);
	LWall->isdynamic = false;
	RWall = App->physics->world->AddObject(5.0f, { 0, 0 }, 20, 1050);
	RWall->isdynamic = false;
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
	//with W,A,S,D

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		test->force.y = -200* 10* dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		test->force.y = 200* 10 *dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		test->force.x = -200 * 10 *dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		test->force.x = 200 * 10 *dt;
	}

	//With 

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		test->force.y = -6000 * 10 *dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		test->force.y = 6000 * 10 * dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		test->force.x = -7000 * 10 * dt;
		test->force.y = -5000 * 10 * dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		test->force.x = 7000 * 10 * dt;
		test->force.y = -5000 * 10 * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		test->pos.y = 344;
		test->pos.x = 512;
		test->acc.x = 0;
		test->acc.y = 0;
		test->force.x = 0;
		test->force.y = 0;
		test->speed.x = 0;
		test->speed.y = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->physics->world->density = AIRDENSITY;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->physics->world->density = WATERDENSITY;
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->physics->world->density = LAVADENSITY;
	}

	return UPDATE_CONTINUE;
}
