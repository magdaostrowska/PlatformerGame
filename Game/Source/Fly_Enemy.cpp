#include "Fly_Enemy.h"

#include "App.h"
#include "Collisions.h"

Fly_Enemy::Fly_Enemy(int x, int y) : AnyEnemy(x, y)
{
	fly.PushBack({ 5,72,21,22 });
	currentAnim = &fly;

	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	collider = app->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)app->enemies);
}

void Fly_Enemy::Update(float dt)
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	AnyEnemy::Update(dt);
}
