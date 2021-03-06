#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Entity.h"
#include "Animation.h"
#include "Point.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "Collisions.h"
#include "Scene.h"
#include "Fonts.h"
#include "Window.h"
#include "Shots.h"

#include "EntityManager.h"
#include "Entity.h"

struct SDL_Texture;
struct Collider;

class Player : public Entity
{
public:

	Player();
	virtual ~Player();

	bool Awake(pugi::xml_node&);
	void Spawn(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void ReSpawn();

	void OnCollision(Collider* c1, Collider* c2) override;
		
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	pugi::xml_node playerInfo;

	void Die();

public:

	//const int FPS = 30;
	//const int frameDelay = 100 / FPS;

	Uint32 frameStart;
	int frameTime;

	iPoint position;

	int maxLifes;
	int lifes;
	int posIniX;
	int posIniY;

	int coins;

	int speed;
	int jumpSpeed;
	int fallSpeed;

	int pdt;

	bool runningToLeft;
	bool runningToRight;

	bool onGround;
	bool isJumping;
	bool isTouchingLeft;
	bool isTouchingRight;
	int numPlat;
	bool sumPlat;
	bool sumPlat2;
	bool wallLeft;
	bool wallRight;
	int numJumps;
	bool stopJumping;

	bool godMode;

	int heightOnGround;
	int weightOnWall;

	SDL_Rect rectPlayer;

	SDL_Texture* textureIdleLeft;
	SDL_Texture* textureIdleRight;
	SDL_Texture* textureRunLeft;
	SDL_Texture* textureRunRight;
	SDL_Texture* textureJumpLeft;
	SDL_Texture* textureJumpRight;
	SDL_Texture* textureHitLeft;
	SDL_Texture* textureHitRight;
	SDL_Texture* textureDeathRight;
	SDL_Texture* textureDeathLeft;

	Animation* currentAnimation;

	Animation idleLeft, idleRight, runLeft, runRight, jumpLeft, jumpRight, hurtLeft, hurtRight, deathRight, deathLeft;

	unsigned int currentTime;

	unsigned int lastTimeJump;
	unsigned int lastTimeFall;

	int lastGroundposX;
	int lastGroundposY;

	int loadingPos = 0;

	int shotMaxCountdown = 20;
	int shotCountdown = 0;

	int hitCountdown=0;
	int	hitMaxCountdown = 60;

	int stunCountdown = 0;
	int	stunMaxCountdown = 30;

	bool isStunned = false;

	pugi::xml_document	document;

};

#endif //!__MODULE_PLAYER_H__