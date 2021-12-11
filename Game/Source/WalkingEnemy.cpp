#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy() : Enemy(Enemy_Type::WALKING_ENEMY)
{
	name.Create("WalkingEnemy");
	type = Enemy_Type::WALKING_ENEMY;

	//idle.PushBack({ 0,44,63,27 });
	//idle.PushBack({ 75,165,63,27 });
	//idle.PushBack({ 127,165,63,27 });
	//idle.PushBack({ 179,165,63,27 });
}

bool WalkingEnemy::Awake(pugi::xml_node& config)
{
	speed = config.child("velocity").attribute("value").as_float();
	return true;
}

bool WalkingEnemy::Start()
{
	enemySprite = app->tex->Load("Assets/Textures/enemies/enemy.png");
	//colliderEnemy = app->collisions->AddCollider(current_animation->GetCurrentFrame(), Collider::ENEMY, (Module*)this); //a collider to start
	return true;
}

bool WalkingEnemy::PreUpdate()
{
	return false;
}

bool WalkingEnemy::Update(float dt)
{
	switch (state)
	{
	case Enemy_State::IDLE:
		current_animation = &idle;
		//ready = true;
		break;
	case Enemy_State::WALK_FORWARD:
		current_animation = &walk;
		isReversed = true;
		movingToLeft = false;
		movingToRight = true;
		position.x += 2;
		break;
	case Enemy_State::WALK_BACKWARD:
		current_animation = &walk;
		isReversed = false;
		movingToLeft = true;
		movingToRight = false;
		position.x -= 2;
		break;
	case Enemy_State::IS_HIT:
		current_animation = &hurt;
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
}

void WalkingEnemy::RenderEnemy()
{
	if (enemySprite != nullptr && current_animation != nullptr)
	{
		if (isReversed)
			app->render->DrawTexture(enemySprite, position.x, position.y, &current_animation->GetCurrentFrame(), 1, 2);
		else
			app->render->DrawTexture(enemySprite, position.x, position.y, &current_animation->GetCurrentFrame());

		if (colliderEnemy != nullptr)
			colliderEnemy->SetPos(position.x, position.y);
	}
}

void WalkingEnemy::CalculatePath()
{
}
