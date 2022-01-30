#include "Fly_Enemy.h"
#include "Textures.h"
#include "Collisions.h"
#include "Player.h"
#include "Title.h"
#include "Map.h"
#include "PathFinding.h"

Fly_Enemy::Fly_Enemy(int x, int y) : Enemies()
{

	position.x = x;
	position.y = y;

	state = FlyingEnemyState::IDLE;
	followsPath = true;

	texture_left = app->tex->Load("Assets/textures/enemies/fly_enemy_left.png");
	texture_right = app->tex->Load("Assets/textures/enemies/fly_enemy_right_1.png");
	texture_die = app->tex->Load("Assets/textures/enemies/fly_enemy_left.png");

	flyLeft.PushBack({ 0,18,64,40 });
	flyLeft.PushBack({ 64,18,64,40 });
	flyLeft.PushBack({ 128,18,64,40 });
	flyLeft.PushBack({ 192,18,64,40 });

	flyLeft.loop = true;
	flyLeft.speed = 0.1f;

	flyRight.PushBack({ 0,18,64,40 });
	flyRight.PushBack({ 64,18,64,40 });
	flyRight.PushBack({ 128,18,64,40 });
	flyRight.PushBack({ 192,18,64,40 });

	flyRight.loop = true;
	flyRight.speed = 0.1f;

	die.PushBack({ 0,256,66,50 });
	die.PushBack({ 66,256,66,50 });
	die.PushBack({ 132,256,66,50 });
	die.PushBack({ 80,654,48,39 });
	die.PushBack({ 128,654,48,39 });
	die.PushBack({ 192,654,48,39 });

	currentAnim = &flyLeft;

	dir = 0;
	speed = 1 * 16 / 6;

	flyRect = { 0, 0, 24, 24 };

	collider = app->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, this);
}

bool Fly_Enemy::Update(float dt)
{
	if (app->scene->inPause == false) {
		CalculatePath();

		switch (state)
		{
		case FlyingEnemyState::IDLE:
			followsPath = true;
			break;
		case FlyingEnemyState::FLY_LEFT:
			position.x -= speed;
			break;
		case FlyingEnemyState::FLY_RIGHT:
			position.x += speed;
			break;
		case FlyingEnemyState::FLY_UP:
			position.y -= speed;
			break;
		case FlyingEnemyState::FLY_DOWN:
			position.y += speed;
			break;
		case FlyingEnemyState::DIE:
			break;
		default:
			break;
		}

		speed = 0.5 * dt / 6;
		currentAnim->Update();

		if (app->titleScreen->inTitle == 0) {
			if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->collider->rect.x < collider->rect.x) {

				dir = -1;
				if (isLeft == true) {
					position.x += speed * dir;
				}
			}
			else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->collider->rect.x + app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->collider->rect.w > collider->rect.x + collider->rect.w) {
				dir = 1;
				if (isRight == true) {
					position.x += speed * dir;
				}
			}
		}

		collider->SetPos(position.x + 22, position.y + 16);

		isLeft = false;
		isRight = false;

		switch (dir) {
		case 1:
			currentAnim = &flyRight;
			break;
		case -1:
			currentAnim = &flyLeft;
			break;
		}
		//AnyEnemy::Update(dt);
	}
	return true;
}

bool Fly_Enemy::PostUpdate()
{
	return true;
}

void Fly_Enemy::OnCollision(Collider* col)
{
	if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->godMode == false)
	{
		if (col->type == Collider::Type::PLAYER) {

			position.x += 300;
			position.y -= 150;

			if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hitCountdown == 0)
			{
				app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->Die();
				app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hitCountdown = app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hitMaxCountdown;
			}
		}
	}

	if (col->type == Collider::Type::SHOT) {
		//pendingToDelete = true;
		SetToDelete();
	}

	if (col->type == Collider::Type::GROUND) {

		switch (dir) {
		case 1:
			if (collider->rect.x + collider->rect.w < col->rect.x + col->rect.w) {
				isRight = true;
			}
			break;
		case -1:
			if (collider->rect.x + speed < col->rect.x + col->rect.w)
				isLeft = true;
			break;
		}
	}
	//AnyEnemy::OnCollision(collider);
}

void Fly_Enemy::CalculatePath()
{
	iPoint playerPos = app->map->WorldToMap(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y); // player position
	iPoint enemyPos = app->map->WorldToMap(position.x, position.y); // enemy position

	if (playerPos != enemyPos)
	{
		app->pathfinding->CreatePath(playerPos, enemyPos);
		if (followsPath == true)PathToMove();
	}
}

void Fly_Enemy::PathToMove()
{
	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
	iPoint pos = app->map->MapToWorld(path->At(1)->x, path->At(1)->y);

	if (pos.x < position.x)
	{
		state = FlyingEnemyState::FLY_LEFT;
	}
	if (pos.x > position.x)
	{
		state = FlyingEnemyState::FLY_RIGHT;
	}

	if (pos.x >= position.x - 5 && pos.x <= position.x + 5)
	{
		state = FlyingEnemyState::FLY_DOWN;
	}
}

bool Fly_Enemy::LoadState(pugi::xml_node& data)
{
	data = data.child("flying_enemy");

	//Load enemy's position
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool Fly_Enemy::SaveState(pugi::xml_node& data) const
{
	std::cout << "SaveState Player" << std::endl;
	data = data.append_child("flying_enemy");

	//Enemy's position
	
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	data = data.parent();
	return true;
}
