#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
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

	//Adding some objects and example, and test object, which we will use later on
	App->renderer->camera.x = App->renderer->camera.y = 0;
	test = App->physics->world->AddObject(5.0f, { 800,100 }, 20, 20);
	floor = App->physics->world->AddObject(20.0f, { 0,700 }, 1050, 20);
	floor->isdynamic = false;
	roof = App->physics->world->AddObject(20.0f, { 0,0 }, 1050, 20);
	roof->isdynamic = false;
	LWall = App->physics->world->AddObject(20.0f, { SCREEN_WIDTH-20,0 }, 20, 1050);
	LWall->isdynamic = false;
	RWall = App->physics->world->AddObject(20.0f, { 0, 0 }, 20, 1050);
	RWall->isdynamic = false;
	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleScene::Update(float dt)
{
	//Add force continuosly to test object with W,A,S,D

	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT)
	{
		if (App->physics->mousex > 20 && App->physics->mousex < 1005 && App->physics->mousey > 19 && App->physics->mousey < 700)
		App->physics->MonteCarlo = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		test->AddForce({0,-200});

	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		test->AddForce({ 0, 200 });
		
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		test->AddForce({-200, 0 });

	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		test->AddForce({ 200, 0 });
	}

	//Add a force only once to test with arrow keys 
	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		test->AddForce({ 0,-3500 });
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		test->AddForce({ 0, 3500 });
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		test->AddForce({ -3500, -2500 });
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		test->AddForce({ 3500, -2500 });
	}

	//Reset test position
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

	//Change the density of the "Fluid" of the simulation
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

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		App->physics->world->density = SPACEDENSITY;
	}

	return UPDATE_CONTINUE;
}
