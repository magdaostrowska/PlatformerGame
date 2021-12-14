#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "EntityManager.h"
#include "App.h"
#include "Point.h"
#include "Animation.h"
#include "Title.h"
#include "Render.h"

struct SDL_Texture;

class Entity : public EntityManager
{
public:

	Entity(EntityType type);
	Entity(EntityType type, int x, int y);
	~Entity();

	virtual bool Awake(pugi::xml_node& config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual bool OnCollision() { return true; };

	virtual void Draw();
	virtual void OnCollision(Collider* collider);
	virtual void SetToDelete();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

public:

	EntityType type;
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // !__ENTITY_H__