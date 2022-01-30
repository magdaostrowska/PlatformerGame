#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Items.h"
#include "Enemies.h"


EntityManager::EntityManager()
{
	name.Create("EntityManager");
}

EntityManager::~EntityManager()
{}

bool EntityManager::Awake(pugi::xml_node& config)
{
	CreateEntity(EntityType::PLAYER);
	CreateEntity(EntityType::ITEM);

	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.start;

	while ((item != NULL) && (ret == true))
	{
		// L01: DONE 5: Add a new argument to the Awake method to receive a pointer to an xml node.
		// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
		// that can be used to read all variables for that module.
		// Send nullptr if the node does not exist in config.xml
		ret = item->data->Awake(config.child(item->data->name.GetString()));

		item = item->next;
	}
	
	return true;
}

// Called before the first frame
bool EntityManager::Start()
{

	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		//if (item->data->active == true) {
			ret = item->data->Start();
		//}
		item = item->next;
	}
	return ret;
}

bool EntityManager::PreUpdate()
{
	bool ret = true;

	ListItem<Entity*>* item;
	Entity* pModule = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		//if (pModule->active == false) {
		//	continue;
		//}

		ret = item->data->PreUpdate();
	}
	return ret;
}

// Call modules on each loop iteration
bool EntityManager::Update(float dt)
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.start;
	Entity* pModule = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		//if (pModule->active == false) {
		//	continue;
		//}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool EntityManager::PostUpdate()
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pModule = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		//if (pModule->active == false) {
		//	continue;
		//}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		//if (item->data->active == true) {
			ret = item->data->CleanUp();
		//}
		item = item->prev;
	}

	return ret;
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
	Player* retPlayer = new Player();
	Enemies* retEnemy = new Enemies();
	Items* retItem = new Items();

	Entity* retu = nullptr;

	switch (type)
	{
	case EntityType::PLAYER:
		
		retu = retPlayer;
		retu->playerList.push_back(retPlayer);
		
		break;
	case EntityType::ENEMY: 
		
		retu = retEnemy;
		retu->enemyList.push_back(retEnemy);

		break;
	case EntityType::ITEM:
		
		retu = retItem;
		retu->itemList.push_back(retItem);

		break;
	}

	if (retu != nullptr) {
		entities.add(retu);
	}
	

	return retu;
}


Entity* EntityManager::FindEntity(EntityType Etype)
{
	Entity* ret = nullptr;

	for (int i = 0; i < entities.count(); i++) {
		if (entities.At(i)->data->type == Etype) {


			ret = entities.At(i)->data;
		}
	}


	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
}