#ifndef __FLY_ENEMY_H__
#define __FLY_ENEMY_H__

#include "Enemies.h"
#include "Entity.h"
#include <iostream>

enum class FlyingEnemyState {
	IDLE,
	FLY_LEFT,
	FLY_RIGHT,
	FLY_UP,
	FLY_DOWN,
	DIE,
};

class Fly_Enemy : public Enemies
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Fly_Enemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	bool Update(float dt) override;
	bool PostUpdate() override;
	void OnCollision(Collider* collider) override;

	void CalculatePath();
	void PathToMove();

	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation flyLeft, flyRight, die;
	SDL_Rect flyRect;

	FlyingEnemyState state;

	bool isLeft = false;
	bool isRight = false;
	bool followsPath;
	int speed;
};

#endif // __WALK_ENEMY_H__
