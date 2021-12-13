#include "Items.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Title.h"
#include "AnyItem.h"
#include "Item_Coin.h"
#include "Item_Potion.h"

Items::Items() : Module()
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
		items[i] = nullptr;
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
		if (items[i] != nullptr && items[i]->pendingToDelete)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}

	return true;
}

bool Items::Update(float dt)
{
	HandleItemsSpawn();

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
			items[i]->Update(dt);
	}

	HandleItemsDespawn();

	return true;
}

bool Items::PostUpdate()
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
			items[i]->Draw();
	}

	return true;
}

// Called before quitting
bool Items::CleanUp()
{
	//LOG("Freeing all items");

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}

	return true;
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
		if (items[i] != nullptr)
		{
			// Delete the item when it has reached the end of the screen
			//if (items[i]->position.x * SCREEN_SIZE < (app->render->camera.x) - SPAWN_MARGIN)
			//{
			if (app->titleScreen->inTitle != 0) {
				items[i]->SetToDelete();
			}

			if (removeAll == true) {
				items[i]->SetToDelete();
			}


			
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
		if (items[i] == nullptr)
		{
			switch (info.type)
			{
			case Item_type::COIN:
				items[i] = new Item_Coin(info.x, info.y);
				break;
			case Item_type::POTION:
				items[i] = new Item_Potion(info.x, info.y);
				break;
			}
			//items[i]->texture = texture;
			//items[i]->destroyedFx = itemDestroyedFx;
			break;
		}
	}
}

void Items::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr && items[i]->GetCollider() == c1)
		{
			items[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}