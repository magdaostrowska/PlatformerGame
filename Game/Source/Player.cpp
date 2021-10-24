#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "Collisions.h"

Player::Player() : Module()
{
	idleLeft.PushBack({ 0, 0, 48, 48 });
	idleLeft.PushBack({ 48, 0, 48, 48 });
	idleLeft.PushBack({ 96, 0, 48, 48 });
	idleLeft.PushBack({ 144, 0, 48, 48 });

	idleLeft.loop = true;
	idleLeft.speed = 0.025;

	idleRight.PushBack({ 144, 0, 48, 48 });
	idleRight.PushBack({ 96, 0, 48, 48 });
	idleRight.PushBack({ 48, 0, 48, 48 });
	idleRight.PushBack({ 0, 0, 48, 48 });

	idleRight.loop = true;
	idleRight.speed = 0.025;

	runLeft.PushBack({ 0, 0, 48, 48 });
	runLeft.PushBack({ 48, 0, 48, 48 });
	runLeft.PushBack({ 96, 0, 48, 48 });
	runLeft.PushBack({ 144, 0, 48, 48 });
	runLeft.PushBack({ 192, 0, 48, 48 });
	runLeft.PushBack({ 240, 0, 48, 48 });

	runLeft.loop = true;
	runLeft.speed = 0.05;

	runRight.PushBack({ 240, 0, 48, 48 });
	runRight.PushBack({ 192, 0, 48, 48 });
	runRight.PushBack({ 144, 0, 48, 48 });
	runRight.PushBack({ 96, 0, 48, 48 });
	runRight.PushBack({ 48, 0, 48, 48 });
	runRight.PushBack({ 0, 0, 48, 48 });
	
	runRight.loop = true;
	runRight.speed = 0.05;
}

Player::~Player()
{}

bool Player::Start()
{
	//texture = App->textures->Load("Assets/Textures/spritesheet_player.png");
	textureIdleLeft = app->tex->Load("Assets/Textures/Punk_idle_left.png");
	textureRunLeft = app->tex->Load("Assets/Textures/Punk_run_left.png");
	textureIdleRight = app->tex->Load("Assets/Textures/Punk_idle_right.png");
	textureRunRight = app->tex->Load("Assets/Textures/Punk_run_right.png");
	//idleLeft.Reset();
	currentAnimation = &idleLeft;
	position = { 0,0 };
	collider = app->collisions->AddCollider({ position.x+7, position.y+14, 15, 34+1 }, Collider::Type::PLAYER, this);
	return true;
}

void Player::spawn(int lvl) {

}

bool Player::Update(float dt)
{
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}

	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
		position.x += speed;
		runningToLeft = true;
		runRight.Reset();
		currentAnimation = &runLeft;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= speed;
		runningToRight = true;
		runLeft.Reset();
		currentAnimation = &runRight;
	}
	else {
		if (runningToRight == true) {
			runningToRight = false;
			idleRight.Reset();
			currentAnimation = &idleRight;
		}
		else if(runningToLeft == true){
			runningToLeft = false;
			idleLeft.Reset();
			currentAnimation = &idleLeft;
		}
		
		
	}

	

	collider->SetPos(position.x + 7, position.y + 14);

	return true;
}

bool Player::PostUpdate()
{
	rectPlayer = currentAnimation->GetCurrentFrame();
	
	if (currentAnimation == &idleLeft) {
		app->render->DrawTexture(textureIdleLeft, position.x, position.y, &rectPlayer, 1.0f);
	}
	else if (currentAnimation == &idleRight) {
		app->render->DrawTexture(textureIdleRight,position.x -19, position.y, &rectPlayer, 1.0f);
	}
	else if (currentAnimation == &runLeft) {
		app->render->DrawTexture(textureRunLeft, position.x, position.y, &rectPlayer, 1.0f);
	}
	else if (currentAnimation == &runRight) {
		app->render->DrawTexture(textureRunRight, position.x - 19, position.y, &rectPlayer, 1.0f);
	}
	
	currentAnimation->Update();
	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{

}

bool Player::CleanUp() {

	return true;
}

