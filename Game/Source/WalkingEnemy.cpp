#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : Enemy(Enemy_Type::WALKING_ENEMY)
{
	name.Create("WalkingEnemy");
	type = Enemy_Type::WALKING_ENEMY;
}

bool WalkingEnemy::Awake(pugi::xml_node& config)
{
	config = app->GetConfig();
	config = config.child("walkingEnemy");
	speed = config.child("velocity").attribute("value").as_float();
	return true;
}

bool WalkingEnemy::Start()
{
	return false;
}

bool WalkingEnemy::PreUpdate()
{
	return false;
}

bool WalkingEnemy::Update(float dt)
{
	return false;
}

bool WalkingEnemy::CleanUp()
{
	return false;
}

void WalkingEnemy::OnCollision(Collider* c1, Collider* c2)
{
}

void WalkingEnemy::CalculatePath()
{
}
