#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Globals.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		GROUND,
		WALL,
		ENEMY,
		COIN,
		POTION,
		SHOT,

		MAX
	};

	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);
	bool Intersects(const SDL_Rect& r) const;
	void AddListener(Module* listener);

	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__
