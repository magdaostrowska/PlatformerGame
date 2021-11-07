#include "Player.h"
#include "Log.h"
#include "Title.h"
#include <iostream>

Player::Player() : Module()
{
	name.Create("player");

	lifes = 3;

	speed = 1.0f;
	jumpSpeed = 3;

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
	idleLeft.speed = 0.025f;

	idleRight.PushBack({ 144, 0, 48, 48 });
	idleRight.PushBack({ 96, 0, 48, 48 });
	idleRight.PushBack({ 48, 0, 48, 48 });
	idleRight.PushBack({ 0, 0, 48, 48 });

	idleRight.loop = true;
	idleRight.speed = 0.025f;

	runLeft.PushBack({ 0, 0, 48, 48 });
	runLeft.PushBack({ 48, 0, 48, 48 });
	runLeft.PushBack({ 96, 0, 48, 48 });
	runLeft.PushBack({ 144, 0, 48, 48 });
	runLeft.PushBack({ 192, 0, 48, 48 });
	runLeft.PushBack({ 240, 0, 48, 48 });

	runLeft.loop = true;
	runLeft.speed = 0.05f;

	runRight.PushBack({ 240, 0, 48, 48 });
	runRight.PushBack({ 192, 0, 48, 48 });
	runRight.PushBack({ 144, 0, 48, 48 });
	runRight.PushBack({ 96, 0, 48, 48 });
	runRight.PushBack({ 48, 0, 48, 48 });
	runRight.PushBack({ 0, 0, 48, 48 });

	runRight.loop = true;
	runRight.speed = 0.05f;

	jumpLeft.PushBack({ 0, 0, 48, 48 });
	jumpLeft.PushBack({ 48, 0, 48, 48 });
	jumpLeft.PushBack({ 96, 0, 48, 48 });
	jumpLeft.PushBack({ 144, 0, 48, 48 });

	jumpLeft.loop = false;
	jumpLeft.speed = 0.05f;

	jumpRight.PushBack({ 144, 0, 48, 48 });
	jumpRight.PushBack({ 96, 0, 48, 48 });
	jumpRight.PushBack({ 48, 0, 48, 48 });
	jumpRight.PushBack({ 0, 0, 48, 48 });

	jumpRight.loop = false;
	jumpRight.speed = 0.05f;
}

Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config) {

	bool ret = true;

	Spawn(config);

	return ret;
}

bool Player::Start()
{
	//texture = App->textures->Load("Assets/Textures/spritesheet_player.png");
	textureIdleLeft = app->tex->Load("Assets/Textures/Punk_idle_left.png");
	textureRunLeft = app->tex->Load("Assets/Textures/Punk_run_left.png");
	textureJumpLeft = app->tex->Load("Assets/Textures/Punk_jump_left.png");
	textureIdleRight = app->tex->Load("Assets/Textures/Punk_idle_right.png");
	textureRunRight = app->tex->Load("Assets/Textures/Punk_run_right.png");
	textureJumpRight = app->tex->Load("Assets/Textures/Punk_jump_right.png");

	//idleLeft.Reset();
	currentAnimation = &idleLeft;
	collider = app->collisions->AddCollider({ position.x + 7 - speed, position.y + 14, 15 + 2 + 2 * speed, 34 + jumpSpeed }, Collider::Type::PLAYER, this);

	lastTimeFall = SDL_GetTicks();
	lastTimeJump = SDL_GetTicks();

	return true;
}

void Player::Spawn(pugi::xml_node& config) {
	

	if (app->scene->level == 1)
	{
		position.x = config.child("level1").child("position").attribute("x").as_int();
		position.y = config.child("level1").child("position").attribute("y").as_int();
	}
	else if (app->scene->level == 2)
	{
		position.x = config.child("level2").child("position").attribute("x").as_int();
		position.y = config.child("level2").child("position").attribute("y").as_int();
	}

	lifes = config.child("lifes").attribute("lifes").as_int();
	document.load_file("config.xml");

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

	if (app->titleScreen->inTitle == true) {
		return true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		LOG("Entering the godMode");

		if(!godMode) {
			isTouchingLeft = false;
			isTouchingRight = false;
		}

		godMode = !godMode;
	}
	return true;
}


bool Player::Update(float dt)
{
	currentTime = SDL_GetTicks();

	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}

	if (app->titleScreen->inTitle == 1|| app->titleScreen->inTitle == 2) {
		return true;
	}



	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		app->scene->level = 1;
		app->scene->Start();
		//position = { 0,0 };
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		app->scene->level = 1;
		app->scene->Start();
		//position = { 0,0 };
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		app->scene->level = 2;
		app->scene->Start();
		//position = { 0,180 };
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

	if (onGround == false && stopJumping == true) {
		//jumpLeft.Reset();
		//jumpRight.Reset();
		isJumping = false;
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
				//doubleJump = false;
			}
			position.y += 3;
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
				//doubleJump = false;
			}

			position.y += 2;
		}
		else if (currentTime >= lastTimeFall + 50) {

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
			position.y += 1;
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
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && wallRight == false) {
		if (position.x < 1600 - 24) {
			position.x += speed;
			runningToLeft = true;
			runRight.Reset();
			currentAnimation = &runLeft;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && wallLeft == false) {
		if (position.x > -7) {
			position.x -= speed;
			runningToRight = true;
			runLeft.Reset();
			currentAnimation = &runRight;
		}
	}
	else if (onGround == true) {
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
			position.y -= 1;
		}
		else if (currentTime >= lastTimeJump + 75) {
			position.y -= 2;
		}
		else {
			position.y -= jumpSpeed;
		}
	}

	if (isJumping == true) {
		if (currentAnimation == &runLeft || currentAnimation == &idleLeft) {
			currentAnimation = &jumpLeft;
			runningToLeft = true;
			jumpRight.Reset();
		}
		if (currentAnimation == &runRight || currentAnimation == &idleRight) {
			currentAnimation = &jumpRight;
			runningToRight = true;
			jumpLeft.Reset();
		}
	}
	else {
		//jumpLeft.Reset();
		//jumpRight.Reset();
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && wallRight == false) {
		if (position.x < 1600 - 24) {
			runningToLeft = true;
			runningToRight = false;
			//	runRight.Reset();
				//currentAnimation = &runLeft;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && wallLeft == false) {
		if (position.x > -7) {
			runningToRight = true;
			runningToLeft = false;
			//runLeft.Reset();
			//currentAnimation = &runRight;
		}
	}

	if (position.y >= (app->render->camera.y + app->render->camera.h) / 3) {
		Die();
	}

	if (collider != nullptr)
	{
		collider->SetPos(position.x + 6 - speed, position.y + 14);

	}
	return true;
}

bool Player::PostUpdate()
{
	if (app->titleScreen->inTitle == true) {
		return true;
	}
	currentAnimation->Update();
	return true;
}

void Player::Die() {
	if (lifes > 1) {
		lifes--;
		position = { lastGroundposX,lastGroundposY - 48 };
	}
	else if (lifes <= 1) {
		lifes = 0;
		app->titleScreen->inTitle = 2;
		position = { 0,0 };
	}

}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (godMode == false) {

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GROUND) {

			if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed + 1 && c1->rect.y + c1->rect.h >= c2->rect.y) {
				position.y = c2->rect.y - 48;

				if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { 

					isTouchingLeft = true;
					lastGroundposX = c2->rect.x;
					lastGroundposY = c2->rect.y;
				}

			}

			if (c1->rect.y + c1->rect.h - jumpSpeed != c2->rect.y && isJumping == false) {

				if (c1->rect.x + c1->rect.w - 2 - speed < c2->rect.x && c1->rect.x + c1->rect.w + speed > c2->rect.x) {
					//wallRight = true;
				}

				if (c1->rect.x + 2 + speed > c2->rect.x + c2->rect.w && c1->rect.x - speed < c2->rect.x + c2->rect.w) {
					//wallLeft = true;
				}
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL) {

			if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed + 1 && c1->rect.y + c1->rect.h >= c2->rect.y) {
				//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				position.y = c2->rect.y - 48;

				if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { 

					isTouchingLeft = true;
					lastGroundposX = c2->rect.x;
					lastGroundposY = c2->rect.y;
					//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				}
			}

			if (c1->rect.y + c1->rect.h - jumpSpeed != c2->rect.y) {

				if (c1->rect.y < c2->rect.y) {
					
					if (c1->rect.x + c1->rect.w - 2 - speed < c2->rect.x) {
						wallRight = true;
					}

					if (c1->rect.x + 2 + speed > c2->rect.x + c2->rect.w && c1->rect.x - speed < c2->rect.x + c2->rect.w) {
						wallLeft = true;
					}
				}

			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DEATH) {
			if (true)
			{
				lifes--;
			}
		}
	}
}

bool Player::CleanUp() {
	return true;
}