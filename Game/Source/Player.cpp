#include "Player.h"
#include "Log.h"
#include "Title.h"
#include "Map.h"
#include <iostream>

Player::Player() : Module()
{
	name.Create("player");

	lifes = 3;
	coins = 0;

	int t = 1;

	speed = 1.0f;
	jumpSpeed = 3.0f;
	fallSpeed = 1.0f*1;
	pdt = 16;

	runningToLeft = false;
	runningToRight = false;
	onGround = false;
	isJumping = false;
	isTouchingLeft = false;
	isTouchingRight = false;
	numPlat = 0;
	sumPlat = false;
	sumPlat2 = false;
	wallLeft = false;
	wallRight = false;
	numJumps = 0;
	stopJumping = true;

	godMode = false;

	heightOnGround = NULL;
	weightOnWall = NULL;

	textureIdleLeft = nullptr;
	textureIdleRight = nullptr;
	textureRunLeft = nullptr;
	textureRunRight = nullptr;
	textureJumpLeft = nullptr;
	textureJumpRight = nullptr;

	currentAnimation = nullptr;

	collider = nullptr;

	lastTimeJump = 0;
	lastTimeFall = 0;

	idleLeft.PushBack({ 0, 0, 48, 48 });
	idleLeft.PushBack({ 48, 0, 48, 48 });
	idleLeft.PushBack({ 96, 0, 48, 48 });
	idleLeft.PushBack({ 144, 0, 48, 48 });

	idleLeft.loop = true;
	idleLeft.speed = 0.1f;

	idleRight.PushBack({ 144, 0, 48, 48 });
	idleRight.PushBack({ 96, 0, 48, 48 });
	idleRight.PushBack({ 48, 0, 48, 48 });
	idleRight.PushBack({ 0, 0, 48, 48 });

	idleRight.loop = true;
	idleRight.speed = 0.1f;

	runLeft.PushBack({ 0, 0, 48, 48 });
	runLeft.PushBack({ 48, 0, 48, 48 });
	runLeft.PushBack({ 96, 0, 48, 48 });
	runLeft.PushBack({ 144, 0, 48, 48 });
	runLeft.PushBack({ 192, 0, 48, 48 });
	runLeft.PushBack({ 240, 0, 48, 48 });

	runLeft.loop = true;
	runLeft.speed = 0.15f;

	runRight.PushBack({ 240, 0, 48, 48 });
	runRight.PushBack({ 192, 0, 48, 48 });
	runRight.PushBack({ 144, 0, 48, 48 });
	runRight.PushBack({ 96, 0, 48, 48 });
	runRight.PushBack({ 48, 0, 48, 48 });
	runRight.PushBack({ 0, 0, 48, 48 });

	runRight.loop = true;
	runRight.speed = 0.15f;

	jumpLeft.PushBack({ 0, 0, 48, 48 });
	jumpLeft.PushBack({ 48, 0, 48, 48 });
	jumpLeft.PushBack({ 96, 0, 48, 48 });
	jumpLeft.PushBack({ 144, 0, 48, 48 });

	jumpLeft.loop = false;
	jumpLeft.speed = 0.4f;

	jumpRight.PushBack({ 144, 0, 48, 48 });
	jumpRight.PushBack({ 96, 0, 48, 48 });
	jumpRight.PushBack({ 48, 0, 48, 48 });
	jumpRight.PushBack({ 0, 0, 48, 48 });

	jumpRight.loop = false;
	jumpRight.speed = 0.4f;

	hurtLeft.PushBack({ 48, 0, 48, 48 });
	hurtLeft.PushBack({ 0, 0, 48, 48 });

	hurtLeft.loop = false;
	hurtLeft.speed = 1.0f;

	hurtRight.PushBack({ 0, 0, 48, 48 });
	hurtRight.PushBack({ 48, 0, 48, 48 });

	hurtRight.loop = false;
	hurtRight.speed = 1.0f;

	deathLeft.PushBack({ 196, 0, 48, 48 });
	deathLeft.PushBack({ 144, 0, 48, 48 });
	deathLeft.PushBack({ 96, 0, 48, 48 });
	deathLeft.PushBack({ 48, 0, 48, 48 });
	deathLeft.PushBack({ 0, 0, 48, 48 });
	

	deathLeft.loop = false;
	deathLeft.speed = 1.0f;

	deathRight.PushBack({ 0, 0, 48, 48 });
	deathRight.PushBack({ 48, 0, 48, 48 });
	deathRight.PushBack({ 96, 0, 48, 48 });
	deathRight.PushBack({ 144, 0, 48, 48 });
	deathRight.PushBack({ 196, 0, 48, 48 });

	deathRight.loop = false;
	deathRight.speed = 1.0f;

}

Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config) {

	bool ret = true;

	Spawn(config);
	//playerInfo = config;

	return ret;
}

bool Player::Start()
{
	//texture = App->textures->Load("Assets/Textures/spritesheet_player.png");
	textureIdleLeft = app->tex->Load("Assets/Textures/player/punk_idle_left.png");
	textureRunLeft = app->tex->Load("Assets/Textures/player/punk_run_left.png");
	textureJumpLeft = app->tex->Load("Assets/Textures/player/punk_jump_left.png");
	textureIdleRight = app->tex->Load("Assets/Textures/player/punk_idle_right.png");
	textureRunRight = app->tex->Load("Assets/Textures/player/punk_run_right.png");
	textureJumpRight = app->tex->Load("Assets/Textures/player/punk_jump_right.png");
	textureHitLeft = app->tex->Load("Assets/Textures/player/hurt_left.png");
	textureHitRight = app->tex->Load("Assets/Textures/player/hurt_right.png");
	textureDeathRight = app->tex->Load("Assets/Textures/player/death_right.png");
	textureDeathLeft = app->tex->Load("Assets/Textures/player/death_left.png");


	//idleLeft.Reset();
	currentAnimation = &idleLeft;
	collider = app->collisions->AddCollider({ position.x + 7 - speed, position.y + 14, 15 + 2 + 2 * speed, 34 + jumpSpeed * pdt / 4 }, Collider::Type::PLAYER, this);

	lastTimeFall = SDL_GetTicks();
	lastTimeJump = SDL_GetTicks();

	return true;
}

void Player::Spawn(pugi::xml_node& config) {
	
	currentAnimation = &idleLeft;

	if (app->scene->level == 1)
	{
		posIniX = config.child("position").attribute("x").as_int();
		posIniY = config.child("position").attribute("y").as_int();
	}
	else if (app->scene->level == 2)
	{
		posIniX = config.child("position").attribute("x").as_int();
		posIniY = config.child("position").attribute("y").as_int();
	}

	maxLifes = config.child("lifes").attribute("lifes").as_int();
	
	ReSpawn();
	
	
	//document.load_file("config.xml");

}

void Player::ReSpawn() {
	currentAnimation = &idleLeft;
	lifes = maxLifes;
	position.x = posIniX;
	position.y = posIniY;
	coins = 0;
	
	stunCountdown == 0;
}

bool Player::LoadState(pugi::xml_node& data)
{

	//Load player's lifes and  position
	lifes = data.child("lifes").attribute("lifes").as_int();
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	//Load level
	if (app->scene->level != data.child("level").attribute("level").as_int())
	{
		app->scene->level = data.child("level").attribute("level").as_int();
		app->fade->Fade();
	}

	//Load camera's position
	app->render->camera.x = data.child("playercamera").attribute("x").as_int();
	app->render->camera.y = data.child("playercamera").attribute("y").as_int();
	
	return true;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	std::cout << "SaveState Player" << std::endl;

	//Player's position and lifes
	data.append_child("position").append_attribute("x") = position.x;
	data.child("position").append_attribute("y") = position.y;
	data.append_child("lifes").append_attribute("lifes") = lifes;

	//Level
	data.append_child("level").append_attribute("level") = app->scene->level;

	//Camera position
	data.append_child("camera").append_attribute("x") = app->render->camera.x;
	data.child("camera").append_attribute("y") = app->render->camera.y;

	return true;
}

bool Player::PreUpdate() {

	return true;
}

bool Player::Update(float dt)
{
	currentTime = SDL_GetTicks();
	pdt = dt;

	/*
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
	*/

	if (app->titleScreen->inTitle == 1) {
		return true;
	}

	if (lifes >= 1) {
		if (currentAnimation == &hurtLeft) {
			currentAnimation = &idleRight;
		}
		
		if (currentAnimation == &hurtRight) {
			currentAnimation = &idleLeft;
		}
		
	}
	

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		LOG("Entering the godMode");

		if (!godMode) {
			isTouchingLeft = false;
			isTouchingRight = false;
		}

		godMode = !godMode;
	}

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		position = { 1500,0 };
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		//app->scene->level = 1;
		//app->scene->Start();
		//position = { 0,0 };
	}
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		//app->scene->level = 2;
		//app->scene->Start();
		//position = { 0,0 };
	}

	if (isTouchingLeft == false && isTouchingRight == false) {
		if (onGround == true) {
			lastTimeFall = currentTime;
			onGround = false;
			isJumping = false;
			jumpLeft.Reset();
			jumpRight.Reset();
			//stopJumping = false;
		}
	}
	else if (isTouchingLeft == true || isTouchingRight == true) {

		onGround = true;
		numJumps = 2;
		isJumping = false;
		//doubleJump = true;
	}
	isTouchingLeft = false;
	isTouchingRight = false;

	if (godMode == false)
	{
		
		if (onGround == false && stopJumping == true) {
			isJumping = false;
			//if (isStunned == false) {
				if (currentTime >= lastTimeFall + 200) {

					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && numJumps > 0) {
						if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
							currentAnimation = &jumpLeft;
							runningToLeft = true;
						}
						if (currentAnimation == &runRight || currentAnimation == &idleRight) {
							currentAnimation = &jumpRight;
							runningToRight = true;
						}
						lastTimeJump = currentTime;
						isJumping = true;
						numJumps--;
						stopJumping = false;
					}
					position.y += fallSpeed * 3 * pdt / 4;
				}
				else if (currentTime >= lastTimeFall + 150) {

					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && numJumps > 0) {
						if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
							currentAnimation = &jumpLeft;
							runningToLeft = true;
						}
						if (currentAnimation == &runRight || currentAnimation == &idleRight) {
							currentAnimation = &jumpRight;
							runningToRight = true;
						}
						lastTimeJump = currentTime;
						isJumping = true;
						numJumps--;
						stopJumping = false;
					}
					position.y += fallSpeed * 2 * pdt / 4;
				}
				else if (currentTime >= lastTimeFall + 40) {

					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && numJumps > 0) {
						if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
							currentAnimation = &jumpLeft;
							runningToLeft = true;
						}
						if (currentAnimation == &runRight || currentAnimation == &idleRight) {
							currentAnimation = &jumpRight;
							runningToRight = true;
						}
						lastTimeJump = currentTime;
						isJumping = true;
						numJumps--;
						stopJumping = false;
						//doubleJump = false;
					}
					position.y += fallSpeed * pdt / 4;
				}
				else {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && numJumps > 0) {
						if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
							currentAnimation = &jumpLeft;
							runningToLeft = true;
						}
						if (currentAnimation == &runRight || currentAnimation == &idleRight) {
							currentAnimation = &jumpRight;
							runningToRight = true;
						}
						lastTimeJump = currentTime;
						isJumping = true;
						numJumps--;
						stopJumping = false;
					}
				}

				//position.y += 1;
			//}
		}
	}
	//godMode == true
	else {
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			position.y -= speed;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			position.y += speed;
		}
	}

	//if (isStunned == false) {
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && wallRight == false) {
			if (position.x < 1600 - 24) {
				position.x += speed * pdt / 4;
				runningToLeft = true;
				runRight.Reset();
				currentAnimation = &runLeft;
			}
		}
		else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && wallLeft == false) {
			if (position.x > -7) {
				position.x -= speed * pdt / 4;
				runningToRight = true;
				runLeft.Reset();
				currentAnimation = &runRight;
			}
		}
		else if (onGround == true && currentAnimation != &hurtRight && currentAnimation != &hurtLeft) {
			if (runningToRight == true) {
				runningToRight = false;
				idleRight.Reset();
				currentAnimation = &idleRight;
			}
			else if (runningToLeft == true) {
				runningToLeft = false;
				idleLeft.Reset();
				currentAnimation = &idleLeft;
			}
		}
	//}

	wallLeft = false;
	wallRight = false;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && onGround == true && numJumps > 0) {
		if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
			currentAnimation = &jumpLeft;
			runningToLeft = true;
		}
		if (currentAnimation == &runRight || currentAnimation == &idleRight) {
			currentAnimation = &jumpRight;
			runningToRight = true;
		}
		lastTimeJump = currentTime;
		isJumping = true;
		stopJumping = false;
		numJumps--;
	}

	if (stopJumping == false && numJumps >= 0) {

		if (currentTime >= lastTimeJump + 150) {
			lastTimeFall = currentTime;
			stopJumping = true;
		}
		else if (currentTime >= lastTimeJump + 120) {
			position.y -= 1 * pdt / 4;
		}
		else if (currentTime >= lastTimeJump + 75) {
			position.y -= 2 * pdt / 4;
		}
		else {
			position.y -= jumpSpeed * pdt / 4;
		}
	}

	//if (isStunned == false) {
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && wallRight == false) {
			if (position.x < 1600 - 24) {
				runningToLeft = true;
				runningToRight = false;
			}
		}
		else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && wallLeft == false) {
			if (position.x > -7) {
				runningToRight = true;
				runningToLeft = false;
			}
		}
	//}
	

	if (isJumping == true || onGround == false) {
		if ((currentAnimation == &runLeft || currentAnimation == &idleLeft) && currentAnimation != &hurtRight && currentAnimation != &hurtLeft) {
			currentAnimation = &jumpLeft;
			runningToLeft = true;
			jumpRight.Reset();
		}
		if ((currentAnimation == &runRight || currentAnimation == &idleRight) && currentAnimation != &hurtRight && currentAnimation != &hurtLeft) {
			currentAnimation = &jumpRight;
			runningToRight = true;
			jumpLeft.Reset();
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
		if (shotCountdown <= 0)
		{
			int pos = 0;
			int dir = 1;
			if (currentAnimation == &idleRight || currentAnimation == &runRight || currentAnimation == &jumpRight) {
				pos = -16;
				dir = -1;
			}
			else if (currentAnimation == &idleLeft || currentAnimation == &runLeft || currentAnimation == &jumpLeft) {
				pos = collider->rect.w +2;
				dir = 1;
				
			}

			Particle* newParticle = app->shots->AddParticle(app->shots->shot, position.x + pos, position.y+16, dir, Collider::Type::SHOT);

			newParticle->collider->AddListener(this);
			shotCountdown = shotMaxCountdown;
		}
	}

	if (hitCountdown > 0) {
		hitCountdown = hitCountdown - dt / 16;
	}

	if (shotCountdown > 0) {
		shotCountdown = shotCountdown - dt / 16;
	}

	if (stunCountdown > 0) {
		isStunned = true;
		stunCountdown = stunCountdown - dt / 16;
	}
	else {
		isStunned = false;
	}

	if (isStunned == true) {
		if (currentAnimation == &idleRight || currentAnimation == &runRight || currentAnimation == &jumpRight) {
			currentAnimation = &hurtLeft;
		}
		else if (currentAnimation == &idleLeft || currentAnimation == &runLeft || currentAnimation == &jumpLeft) {
			currentAnimation = &hurtRight;

		}
	}

	

	

	if (!godMode) {
		if (position.y >= (app->render->camera.y + app->render->camera.h) / 3){
			Die();
		}
	}

	if (collider != nullptr)
	{
		collider->SetPos(position.x + 6 - speed, position.y + 14);

	}

	if ((deathLeft.HasFinished() || deathRight.HasFinished() )&& lifes <=0) {
		
		app->fade->Fade(120, 0);
		if (app->fade->frameCount >= app->fade->maxFadeFrames) {
			app->titleScreen->inTitle = 2;
		}

		//app->map->RemoveCol();
		//app->map->LoadCol();
		//position = { 0,0 };
		//Spawn(playerInfo);
		//coins = 0;
	}


	return true;
}

bool Player::PostUpdate()
{
	if (app->titleScreen->inTitle == 1) {
		return true;
	}
	currentAnimation->Update();

	
	return true;
}

void Player::Die() {
	if (lifes > 1) {
		lifes--;
		
		
		if (position.y >= (app->render->camera.y + app->render->camera.h) / 3) {
			position = { lastGroundposX,lastGroundposY - 48 };
		}

		hitCountdown = hitMaxCountdown;
		stunCountdown = stunMaxCountdown;
		
	}
	else if (lifes <= 1) {
		lifes = 0;
		if (currentAnimation == &idleRight || currentAnimation == &runRight || currentAnimation == &jumpRight || currentAnimation == &hurtRight) {
			currentAnimation = &deathLeft;
		}
		else if (currentAnimation == &idleLeft || currentAnimation == &runLeft || currentAnimation == &jumpLeft || currentAnimation == &hurtLeft) {
			currentAnimation = &deathRight;

		}

		
		
	}

}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (godMode == false) {

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GROUND) {

			if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed * 16 / 4 + 1 && c1->rect.y + c1->rect.h >= c2->rect.y) {
				if (loadingPos == 0) {
					position.y = c2->rect.y - 48;
				}
				else {
					loadingPos++;
					if (loadingPos >= 3) {
						if (position.y != c2->rect.y - 48) {
							loadingPos = 0;
						}
					}



				}

				if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { 

					isTouchingLeft = true;
					lastGroundposX = c2->rect.x;
					lastGroundposY = c2->rect.y;
				}

			}

			if (c1->rect.y + c1->rect.h - jumpSpeed * 16 / 4 != c2->rect.y && isJumping == false) {

				if (c1->rect.x + c1->rect.w - 2 - speed * 16 / 4 < c2->rect.x && c1->rect.x + c1->rect.w + speed * 16 / 4 > c2->rect.x) {
					//wallRight = true;
				}

				if (c1->rect.x + 2 + speed * 16 / 4 > c2->rect.x + c2->rect.w && c1->rect.x - speed * 16 / 4 < c2->rect.x + c2->rect.w) {
					//wallLeft = true;
				}
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL) {

			if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed * 16 / 4 + 1 && c1->rect.y + c1->rect.h >= c2->rect.y) {
				//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				if (loadingPos == 0) {
					position.y = c2->rect.y - 48;
				}
				else {
					loadingPos++;
					if (loadingPos >= 3) {
						if (position.y != c2->rect.y - 48) {
							loadingPos = 0;
						}
					}



				}

				if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { 

					isTouchingLeft = true;
					lastGroundposX = c2->rect.x;
					lastGroundposY = c2->rect.y;
					//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				}
			}

			if (c1->rect.y + c1->rect.h - jumpSpeed * 16 / 4 != c2->rect.y) {

				if (c1->rect.y < c2->rect.y) {
					
					if (c1->rect.x + c1->rect.w - 2 - speed * 16 / 4 < c2->rect.x) {
						wallRight = true;
					}

					if (c1->rect.x + 2 + speed * 16 / 4 > c2->rect.x + c2->rect.w && c1->rect.x - speed < c2->rect.x + c2->rect.w) {
						wallLeft = true;
					}
				}
			}
		}
	}
}

bool Player::CleanUp() {
	return true;
}