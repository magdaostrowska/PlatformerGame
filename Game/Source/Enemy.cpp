#include "Enemy.h"

Enemy::Enemy(Enemy_Type type) : ModuleEnemy()
{
	type = Enemy_Type::NO_TYPE;
	state = Enemy_State::IDLE;
	collider_entity = nullptr;

	isDead = false;
	isMovingRight = false;
	isMovingLeft = false;
	beingHit = false;
	isReversed = false;

	collider_at_right = false; //If true, entity can't go to the right 
	collider_at_left = false;
}

Enemy::~Enemy()
{

}