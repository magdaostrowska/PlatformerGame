#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Module.h"
#include "List.h"
#include <vector>



class Entity;

enum class EntityType
{
	PLAYER,
	ENEMY,
	ITEM,
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
	
	Entity* FindEntity(EntityType type);


	void DestroyEntity(Entity* entity);

public:

	List<Entity*> entities;

};


#endif // !__ENTITY_MANAGER_H__