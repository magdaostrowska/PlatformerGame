#include "ModuleEnemy.h"
#include "WalkingEnemy.h"

ModuleEnemy::ModuleEnemy()
{
	name.Create("ModuleEnemy");
	//enemyList = nullptr;
}

ModuleEnemy::~ModuleEnemy()
{
}

bool ModuleEnemy::Awake(pugi::xml_node& config)
{
	bool ret = true;
	return ret;
}

bool ModuleEnemy::Start()
{
	bool ret = true;
	return ret;
}

bool ModuleEnemy::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool ModuleEnemy::Update(float dt)
{
	bool ret = true;
	for (int i = 0; i < enemiesList.size(); i++)
	{
		enemiesList[i]->Update(dt);
	}
	return ret;
}

bool ModuleEnemy::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool ModuleEnemy::CleanUp()
{
	bool ret = true;
	return ret;
}

Enemy* ModuleEnemy::CreateEnemy(Enemy_Type type, int x, int y)
{
	Enemy* ret = nullptr;
	switch (type)
	{
	case Enemy_Type::WALKING_ENEMY:
		ret = new WalkingEnemy();
		ret->position.x = x;
		ret->position.y = y;
		ret->Awake(app->GetConfig().child("walkingEnemy"));
		ret->Start();
		break;
	case Enemy_Type::FLYING_ENEMY:
		break;
	case Enemy_Type::NO_TYPE:
		break;
	default:
		break;
	}
	enemiesList.push_back(ret);
	return ret;
}