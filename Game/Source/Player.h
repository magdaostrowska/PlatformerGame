#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class Player : public Module
{
public:

	Player();

	virtual ~Player();

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void spawn(int lvl);

public:

	const int FPS = 30;
	const int frameDelay = 100 / FPS;

	Uint32 frameStart;
	int frameTime;

	iPoint position;

	int speed = 1;

	bool runningToLeft = false;
	bool runningToRight = false;

	SDL_Rect rectPlayer;

	SDL_Texture* textureIdleLeft = nullptr;
	SDL_Texture* textureIdleRight = nullptr;
	SDL_Texture* textureRunLeft = nullptr;
	SDL_Texture* textureRunRight = nullptr;


	Animation* currentAnimation = nullptr;

	Animation idleLeft, idleRight, runLeft, runRight;

	Collider* collider = nullptr;
	/*
	iPoint position;

	int speed = 1;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation idleDown, idleUp, idleRight, idleLeft;
	Animation walkDown, walkUp, walkRight, walkLeft;
	Animation pushDown, pushUp, pushRight, pushLeft;

	Collider* collider = nullptr;

	Collider* colliderR = nullptr;
	Collider* colliderL = nullptr;
	Collider* colliderU = nullptr;
	Collider* colliderD = nullptr;
	bool resetTouch = true;

	bool destroyed = false;

	uint laserFx = 0;
	uint explosionFx = 0;

	int score = 000;

	const int FPS = 60;
	const int frameDelay = 100 / FPS;

	Uint32 frameStart;
	int frameTime;

	signed int countx = 0;
	signed int county = 0;
	signed int movx;
	signed int movy;

	bool posInix = true;
	bool posIniy = true;

	bool isTouchingR = false;
	bool isTouchingL = false;
	bool isTouchingU = false;
	bool isTouchingD = false;

	bool isPushingR = false;
	bool isPushingL = false;
	bool isPushingU = false;
	bool isPushingD = false;

	bool isBlockedR = false;
	bool isBlockedL = false;
	bool isBlockedU = false;
	bool isBlockedD = false;

	bool inContactR = false;
	bool inContactL = false;
	bool inContactU = false;
	bool inContactD = false;



	bool canStart = false;

	int zoom;

	int lvl;

	unsigned int currentTime;

	unsigned int lastTime = 0;

	int delay = 300;
	*/
};

#endif //!__MODULE_PLAYER_H__
