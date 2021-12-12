#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "ModuleEnemy.h"
#include "Animation.h"
#include "App.h"
//#include <memory>

enum class Enemy_State
{
	IDLE,
	WALK_FORWARD,
	WALK_BACKWARD,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD,
	FLY,
	FLY_FORWARD,
	FLY_BACKWARD,
	FLY_UP,
	IS_HIT,
	FALL,
	DIE,
};

class Enemy : public ModuleEnemy {

public:
	Enemy(Enemy_Type type);
	virtual ~Enemy();

	virtual bool Awake(pugi::xml_node& config) { return true; };
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };

	virtual void RenderEnemy() {};

	virtual bool OnCollision() { return true; };

public:

	Animation idle;
	Animation walk;
	Animation jump_up;
	Animation jump_down;
	Animation fly;
	Animation fall;
	Animation hurt;
	Animation death;

	Animation* currentAnimation;
	//std::unique_ptr<Animation> currentAnimation = std::make_unique<Animation>();

	//std::unique_ptr<SDL_Texture> enemySprite = std::make_unique<SDL_Texture>();
	Collider* colliderEnemy;

	//Type and states
	Enemy_Type type;
	Enemy_State state;

	//Initial position
	//float				initX;
	//float				initY;

	bool				movingToLeft;
	bool				movingToRight;
	bool				isHit;
	bool				isReversed;
	bool				isDead;

	//Entity settings
	iPoint				position;
	float				speed;
	float				fallSpeed;
	float 				maxFallSpeed;
	float 				jumpSpeed; // optional
	float				dt;
};


#endif