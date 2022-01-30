#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Module.h"
#include "Globals.h"


#include "EntityManager.h"
#include "Entity.h"


enum class Enemy_Type
{
	NO_TYPE,
	WALK,
	FLY,
};

struct EnemySpawnpoint
{
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x, y;
};

struct SDL_Texture;

class Enemies : public Entity
{
public:
	// Constructor
	Enemies();

	// Destructor
	~Enemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	void Draw();

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	virtual void OnCollision(Collider* collider);

	virtual Collider* GetCollider() const;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

	void SetToDelete();

	bool removeAll = false;

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

public:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemies* enemiesList[MAX_ENEMIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;

	bool spawnAll = false;

	////////////////ANY ITEM

// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture_left = nullptr;
	SDL_Texture* texture_right = nullptr;
	SDL_Texture* texture_die = nullptr;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	//Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
	int dir;

	int lifes;

	int hitCountdown = 0;
	int	hitMaxCountdown = 60;
};

#endif // __ENEMIES_H__
