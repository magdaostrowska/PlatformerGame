#include "Enemies.h"

#include "App.h"

#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Title.h"

#include "AnyEnemy.h"
#include "Fly_Enemy.h"
#include "Walk_Enemy.h"


#define SPAWN_MARGIN 50


Enemies::Enemies() : Module()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemiesList[i] = nullptr;
}

Enemies::~Enemies()
{

}

bool Enemies::Start()
{
	//texture = app->tex->Load("Assets/Sprites/enemies.png");
	//enemyDestroyedFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}


bool Enemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr && enemiesList[i]->pendingToDelete)
		{
			delete enemiesList[i];
			enemiesList[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::Update(float dt)
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr)
			enemiesList[i]->Update(dt);
	}

	HandleEnemiesDespawn();

	return true;
}

bool  Enemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr)
			enemiesList[i]->Draw();
	}

	return true;
}

// Called before quitting
bool Enemies::CleanUp()
{
	//LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr)
		{
			delete enemiesList[i];
			enemiesList[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
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

void Enemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			//if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			//{
			//	LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);
			if (app->titleScreen->inTitle == 0) {
				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		//	}
		}
	}
}

void Enemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			//if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			//{
				//LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
			if (app->titleScreen->inTitle != 0) {
				enemiesList[i]->SetToDelete();
			}

			if (removeAll==true) {
				enemiesList[i]->SetToDelete();
			}

			
			//}
		}
		
	}
	if (removeAll == true) {
		removeAll = false;
	}
}

void Enemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::WALK_ENEMY:
				enemiesList[i] = new Walk_Enemy(info.x, info.y);
				break;
			case Enemy_Type::FLY_ENEMY:
				enemiesList[i] = new Fly_Enemy(info.x, info.y);
				break;
			}
			//enemiesList[i]->texture = texture;
			//enemiesList[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void Enemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemiesList[i] != nullptr && enemiesList[i]->GetCollider() == c1)
		{
			enemiesList[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}