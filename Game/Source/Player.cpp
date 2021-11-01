#include "Player.h"

Player::Player() : Module()
{

	lifes = 3;

	speed = 1;
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

	jumpLeft.PushBack({ 0, 0, 48, 48 });
	jumpLeft.PushBack({ 48, 0, 48, 48 });
	jumpLeft.PushBack({ 96, 0, 48, 48 });
	jumpLeft.PushBack({ 144, 0, 48, 48 });

	jumpLeft.loop = false;
	jumpLeft.speed = 0.05;

	jumpRight.PushBack({ 144, 0, 48, 48 });
	jumpRight.PushBack({ 96, 0, 48, 48 });
	jumpRight.PushBack({ 48, 0, 48, 48 });
	jumpRight.PushBack({ 0, 0, 48, 48 });



	jumpRight.loop = false;
	jumpRight.speed = 0.05;

}

Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config) {

	bool ret = true;
	config = app->GetConfig();
	lifes = config.child("lifes").attribute("value").as_int();
	document.load_file("config.xml");
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
	position = { 0,0 };
	collider = app->collisions->AddCollider({ position.x + 7 - speed, position.y + 14, 15 + 2 + 2 * speed, 34 + jumpSpeed }, Collider::Type::PLAYER, this);

	lastTimeFall = SDL_GetTicks();
	lastTimeJump = SDL_GetTicks();

	return true;
}

void Player::spawn(int lvl) {

}

bool Player::PreUpdate() {

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

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		position = { 1500,0 };
	}

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		position = { 0,0 };
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
	//isTouchingLeft = false;
	//isTouchingRight = false;



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
	/*else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		position.y -= speed;
		runningToLeft = true;
		runRight.Reset();
		currentAnimation = &runLeft;
		onGround = false;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && onGround == false) {
		position.y += speed;
		runningToLeft = true;
		runRight.Reset();
		currentAnimation = &runLeft;
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
	}*/

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

	if (isJumping == true ) {
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

	collider->SetPos(position.x + 6 - speed, position.y + 14);

	return true;
}

bool Player::PostUpdate()
{

	

	currentAnimation->Update();
	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{


	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GROUND) {

		//if (heightOnGround == NULL) {
		//heightOnGround = c2->rect.y;//position.y;
		//weightOnWall = c2->rect.x;
		//}
		//if (app->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT) {
		/*
		if (((c1->rect.y + c1->rect.h) <= c2->rect.y + 6) && ((c1->rect.y + c1->rect.h) >= c2->rect.y + 1) && (c1->rect.x + c1->rect.w - 2) > c2->rect.x) {
			position.y = heightOnGround - 47;
			onGround = true;
		}
		else if (((c1->rect.y + c1->rect.h-jumpSpeed+1) < c2->rect.y)|| ((c1->rect.x +1 ) >= c2->rect.x+c2->rect.w) ||
			(((c1->rect.x + c1->rect.w -2) <= c2->rect.x ) && (c1->rect.y + c1->rect.h-jumpSpeed-1) == c2->rect.y)){
			//position.y = heightOnGround - 47;
			onGround = false;
			lastTimeFall = currentTime;
		}
		else {
			//onGround = false;
			//lastTimeFall = currentTime;
		}
		*/
		//SI ESTA PISANDO EL SUELO
		//isTouchingLeft = false;
		//isTouchingRight = false;
		//wallRight = false;

		if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed && c1->rect.y + c1->rect.h >= c2->rect.y) {
			//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
			position.y = c2->rect.y - 48;

			/*/
			if ((c1->rect.x + c1->rect.w - 2 > c2->rect.x) || (c1->rect.x + 2 < c2->rect.x + c2->rect.w)) {

				c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				onGround = true;
			}
			//else if()
		}*/

		//HACE QUE NO SE ENGANCHE A LA PARED DE LA IZQUIERDA
			if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { //&& c2->rect.x<=c1->rect.x) {

				isTouchingLeft = true;
				//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
			}

			/*
			if (c1->rect.x + c1->rect.w - 3 > c2->rect.x) {
				//isTouchingRight = true;
				//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
			}


/*
			if (c2->rect.x < c1->rect.x && c2->rect.x + c2->rect.w>c1->rect.x) {
				isTouchingLeft = true;
			}

			if (c2->rect.x<c1->rect.x && c2->rect.x + c2->rect.w>c1->rect.x) {
				isTouchingLeft = true;
			}

			if (c2->rect.x > c1->rect.x && c2->rect.x + c2->rect.w > c1->rect.x) {
				isTouchingLeft = true;
			}
			*/
			//SUELO A LA DERECHA
			/*
			if (c1->rect.x<=c2->rect.x) {
				if (c1->rect.x+c1->rect.w-speed>=c2->rect.x) {
					//isTouchingLeft = true;
					//isTouchingLeft = true;
				}
				else {

				}
				//isTouchingLeft = true;

			}
			//SUELO A LA IZQUIERDA
			if (c1->rect.x >= c2->rect.x) {
				if (c2->rect.x+c2->rect.w-speed<c1->rect.x) {

				}
				else {
					//isTouchingLeft = true;
					//isTouchingLeft = true;
				}

			}
			*/

			//if (c1->rect.x + c1->rect.w > c2->rect.x ) {
		//		isTouchingRight = true;
			//	c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
		//	}

		}

		if (c1->rect.y + c1->rect.h - jumpSpeed != c2->rect.y && isJumping == false) {
			//if(position.y <= c2->rect.y - 45 && position.y >= c2->rect.y - 47){

			if (c1->rect.x + c1->rect.w - 2 - speed < c2->rect.x && c1->rect.x + c1->rect.w + speed > c2->rect.x) {
				//wallRight = true;
			}

			if (c1->rect.x + 2 + speed > c2->rect.x + c2->rect.w && c1->rect.x - speed < c2->rect.x + c2->rect.w) {
				//wallLeft = true;
			}


		}


		//if(c1->rect.x)

			/*
			if (sumPlat == false) {
				if (numPlat == 0) {
					numPlat = 1;
				}
				else if (numPlat == 1) {
					numPlat = 2;
				}
			}
			*/
			/*
			if (c1->rect.x + c1->rect.w - 2 < c2->rect.x) {
				//onGround = false;
				//sumPlat = false;
				isTouchingLeft = false;
				isTouchingRight = false;
			//	if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) {
			//		isTouchingRight = false;
			//	}
				//onGround = true;
			}
			else if(c1->rect.x + 2 > c2->rect.x + c2->rect.w) {
				//onGround = false;
				//sumPlat = false;
				isTouchingRight = false;
				isTouchingLeft = false;

				//isTouchingLeft = true;
			}
			else {
				c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				//onGround = true;
				if (c1->rect.x>c2->rect.x) {
					//isTouchingLeft = true;
				}
				isTouchingLeft = true;
				isTouchingRight = true;
				if (c1->rect.x < c2->rect.x) {
					//isTouchingRight = true;
				}
				//isTouchingLeft = false;
				//sumPlat = true;



			}



		}
		/*
		if (((c1->rect.x + c1->rect.w  -1-speed) == c2->rect.x) && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) { //&& (c1->rect.x + c1->rect.w  >= c2->rect.x) && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) {
		position.x = weightOnWall-23;
		//position.x = c2->rect.x + -rectPlayer.w +23 ;
		//isTouchingRight = true;
		}
		else if (((c1->rect.x + c1->rect.w -speed) <= c2->rect.x)){// && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) {
			//position.x = weightOnWall - 23;
			//isTouchingRight = false;
		}


		if (((c1->rect.x) == c2->rect.x+c2->rect.w-1-speed) && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) { //&& (c1->rect.x + c1->rect.w  >= c2->rect.x) && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) {

			position.x = c2->rect.x + c2->rect.w+6+speed ;
			//isTouchingLeft = true;
		}
		else if (((c1->rect.x ) >= c2->rect.x+c2->rect.w - speed)) {// && (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h)) {
			//isTouchingLeft = false;
		}

		/*
		else if (((c1->rect.y + c1->rect.h) <= c2->rect.y + 6) && ((c1->rect.y + c1->rect.h) >= c2->rect.y + 1)) {
			position.y = heightOnGround - 47;
			onGround = true;
		}
		else {
			onGround = false;
			lastTimeFall = currentTime;
		}
		//}
		//else {
		//	position.y = heightOnGround - 48;
		//}
		*/

	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL) {

		

		if (c1->rect.y + c1->rect.h <= c2->rect.y + jumpSpeed && c1->rect.y + c1->rect.h >= c2->rect.y) {
			//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
			position.y = c2->rect.y - 48;

			/*/
			if ((c1->rect.x + c1->rect.w - 2 > c2->rect.x) || (c1->rect.x + 2 < c2->rect.x + c2->rect.w)) {

				c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
				onGround = true;
			}
			//else if()
		}*/

		//HACE QUE NO SE ENGANCHE A LA PARED DE LA IZQUIERDA
			if (c1->rect.x + 1 < c2->rect.x + c2->rect.w && c1->rect.x + c1->rect.w - 1 > c2->rect.x) { //&& c2->rect.x<=c1->rect.x) {

				isTouchingLeft = true;
				//c1->rect.y = c2->rect.y - c1->rect.h + jumpSpeed;
			}

		
		}

		if (c1->rect.y + c1->rect.h - jumpSpeed != c2->rect.y && isJumping == false && onGround == true) {
			//if(position.y <= c2->rect.y - 45 && position.y >= c2->rect.y - 47){

			if (c1->rect.x + c1->rect.w - 2 - speed < c2->rect.x && c1->rect.x + c1->rect.w + speed > c2->rect.x) {
				wallRight = true;
			}

			if (c1->rect.x + 2 + speed > c2->rect.x + c2->rect.w && c1->rect.x - speed < c2->rect.x + c2->rect.w) {
				wallLeft = true;
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


bool Player::CleanUp() {
	return true;
}

