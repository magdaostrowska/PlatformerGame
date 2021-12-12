#ifndef __ITEM_POTION_H__
#define __ITEM_POTION_H__

#include "AnyItem.h"
//#include "Path.h"

class Item_Potion : public AnyItem
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Item_Potion(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;

	void OnCollision(Collider* collider) override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	//Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation potAnim;
	SDL_Rect potRect;
};

#endif // __ITEM_POTION_H__
