#include "Walk_Enemy.h"
#include "Collisions.h"
#include "Textures.h"
#include "Player.h"
#include "Title.h"
#include "Enemies.h"

Walk_Enemy::Walk_Enemy(int x, int y) : Enemies()
{
	position.x = x;
	position.y = y;

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

	hitLeft.PushBack({ 128,160,64,32 });
	hitLeft.PushBack({ 192,160,64,32 });

	hitLeft.loop = false;
	hitLeft.speed = 0.1f;

	hitRight.PushBack({ 64,160,64,32 });
	hitRight.PushBack({ 0,160,64,32 });

	hitRight.loop = false;
	hitRight.speed = 0.1f;

	dieLeft.PushBack({ 0,192,64,32 });
	dieLeft.PushBack({ 64,192,64,32 });
	dieLeft.PushBack({ 128,192,64,32 });
	dieLeft.PushBack({ 192,192,64,32 });

	dieLeft.PushBack({ 0,224,64,32 });
	dieLeft.PushBack({ 64,224,64,32 });
	dieLeft.PushBack({ 128,224,64,32 });
	dieLeft.PushBack({ 192,224,64,32 });

	dieLeft.loop = false;
	dieLeft.speed = 0.1f;

	dieRight.PushBack({ 192,192,64,32 });
	dieRight.PushBack({ 128,192,64,32 });
	dieRight.PushBack({ 64,192,64,32 });
	dieRight.PushBack({ 0,192,64,32 });

	dieRight.PushBack({ 192,224,64,32 });
	dieRight.PushBack({ 128,224,64,32 });
	dieRight.PushBack({ 64,224,64,32 });
	dieRight.PushBack({ 0,224,64,32 });

	dieRight.loop = false;
	dieRight.speed = 0.1f;


	currentAnim = &walkLeft;

	lifes = 3;

	dir = 0;
	speed = 1 * 16 / 6;
	walkRect = { x + 22 - 5, y + 16, 23 + 10, 18 };

	collider = app->collisions->AddCollider(walkRect, Collider::Type::ENEMY, this);
}

bool Walk_Enemy::Update(float dt)
{

	speed = 1 * dt / 6;
	
	if (app->titleScreen->inTitle == 0 && app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->collider != NULL && collider != NULL) {
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





	collider->SetPos(position.x + 22 - 5, position.y + 16);

	isLeft = false;
	isRight = false;

	switch (dir) {
	case 1:
		if (currentAnim != &hitRight && currentAnim != &hitLeft && currentAnim != &dieLeft && currentAnim != &dieRight) {
			currentAnim = &walkRight;
		}
		else if (currentAnim == &hitRight) {
			if (hitRight.HasFinished()) {
				hitRight.Reset();
				hitRight.ResetLoopCount();
				hitLeft.Reset();
				hitLeft.ResetLoopCount();
				currentAnim = &walkRight;
			}
		}
		else if (currentAnim == &hitLeft) {
			if (hitLeft.HasFinished()) {
				hitRight.Reset();
				hitRight.ResetLoopCount();
				hitLeft.Reset();
				hitLeft.ResetLoopCount();
				currentAnim = &walkRight;
			}
		}
		else if (currentAnim == &dieRight) {
			if (dieRight.HasFinished()) {
				dieRight.Reset();
				dieRight.ResetLoopCount();
				dieLeft.Reset();
				dieLeft.ResetLoopCount();
				SetToDelete();
				texture_left = nullptr;
				texture_right = nullptr;
			}
		}
		else if (currentAnim == &dieLeft) {
			if (dieLeft.HasFinished()) {
				dieRight.Reset();
				dieRight.ResetLoopCount();
				dieLeft.Reset();
				dieLeft.ResetLoopCount();
				SetToDelete();
				texture_left = nullptr;
				texture_right = nullptr;
			}
		}
		break;
	case -1:
		if (currentAnim != &hitRight && currentAnim != &hitLeft && currentAnim != &dieLeft && currentAnim != &dieRight) {
			if (pendingToDelete == false) {
				currentAnim = &walkLeft;
			}

		}
		else if (currentAnim == &hitRight) {
			if (hitRight.HasFinished()) {
				hitRight.Reset();
				hitRight.ResetLoopCount();
				hitLeft.Reset();
				hitLeft.ResetLoopCount();
				currentAnim = &walkLeft;
			}
		}
		else if (currentAnim == &hitLeft) {
			if (hitLeft.HasFinished()) {
				hitRight.Reset();
				hitRight.ResetLoopCount();
				hitLeft.Reset();
				hitLeft.ResetLoopCount();
				currentAnim = &walkLeft;
			}
		}
		else if (currentAnim == &dieRight) {
			if (dieRight.HasFinished()) {
				dieRight.Reset();
				dieRight.ResetLoopCount();
				dieLeft.Reset();
				dieLeft.ResetLoopCount();
				SetToDelete();
				texture_left = nullptr;
				texture_right = nullptr;
			}
		}
		else if (currentAnim == &dieLeft) {
			if (dieLeft.HasFinished()) {
				dieRight.Reset();
				dieRight.ResetLoopCount();
				dieLeft.Reset();
				dieLeft.ResetLoopCount();
				SetToDelete();
				texture_left = nullptr;
				texture_right = nullptr;
			}
		}
		break;
	}

	if (hitCountdown > 0) {
		hitCountdown = hitCountdown - dt / 16;
	}

	currentAnim->Update();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	return true;
}

bool Walk_Enemy::PostUpdate() {
	return true;
}

void Walk_Enemy::OnCollision(Collider* col)
{
	if (col->type == Collider::Type::PLAYER) {
		if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hitCountdown <= 0)
		{
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->Die();

		}
	}

	if (col->type == Collider::Type::GROUND) {


		switch (dir) {
		case 1:
			//if (collider->rect.x + collider->rect.w < col->rect.x + col->rect.w && collider->rect.x + collider->rect.w > col->rect.x) {
			//if (collider->rect.x < col->rect.x {// && collider->rect.x + collider->rect.w > col->rect.x) {
			//if (collider->rect.x + collider->rect.w -5 < col->rect.x + col->rect.w && collider->rect.x + collider->rect.w > col->rect.x) {
			if (collider->rect.x + collider->rect.w > col->rect.x && collider->rect.x < col->rect.x) {
				isRight = true;
			}

			break;
		case -1:
			if (collider->rect.x< col->rect.x + collider->rect.w && collider->rect.x > col->rect.x) {
				//if (collider->rect.x > col->rect.x) {
				isLeft = true;
			}
			break;
		}
	}

	if (col->type == Collider::Type::SHOT) {

		if (hitCountdown <= 0)
		{
			switch (dir) {
			case 1:

				if (lifes > 1) {
					lifes--;
					currentAnim = &hitRight;
				}
				else {
					//currentAnim = &walkRight;
					currentAnim = &dieRight;
				}

				break;
			case -1:
				if (lifes > 1) {
					lifes--;
					currentAnim = &hitLeft;
				}
				else {
					//currentAnim = &walkRight;
					currentAnim = &dieLeft;
				}
				break;
			}
			hitCountdown = hitMaxCountdown;
			int o = 0;
		}
	}
}

bool Walk_Enemy::LoadState(pugi::xml_node& data)
{
	data = data.child("walking_enemy");

	//Load enemy's position
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}

bool Walk_Enemy::SaveState(pugi::xml_node& data) const
{
	data = data.append_child("walking_enemy");

	//Enemy's position
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;

	data = data.parent();
	return true;
}
