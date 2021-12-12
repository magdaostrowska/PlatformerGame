#include "Fly_Enemy.h"
#include "Textures.h"
#include "App.h"
#include "Collisions.h"
#include "Player.h"
#include "Title.h"
#include "Map.h"
#include "PathFinding.h"

Fly_Enemy::Fly_Enemy(int x, int y) : AnyEnemy(x, y)
{
	state = FlyingEnemyState::IDLE;
	followsPath = true;

	texture_left = app->tex->Load("Assets/textures/enemies/fly_enemy_left.png");
	texture_right = app->tex->Load("Assets/textures/enemies/fly_enemy_right.png");
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

	collider = app->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)app->enemies);
}

void Fly_Enemy::Update(float dt)
{
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
		if (app->player->collider->rect.x < collider->rect.x) {

			dir = -1;
			if (isLeft == true) {
				position.x += speed * dir;
			}
		}
		else if (app->player->collider->rect.x + app->player->collider->rect.w > collider->rect.x + collider->rect.w) {
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
	AnyEnemy::Update(dt);
}

void Fly_Enemy::PostUpdate()
{}

void Fly_Enemy::OnCollision(Collider* col)
{
	if (app->player->godMode == false)
	{
		if (col->type == Collider::Type::PLAYER) {

			position.x += 300;
			position.y -= 150;

			if (app->player->hitCountdown == 0)
			{
				app->player->Die();
				app->player->hitCountdown = app->player->hitMaxCountdown;
			}
		}
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
	AnyEnemy::OnCollision(collider);
}

void Fly_Enemy::CalculatePath()
{
	iPoint playerPos = app->map->WorldToMap(app->player->position.x, app->player->position.y); // player position
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
