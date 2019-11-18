#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleColliders.h"
#include "ModuleScene.h"

ModuleColliders::ModuleColliders(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	// Collider floor
	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][NO_COLLIDER] = false;

	// Collider player
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][NO_COLLIDER] = false;
}

// Destructor
ModuleColliders::~ModuleColliders()
{}

bool ModuleColliders::PreUpdate()
{
	bool ret = true;
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];
		if (c1->Enabled == false)
		{
			continue;
		}

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];
			if (c2->Enabled == false)
			{
				continue;
			}
			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return ret;
}

// Called before render is available
update_status ModuleColliders::Update(float dt)
{
	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleColliders::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{

		case COLLIDER_NONE: // purple
			App->renderer->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;

		/*case NO_COLLIDER: // white
			if (App->player->showcolliders == true)
			{
				App->renderer->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			}
			break;

		case COLLIDER_FLOOR: // blue
			if (App->player->showcolliders == true)
			{
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			}
			break;

		case COLLIDER_PLATAFORM: //purple
			if (App->player->showcolliders == true)
			{
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			}
			break;

		case COLLIDER_WALL: //turquesa
			if (App->player->showcolliders == true)
			{
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			}
			break;

		case COLLIDER_PLAYER: // green
			if (App->scene_intro->showcolliders == true)
			{
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			}
			break;*/
		}
	}
}

// Called before quitting
bool ModuleColliders::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleColliders::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (r.x + r.w < rect.x || r.x > rect.x + rect.w || r.y + r.h < rect.y || r.y > rect.y + rect.h) {
		return false;
	}
	else {
		return true;
	}
}