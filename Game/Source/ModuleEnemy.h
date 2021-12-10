#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"

enum class Enemy_Type 
{
	WALKING_ENEMY,
	FLYING_ENEMY,
	NO_TYPE,
};

class ModuleEnemy : public Module {

public:

	ModuleEnemy();
	~ModuleEnemy();

	virtual bool Awake(pugi::xml_node& config);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();

	bool Save(pugi::xml_node& file)const;
	bool Load(pugi::xml_node& file);

	//j1Entity* CreateEntity(entityTypes type, int position_x, int position_y);
	//void DestroyEntity(j1Entity* entity);
	void DestroyAllEntities();

public:

	//p2List<j1Entity*> entitiesList;
};

#endif // __MODULEENEMY_H__