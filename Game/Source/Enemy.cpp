#include "Enemy.h"

Enemy::Enemy(Enemy_Type type) : ModuleEnemy()
{
	type = Enemy_Type::NO_TYPE;
	state = Enemy_State::IDLE;

	enemySprite = nullptr;
	isDead = false;
	movingToRight = false;
	movingToLeft = false;
	isHit = false;
	isReversed = false;
	colliderEnemy = nullptr;
}

Enemy::~Enemy()
{

}