#ifndef __WALKING_ENEMY_H__
#define __WALKING_ENEMY_H__

#include "Enemy.h"
#include "App.h"
#include "Collisions.h"

class WalkingEnemy : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	WalkingEnemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:

	// Enemy animations
	Animation front, back;
};

#endif // __WALKING_ENEMY_H__