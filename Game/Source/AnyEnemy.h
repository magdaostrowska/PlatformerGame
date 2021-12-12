#ifndef __ANY_ENEMY_H__
#define __ANY_ENEMY_H__

#include "Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class AnyEnemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	AnyEnemy(int x, int y);

	// Destructor
	virtual ~AnyEnemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update(float dt);

	virtual void PostUpdate();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture_left = nullptr;
	SDL_Texture* texture_right = nullptr;
	SDL_Texture* texture_die = nullptr;

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
	int dir;

	int lifes;

	int hitCountdown = 0;
	int	hitMaxCountdown = 60;

	
};

#endif // __ANY_ENEMY_H__
