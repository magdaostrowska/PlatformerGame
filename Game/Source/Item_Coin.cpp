#include "Item_Coin.h"

#include "App.h"
#include "Collisions.h"
#include "Textures.h"
#include "Player.h"

Item_Coin::Item_Coin(int x, int y) : Entity(EntityType::ITEM_COIN, x, y)
{
	texture = app->tex->Load("Assets/textures/items/coin.png");

	coinAnim.PushBack({ 0, 0, 32, 32 });
	coinAnim.PushBack({ 32, 0, 32, 32 });
	coinAnim.PushBack({ 64, 0, 32, 32 });
	coinAnim.PushBack({ 96, 0, 32, 32 });
	coinAnim.PushBack({ 128, 0, 32, 32 });

	coinAnim.loop = true;
	coinAnim.speed = 0.1f;

	currentAnim = &coinAnim;

	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	coinRect = { x+9, y+8, 14, 16 };

	//collider = app->collisions->AddCollider({ x+9, y+8, 16, 16 }, Collider::Type::COIN, (Module*)app->items);
	collider = app->collisions->AddCollider(coinRect, Collider::Type::COIN, (Module*)app->items);
}

bool Item_Coin::Update(float dt)
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	//collider->SetPos(coinRect.x, coinRect.y);

	//currentAnim->Update();

	Entity::Update(dt);
	return true;
}

void Item_Coin::OnCollision(Collider* collider)
{
	app->player->coins++;
		SetToDelete();

	Entity::OnCollision(collider);
}
