#include "Item_Potion.h"

#include "App.h"
#include "Collisions.h"
#include "Textures.h"
#include "Player.h"

Item_Potion::Item_Potion(int x, int y) : AnyItem(x, y)
{
	texture = app->tex->Load("Assets/textures/items/potion.png");

	potAnim.PushBack({ 0, 0, 32, 32 });
	potAnim.PushBack({ 32, 0, 32, 32 });
	potAnim.PushBack({ 64, 0, 32, 32 });
	potAnim.PushBack({ 96, 0, 32, 32 });
	potAnim.PushBack({ 128, 0, 32, 32 });
	potAnim.PushBack({ 160, 0, 32, 32 });
	potAnim.PushBack({ 192, 0, 32, 32 });
	potAnim.PushBack({ 224, 0, 32, 32 });


	potAnim.loop = true;
	potAnim.speed = 0.1f;

	currentAnim = &potAnim;

	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	potRect = { x + 9, y + 8, 14, 16 };

	//collider = app->collisions->AddCollider({ x+9, y+8, 16, 16 }, Collider::Type::COIN, (Module*)app->items);
	collider = app->collisions->AddCollider(potRect, Collider::Type::POTION, (Module*)app->items);
}

void Item_Potion::Update(float dt)
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	AnyItem::Update(dt);
}

void Item_Potion::OnCollision(Collider* collider)
{
	//app->particles->AddParticle(app->particles->explosion, position.x, position.y);
	//app->audio->PlayFx(destroyedFx);

	if (app->player->lifes < app->player->maxLifes) {
		app->player->lifes++;
		SetToDelete();
	}

	
	AnyItem::OnCollision(collider);
}