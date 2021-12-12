#ifndef __WALK_ENEMY_H__
#define __WALK_ENEMY_H__

#include "AnyEnemy.h"

class Walk_Enemy : public AnyEnemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Walk_Enemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;
	void PostUpdate() override;
	void OnCollision(Collider* collider) override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walkLeft, walkRight;
	SDL_Rect walkRect; 

	bool noLeft = false;
	bool noRight = false;

	bool isLeft = false;
	bool isRight = false;

	int speed;
};

#endif // __WALK_ENEMY_H__