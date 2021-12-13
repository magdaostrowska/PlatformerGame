#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "Player.h"
#include "Walk_Enemy.h"
#include "Fly_Enemy.h"
#include "Item_Potion.h"
#include "Item_Coin.h"
#include "List.h"

#include <vector>

class Entity;
enum class EntityType;

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

#endif
