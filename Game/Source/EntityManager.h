#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include <vector>

class Entity;

enum class EntityType
{
	PLAYER,
	WALK_ENEMY,
	FLY_ENEMY,
	ITEM_COIN,
	ITEM_POTION,
	UNKNOWN
};

class EntityManager : public Module
{
public:
	EntityManager();
	~EntityManager();

	virtual bool Awake(pugi::xml_node& config);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();

	bool Save(pugi::xml_node& file)const;
	bool Load(pugi::xml_node& file);

	Entity* CreateEntity(EntityType type);
	void DestroyEntity(Entity* entity);

public:

	std::vector<Entity*> entites;

};


#endif // !__ENTITYMANAGER_H__