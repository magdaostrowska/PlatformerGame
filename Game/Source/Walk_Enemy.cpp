#include "Walk_Enemy.h"

#include "App.h"
#include "Collisions.h"
#include "Textures.h"
#include "Player.h"
#include "Title.h"

Walk_Enemy::Walk_Enemy(int x, int y) : AnyEnemy(x, y)
{
	texture_left = app->tex->Load("Assets/textures/enemies/walk_enemy_left.png");
	texture_right = app->tex->Load("Assets/textures/enemies/walk_enemy_right.png");

	walkLeft.PushBack({ 128,128,64,32 });
	walkLeft.PushBack({ 192,128,64,32 });
	walkLeft.PushBack({ 0,160,64,32 });
	walkLeft.PushBack({ 64,160,64,32 });

	walkLeft.loop = true;
	walkLeft.speed = 0.1f;

	walkRight.PushBack({ 64,128,64,32 });
	walkRight.PushBack({ 0,128,64,32 });
	walkRight.PushBack({ 192,160,64,32 });
	walkRight.PushBack({ 128,160,64,32 });

	walkRight.loop = true;
	walkRight.speed = 0.1f;

	currentAnim = &walkLeft;

	dir = 0;
	speed = 1*16/6;
	walkRect = { x+22, y+16, 23, 18 };

	collider = app->collisions->AddCollider(walkRect, Collider::Type::ENEMY, (Module*)app->enemies);
}

void Walk_Enemy::Update(float dt)
{
	speed = 1 * dt/6;
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

	collider->SetPos(position.x+22, position.y+16);

	isLeft = false;
	isRight = false;

	switch (dir) {
	case 1:
		currentAnim = &walkRight;
		break;
	case -1:
		currentAnim = &walkLeft;
		break;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	AnyEnemy::Update(dt);
}

void Walk_Enemy::PostUpdate() 
{}

void Walk_Enemy::OnCollision(Collider* col)
{

	/*if (col->type == Collider::Type::PLAYER) {
		if (app->player->hitCountdown == 0)
		{
			app->player->Die();
			app->player->hitCountdown = app->player->hitMaxCountdown;
		}
	}*/

	if (col->type == Collider::Type::GROUND) {
		
		switch (dir) {
		case 1:
			if (collider->rect.x + collider->rect.w < col->rect.x + col->rect.w){// && collider->rect.x + collider->rect.w > col->rect.x) 
			//if (collider->rect.x < col->rect.x {// && collider->rect.x + collider->rect.w > col->rect.x) {
				isRight = true;
			}
			break;
		case -1:
			if (collider->rect.x + speed < col->rect.x + col->rect.w) {//&& collider->rect.x > col->rect.x) {
			//if (collider->rect.x > col->rect.x) {
				isLeft = true;
			}
			break;
		}
	}

	AnyEnemy::OnCollision(collider);
}
