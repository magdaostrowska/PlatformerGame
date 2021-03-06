#ifndef __ITEM_COIN_H__
#define __ITEM_COIN_H__


#include "Entity.h"
#include "Items.h"

class Item_Coin : public Items
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Item_Coin( int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	bool Update(float dt) override;

	void OnCollision(Collider* collider);

	//Collider* GetCollider() const override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	//Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

	Animation coinAnim;
	SDL_Rect coinRect;
};

#endif // __ITEM_COIN_H__