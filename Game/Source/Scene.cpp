#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Fonts.h"
#include "Title.h"
#include "WalkingEnemy.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>

Scene::Scene() : Module()
{
	name.Create("scene");
	level = 1;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// Loading map

	if (level == 1)
	{
		app->enemies->CreateEnemy(Enemy_Type::WALKING_ENEMY, 0, 0);
		app->map->Load("map_level1.tmx");
		back1 = app->tex->Load("Assets/textures/back_image.png");
	}
	else if (level == 2)
	{
		app->map->Load("map_level2.tmx");
		back1 = app->tex->Load("Assets/textures/back_image2.png");
	}

	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFont = app->fonts->Load("Assets/fonts/pixel_font.png", lookupTableChars, 8);

	back_pos = { 0,0 };
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		loadinglvl1 = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) 
	{
		loadinglvl2 = true;	
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		if (level == 1)
		{
			app->player->position.x = 0;
			app->player->position.y = 0;
		}
		else if (level == 2) {
			app->player->position.x = 0;
			app->player->position.y = 180;
		}
	}
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	if (loadinglvl1 == true) {
		app->fade->Fade(120, 1);
		if (app->fade->frameCount >= 120 / 2) {
			level = 1;
			app->map->RemoveCol();
			app->map->CleanUp();

			app->map->Load("map_level1.tmx");
			app->tex->UnLoad(back1);
			back1 = app->tex->Load("Assets/textures/back_image.png");
			//app->player->Spawn();
			app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
			app->map->LoadCol();
			loadinglvl1 = false;
		}
	}

	if (loadinglvl2 == true) {
		app->fade->Fade(120, 1);
		if (app->fade->frameCount >= 120 / 2) {
			level = 2;
			app->map->RemoveCol();
			app->map->CleanUp();

			app->map->Load("map_level2.tmx");
			app->tex->UnLoad(back1);
			back1 = app->tex->Load("Assets/textures/back_image2.png");
			//app->player->Spawn();
			app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
			app->map->LoadCol();
			loadinglvl2 = false;
		}
	}

	if (app->player->position.x > 1504 && app->player->position.y == 148) {
		if (level == 1) {
			app->fade->Fade(120, 1);
			if (app->fade->frameCount >= 120 / 2) {
				level = 2;
				app->map->RemoveCol();
				app->map->CleanUp();

				app->map->Load("map_level2.tmx");
				app->tex->UnLoad(back1);
				back1 = app->tex->Load("Assets/textures/back_image2.png");
				//app->player->Spawn();
				app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
				app->map->LoadCol();
			}
		}
	}

	if (app->player->position.x > 1504 && app->player->position.y == 180) {
		if(level == 2 && app->titleScreen->inTitle !=3) {
			app->fade->Fade(120,0);
			if (app->fade->frameCount >= app->fade->maxFadeFrames) {
				app->titleScreen->inTitle = 3;
			}
			
		}
	}
    // Request Load when pressing L
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	//Save when pressing F5
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	//Load the previous state (even across levels)
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		app->LoadGameRequest();
		app->player->loadingPos = 1;
	}

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		app->render->camera.y += (int)(100 * dt);

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		app->render->camera.y -= (int)(100 * dt);

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		app->render->camera.x += (int)(100 * dt);

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		app->render->camera.x -= (int)(100 * dt);

	//for (int i = 0; i <= app->render->camera.x; i++){
	//	back_pos.x = i * 2;
	//}

	back_pos.x = app->render->camera.x/40;
	
	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->titleScreen->inTitle == 1) {
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 220 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 220 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - 20 / 2) - (app->render->camera.y - (app->render->camera.h / 2 - 20 / 2)) * 2) / app->win->GetScale()), textFont, "PLATVENTURE");
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 400 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 400 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - (20 / 2) + 20) - (app->render->camera.y - (app->render->camera.h / 2 - (20 / 2) + 20)) * 2) / app->win->GetScale()), textFont, "PRESS ENTER TO START");
		return true;
	}
	else if(app->titleScreen->inTitle == 2){
		
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 180 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 180 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - 20 / 2) - (app->render->camera.y - (app->render->camera.h / 2 - 20 / 2)) * 2) / app->win->GetScale()), textFont, "GAME OVER");
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 480 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 480 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - (20 / 2) + 20) - (app->render->camera.y - (app->render->camera.h / 2 - (20 / 2) + 20)) * 2) / app->win->GetScale()), textFont, "PRESS ENTER TO TRY AGAIN");
		return true;
		
	}
	else if (app->titleScreen->inTitle == 3) {

		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 300 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 300 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - 20 / 2) - (app->render->camera.y - (app->render->camera.h / 2 - 20 / 2)) * 2) / app->win->GetScale()), textFont, "CONGRATULATIONS");
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 620 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 620 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - (20 / 2) + 20) - (app->render->camera.y - (app->render->camera.h / 2 - (20 / 2) + 20)) * 2) / app->win->GetScale()), textFont, "PRESS ENTER TO START A NEW GAME");

		return true;

	}

	app->render->DrawTexture(back1, back_pos.x, back_pos.y, &rectMap, 1.0f);

	// Draw map
	app->map->Draw();

	app->player->rectPlayer = app->player->currentAnimation->GetCurrentFrame();

	if (app->player->currentAnimation == &app->player->idleLeft) {
		app->render->DrawTexture(app->player->textureIdleLeft, app->player->position.x, app->player->position.y, &app->player->rectPlayer, 1.0f);
	}
	else if (app->player->currentAnimation == &app->player->idleRight) {
		app->render->DrawTexture(app->player->textureIdleRight, app->player->position.x - 19, app->player->position.y, & app->player->rectPlayer, 1.0f);
	}
	else if (app->player->currentAnimation == &app->player->runLeft) {
		app->render->DrawTexture(app->player->textureRunLeft, app->player->position.x, app->player->position.y, &app->player->rectPlayer, 1.0f);
	}
	else if (app->player->currentAnimation == &app->player->runRight) {
		app->render->DrawTexture(app->player->textureRunRight, app->player->position.x - 19, app->player->position.y, &app->player-> rectPlayer, 1.0f);
	}
	else if (app->player->currentAnimation == &app->player->jumpLeft) {
		app->render->DrawTexture(app->player->textureJumpLeft, app->player->position.x, app->player->position.y, &app->player->rectPlayer, 1.0f);
	}
	else if (app->player->currentAnimation == &app->player->jumpRight) {
		app->render->DrawTexture(app->player->textureJumpRight, app->player->position.x - 19, app->player->position.y, &app->player->rectPlayer, 1.0f);
	}
	sprintf_s(playerLifes, 2, "%01d", app->player->lifes);
	
	blackRect = { 0, (app->render->camera.y - app->render->camera.y * 2) / 3, app->render->camera.w,( app->win->screenSurface->h / 2 - 324 * 3 / 2)/3 };
	app->render->DrawRectangle(blackRect, 0, 0, 0, 255, true);
	blackRect2 = { 0, (app->render->camera.y - app->render->camera.y * 2) / 3 + (app->win->screenSurface->h / 2 - 324 * 3 / 2) / 3 + 324, app->render->camera.w,(app->win->screenSurface->h / 2 - 324 * 3 / 2) / 3 };
	app->render->DrawRectangle(blackRect2, 0, 0, 0, 255, true);

	//app->fonts->BlitText(((app->player->position.x - app->player->position.x * 2) * app->win->GetScale()) + (app->win->screenSurface->w / 2 - 24 * app->win->GetScale()) , 0, textFont,"Lifes:");
	//app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (180 / 2) / app->win->GetScale()) - (app->render->camera.x - (app->render->camera.w / 2 - (180 / 2) / app->win->GetScale())) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "Lifes:");

	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 140/2) - (app->render->camera.x - (app->render->camera.w / 2 - 140/2)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "Lifes: ");
	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (180 / 2) / app->win->GetScale()) - (app->render->camera.x - (app->render->camera.w / 2 - (180 / 2) / app->win->GetScale())) * 2) / app->win->GetScale()) + 240 / app->win->GetScale(), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, playerLifes);

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		ret = false;
	}

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Scene::SaveState(pugi::xml_node& data) const
{
	data.child("level").attribute("level").set_value(1);
	return true;
}
