#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : Enemy(Enemy_Type::WALKING_ENEMY)
{
	name.Create("WalkingEnemy");
	type = Enemy_Type::WALKING_ENEMY;
	currentAnimation = nullptr;

	idle.PushBack({ 0,44,63,27 });
	//idle.PushBack({ 75,165,63,27 });
	//idle.PushBack({ 127,165,63,27 });
	//idle.PushBack({ 179,165,63,27 });
}

bool WalkingEnemy::Awake(pugi::xml_node& config)
{
	speed = config.child("velocity").attribute("value").as_float();
	position.x = 0;
	position.y = 50;
	return true;
}

bool WalkingEnemy::Start()
{
	enemySprite = app->tex->Load("Assets/Textures/enemies/enemy.png");
	currentAnimation = &idle;
	colliderEnemy = app->collisions->AddCollider(currentAnimation->GetCurrentFrame(), Collider::ENEMY, (Module*)this); //a collider to start
	return true;
}

bool WalkingEnemy::PreUpdate()
{
	return false;
}

bool WalkingEnemy::Update(float dt)
{
	position.y += 1;

	switch (state)
	{
	case Enemy_State::IDLE:
		currentAnimation = &idle;
		//ready = true;
		break;
	case Enemy_State::WALK_FORWARD:
		currentAnimation = &walk;
		isReversed = true;
		movingToLeft = false;
		movingToRight = true;
		position.x += 2;
		break;
	case Enemy_State::WALK_BACKWARD:
		currentAnimation = &walk;
		isReversed = false;
		movingToLeft = true;
		movingToRight = false;
		position.x -= 2;
		break;
	case Enemy_State::IS_HIT:
		currentAnimation = &hurt;
		hurt.Reset();
		isDead = true;
		//app->enemies->DestroyEnemy(this);
		break;
	default:
		break;
	}

	RenderEnemy();
	return true;
}

bool WalkingEnemy::CleanUp()
{
	return false;
}

void WalkingEnemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::GROUND)
	{
		position.y -= 1;
	}
}

void WalkingEnemy::RenderEnemy()
{
	if (enemySprite != nullptr && currentAnimation != nullptr)
	{
		if (isReversed)
			app->render->DrawTexture(enemySprite, position.x, position.y, &currentAnimation->GetCurrentFrame(), 1, 2);
		else
			app->render->DrawTexture(enemySprite, position.x, position.y, &currentAnimation->GetCurrentFrame());

		if (colliderEnemy != nullptr)
			colliderEnemy->SetPos(position.x, position.y);
	}
}

void WalkingEnemy::CalculatePath()
{
}
