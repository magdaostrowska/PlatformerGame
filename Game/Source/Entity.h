#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "EntityManager.h"

enum class EntityType
{
	NO_TYPE,
	PLAYER,
	WALK_ENEMY,
	FLY_ENEMY,
	ITEM_COIN,
	ITEM_POTION,
	UNKNOWN
};

class Entity
{
public:

	Entity(EntityType type);
	~Entity();

	virtual void Update();

public:

	EntityType type;
	iPoint position;
};


#endif
