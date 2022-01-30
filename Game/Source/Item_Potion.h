#ifndef __ITEM_POTION_H__
#define __ITEM_POTION_H__

#include "Entity.h"
#include "App.h"
#include "Collisions.h"
#include "Textures.h"
#include "Items.h"

class Item_Potion : public Items
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Item_Potion(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	bool Update(float dt) override;

	void OnCollision(Collider* collider) override;

private:

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation potAnim;
	SDL_Rect potRect;
};

#endif // __ITEM_POTION_H__

