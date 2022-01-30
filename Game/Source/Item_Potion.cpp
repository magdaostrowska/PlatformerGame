#include "Item_Potion.h"
#include "Items.h"
#include "App.h"
#include "Player.h"

Item_Potion::Item_Potion(int x, int y) : Items()
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
	potRect = { x + 9, y + 8, 14, 16 };
	//collider = app->collisions->AddCollider(potRect, Collider::Type::POTION, (Module*)app->items);
}

bool Item_Potion::Update(float dt)
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Entity::Update(dt);
	return true;
}

void Item_Potion::OnCollision(Collider* collider)
{
	//app->particles->AddParticle(app->particles->explosion, position.x, position.y);
	//app->audio->PlayFx(destroyedFx);

	if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->lifes < app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->maxLifes) {
		app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->lifes++;
		SetToDelete();
	}

	Entity::OnCollision(collider);
}