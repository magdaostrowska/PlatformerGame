#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : Enemy(Enemy_Type::WALKING_ENEMY)
{
}

bool WalkingEnemy::Awake(pugi::xml_node&)
{
	return false;
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

void WalkingEnemy::BlitPath()
{
}

void WalkingEnemy::CheckPath()
{
}

void WalkingEnemy::BlitEverything()
{
}

bool WalkingEnemy::CheckInAir()
{
	return false;
}
