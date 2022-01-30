#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "Module.h"
#include "Globals.h"

#include "Entity.h"
#include "EntityManager.h"

enum class Item_type
{
	NO_TYPE,
	COIN,
	POTION,
};

struct ItemSpawnpoint
{
	Item_type type = Item_type::NO_TYPE;
	//EntityType type = EntityType::UNKNOWN;
	int x, y;
};

class AnyItem;
struct SDL_Texture;

class Items : public Entity
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

	void Draw();

	// Called when an item collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	virtual void OnCollision(Collider* collider);

	virtual Collider* GetCollider() const;

	// Add an item into the queue to be spawned later
	bool AddItem(Item_type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleItemsSpawn();

	// Destroys any items that have moved outside the camera limits
	void HandleItemsDespawn();

	void SetToDelete();

	bool removeAll = false;

private:
	// Spawns a new item using the data from the queue
	void SpawnItem(const ItemSpawnpoint& info);

protected:

	// A queue with all spawn points information
	ItemSpawnpoint spawnQueue[MAX_ITEMS];

	// All spawned items in the scene
	Items* itemsL[MAX_ITEMS] = { nullptr };

	// The items sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for collecting an item
	int itemDestroyedFx = 0;

	////////////////ANY ITEM

	// The current position in the world
	iPoint position;


	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	//Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __MODULE_ENEMIES_H__
