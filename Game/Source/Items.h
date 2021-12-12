#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "Module.h"

#define MAX_ITEMS 100

enum class Item_type
{
	NO_TYPE,
	COIN,
	POTION,
};

struct ItemSpawnpoint
{
	Item_type type = Item_type::NO_TYPE;
	int x, y;
};

class AnyItem;
struct SDL_Texture;

class Items : public Module
{
public:
	// Constructor
	Items();

	// Destructor
	~Items();

	// Called when the module is activated
	// Loads the necessary textures for the items
	bool Start();

	// Called at the beginning of the application loop
	// Removes all items pending to delete
	bool PreUpdate();

	// Called at the middle of the application loop
	// Handles all items logic and spawning/despawning
	bool Update(float dt);

	// Called at the end of the application loop
	// Iterates all the items and draws them
	bool PostUpdate();

	// Called on application exit
	// Destroys all active items left in the array
	bool CleanUp();

	// Called when an item collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an item into the queue to be spawned later
	bool AddItem(Item_type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleItemsSpawn();

	// Destroys any items that have moved outside the camera limits
	void HandleItemsDespawn();

private:
	// Spawns a new item using the data from the queue
	void SpawnItem(const ItemSpawnpoint& info);

private:
	// A queue with all spawn points information
	ItemSpawnpoint spawnQueue[MAX_ITEMS];

	// All spawned items in the scene
	AnyItem* items[MAX_ITEMS] = { nullptr };

	// The items sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for collecting an item
	int itemDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__
