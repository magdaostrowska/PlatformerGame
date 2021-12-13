#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entityManager");
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node& config)
{
	return false;
}

bool EntityManager::Start()
{
	return false;
}

bool EntityManager::PreUpdate()
{
	return false;
}

bool EntityManager::Update(float dt)
{
	return false;
}

bool EntityManager::PostUpdate()
{
	return false;
}

bool EntityManager::CleanUp()
{
	return false;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	return false;
}

bool EntityManager::Load(pugi::xml_node& file)
{
	return false;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* ret = nullptr;

	//switch (type)
	//{
	//case EntityType::PLAYER:
	//	//ret = new Player(); 
	//	break;
	//case EntityType::WALK_ENEMY: 	//	ret = new Walk_Enemy(); 	//	break;	//case EntityType::FLY_ENEMY:	//	ret = new Fly_Enemy();	//	break;
	//case EntityType::ITEM_COIN:	//	ret = new Item_Coin();	//	break;	//case EntityType::ITEM_POTION:	//	ret = new Item_Potion();	//	break;
	//}

	if (ret != nullptr)
		entites.push_back(ret);

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
}
