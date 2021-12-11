#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "App.h"
#include <vector>

enum class Enemy_Type 
{
	WALKING_ENEMY,
	FLYING_ENEMY,
	NO_TYPE,
};

class Enemy;

class ModuleEnemy : public Module {

public:

	ModuleEnemy();
	~ModuleEnemy();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//bool Save(pugi::xml_node& file)const;
	//bool Load(pugi::xml_node& file);

	Enemy* CreateEnemy(Enemy_Type type, int x, int y);

public:

	//ListItem<Enemy*> enemyList;
	std::vector<Enemy*> enemiesList;
	SDL_Texture* enemySprite;
};

#endif // __MODULEENEMY_H__