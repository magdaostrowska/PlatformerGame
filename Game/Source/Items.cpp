#include "Items.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Title.h"
#include "Item_Coin.h"
#include "Item_Potion.h"

Items::Items() : Entity(EntityType::ITEM)
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
		itemsL[i] = nullptr;
}

Items::~Items()
{

}

bool Items::Start()
{
	//texture = app->tex->Load("Assets/textures/items/coin.png");
	//itemDestroyedFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}


bool Items::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemsL[i] != nullptr && itemsL[i]->pendingToDelete)
		{
			delete itemsL[i];
			itemsL[i] = nullptr;
		}
	}

	return true;
}

bool Items::Update(float dt)
{
	HandleItemsSpawn();

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{

		if (itemsL[i] != nullptr) {

		
			itemsL[i]->Update(dt);

		}

		if (itemsL[0] == nullptr && app->titleScreen->inTitle ==0) {
			int r = 0;
		}
			
	}

	HandleItemsDespawn();

	return true;
}

bool Items::PostUpdate()
{

	int w = 0;

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{

		if (itemsL[i] != nullptr) {
			//position.x = items[i]->position.x;
			//position.y = items[i]->position.y;

			//itemsL[i]->position.x = 40;
			//itemsL[i]->position.y = 40;
			//itemsL[i]->collider = itemsL[i]->GetCollider();
			if (itemsL[i]->collider == nullptr) {
				int u = 8;
			}
			else {
				int e =7;
			}
			itemsL[i]->Draw();
		}

		w++;

		if (itemsL[0] == nullptr) {
			int a = 5;
		}
			
	}

	

	return true;
}

// Called before quitting
bool Items::CleanUp()
{
	//LOG("Freeing all items");

	/*for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemsL[i] != nullptr)
		{
			delete itemsL[i];
			itemsL[i] = nullptr;
		}
	}*/

	return true;
}

void Items::Draw()
{
	if (currentAnim != nullptr) {
		if (app->titleScreen->inTitle == 0) {
			app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
			
			//app->render->DrawTexture(texture,40, 40, &(currentAnim->GetCurrentFrame()));

			//int u = 0;
		}
			
	}
}

bool Items::AddItem(Item_type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (spawnQueue[i].type == Item_type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void Items::HandleItemsSpawn()
{
	// Iterate all the items queue
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (spawnQueue[i].type != Item_type::NO_TYPE)
		{
			// Spawn a new item if the screen has reached a spawn position
			//if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (app->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			//{
			//	LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);
			if (app->titleScreen->inTitle == 0) {
				SpawnItem(spawnQueue[i]);
				spawnQueue[i].type = Item_type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
			
			//}
		}
	}
}

void Items::HandleItemsDespawn()
{
	// Iterate existing items
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemsL[i] != nullptr)
		{
			// Delete the item when it has reached the end of the screen
			//if (items[i]->position.x * SCREEN_SIZE < (app->render->camera.x) - SPAWN_MARGIN)
			//{
			if (app->titleScreen->inTitle != 0)
				itemsL[i]->SetToDelete();

			if (removeAll == true)
				itemsL[i]->SetToDelete();
		}
	}

	if (removeAll == true) {
		removeAll = false;
	}
		
}

void Items::SpawnItem(const ItemSpawnpoint& info)
{
	// Find an empty slot in the items array
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemsL[i] == nullptr)
		{
			switch (info.type)
			{
			case Item_type::COIN:
				itemsL[i] = new Item_Coin(info.x, info.y);
				break;
			case Item_type::POTION:
				itemsL[i] = new Item_Potion(info.x, info.y);
				break;
			}
			//items[i]->texture = texture;
			//items[i]->destroyedFx = itemDestroyedFx;
			break;
		}
	}
}

void Items::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Items::OnCollision(Collider* c1, Collider* c2)
{
	int j = 8;
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		
		if (app->entity->FindEntity(EntityType::ITEM)->FindSubClassItem()->itemsL[i] != nullptr)
		{
			if (app->entity->FindEntity(EntityType::ITEM)->FindSubClassItem()->itemsL[i]->GetCollider() == c1) {
				//int u = position.x;
				app->entity->FindEntity(EntityType::ITEM)->FindSubClassItem()->itemsL[i]->OnCollision(c2); //Notify the enemy of a collision
				break;
			}
			
			
		}
	}
}

void Items::OnCollision(Collider* collider)
{
	
}

Collider* Items::GetCollider() const
{
	return collider;
}