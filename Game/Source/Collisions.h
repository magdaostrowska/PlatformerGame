#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#define MAX_COLLIDERS 200

#include "Module.h"
#include "Collider.h"
#include "App.h"
#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

class Collisions : public Module
{
public:

	Collisions();

	virtual ~Collisions();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();
	bool CleanUp();
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);
	void RemoveCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS] = { nullptr };
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];
	bool debug = false;
};

#endif // __MODULE_COLLISIONS_H__
