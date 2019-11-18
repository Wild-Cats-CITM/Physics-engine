#ifndef __MODULECOLLIDERS_H__
#define __MODULECOLLIDERS_H__

#define MAX_COLLIDERS 1000

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_FLOOR,
	COLLIDER_PLAYER,
	NO_COLLIDER,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	bool Enabled = true;
};

class ModuleColliders : public Module
{
public:
	ModuleColliders(Application* app, bool start_enabled = true);
	~ModuleColliders();

	bool PreUpdate();
	update_status Update(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
};

#endif // __MODULECOLLIDERS_H__*/
