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
#include "Items.h"
#include "Enemies.h"
#include "PathFinding.h"
#include "Player.h"

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
		app->map->Load("map_level1.tmx");
		back1 = app->tex->Load("Assets/textures/back_image.png");
	}
	else if (level == 2)
	{
		app->map->Load("map_level2.tmx");
		back1 = app->tex->Load("Assets/textures/back_image_2.png");
	}

	int w, h;
	uchar* data = NULL;

	//pathfinding
	if (app->map->CreateWalkabilityMap(w, h, &data))
		app->pathfinding->SetMap(w, h, data);

	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFont = app->fonts->Load("Assets/fonts/pixel_font.png", lookupTableChars, 8);

	back_pos = { 0,0 };
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		//if (level == 2) {
			loadinglvl1 = true;
		//}
		
	}

	

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		
		loadinglvl2 = true;
		
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		if (level == 1)
		{
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x = 0;
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y = 0;

		}
		else if (level == 2) {
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x = 0;
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y = 180;

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
			//app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
			app->map->LoadCol();
			loadinglvl1 = false;
		}
	}

	if (loadinglvl2 == true) {
		app->fade->Fade(120, 1);
		if (app->fade->frameCount >= 120 / 2) {
			level = 2;
			app->map->RemoveCol();
			app->entity->FindEntity(EntityType::ENEMY)->FindSubClassEnemy()->removeAll = true;
			app->entity->FindEntity(EntityType::ITEM)->FindSubClassItem()->removeAll = true;
			app->map->CleanUp();

			app->map->Load("map_level2.tmx");
			app->tex->UnLoad(back1);
			back1 = app->tex->Load("Assets/textures/back_image_2.png");
			//app->player->Spawn();
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x = app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y = 0; //borrar al poner spawn
			app->map->LoadCol();
			loadinglvl2 = false;
		}
	}

	//LOG( "numero X: %d", app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x);
	//LOG("numero Y: %d", app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y);

	if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x > 1504 && app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y == 148) {

		if (level == 1) {
			app->fade->Fade(120, 1);
			if (app->fade->frameCount >= 120 / 2) {
				level = 2;
				app->map->RemoveCol();
				app->map->CleanUp();
				app->entity->FindEntity(EntityType::ENEMY)->FindSubClassEnemy()->removeAll = true;
				app->entity->FindEntity(EntityType::ITEM)->FindSubClassItem()->removeAll = true;
				app->map->Load("map_level2.tmx");
				app->tex->UnLoad(back1);
				back1 = app->tex->Load("Assets/textures/back_image_2.png");
				//app->player->Spawn();
				app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x = app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y = 0; //borrar al poner spawn
				app->map->LoadCol();
			}
		}
	}

	if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x > 1504 && app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y == 180) {
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
		app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->loadingPos = 1;
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

	// Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	//app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->titleScreen->inTitle == 1) {
		app->render->DrawTexture(app->titleScreen->intro_image, 80, 30);
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 220 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 220 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - 20 / 2) - (app->render->camera.y - (app->render->camera.h / 2 - 20 / 2)) * 2) / app->win->GetScale()), textFont, "PLATVENTURE");
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 400 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 400 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - (20 / 2) + 20) - (app->render->camera.y - (app->render->camera.h / 2 - (20 / 2) + 20)) * 2) / app->win->GetScale()), textFont, "PRESS ENTER TO START");
		//app->guiManager->Draw();
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
	
	app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer = app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation->GetCurrentFrame();

	if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->idleLeft) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureIdleLeft, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->idleRight) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureIdleRight, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x - 19, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, & app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->runLeft) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureRunLeft, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->runRight) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureRunRight, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x - 19, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()-> rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->jumpLeft) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureJumpLeft, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->jumpRight) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureJumpRight, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x - 19, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hurtLeft) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureHitLeft, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x - 19, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->hurtRight) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureHitRight, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x , app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->deathLeft) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureDeathLeft, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x - 19, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}
	else if (app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->currentAnimation == &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->deathRight) {
		app->render->DrawTexture(app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->textureDeathRight, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.x, app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->position.y, &app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->rectPlayer, 1.0f);
	}

	//app->render->DrawTexture(app->items->textureRunLeft, app->, app->player->position.y, &app->player->rectPlayer, 1.0f);

	sprintf_s(playerLifes, 2, "%01d", app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->lifes);
	sprintf_s(playerCoins, 2, "%01d", app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->coins);
	
	blackRect = { 0, (app->render->camera.y - app->render->camera.y * 2) / 3, app->render->camera.w,( app->win->screenSurface->h / 2 - 324 * 3 / 2)/3 };
	app->render->DrawRectangle(blackRect, 0, 0, 0, 255, true);
	blackRect2 = { 0, (app->render->camera.y - app->render->camera.y * 2) / 3 + (app->win->screenSurface->h / 2 - 324 * 3 / 2) / 3 + 324, app->render->camera.w,(app->win->screenSurface->h / 2 - 324 * 3 / 2) / 3 };
	app->render->DrawRectangle(blackRect2, 0, 0, 0, 255, true);

	//app->fonts->BlitText(((app->player->position.x - app->player->position.x * 2) * app->win->GetScale()) + (app->win->screenSurface->w / 2 - 24 * app->win->GetScale()) , 0, textFont,"Lifes:");
	//app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (180 / 2) / app->win->GetScale()) - (app->render->camera.x - (app->render->camera.w / 2 - (180 / 2) / app->win->GetScale())) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "Lifes:");

	//app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - 19*20 /2) - (app->render->camera.x - (app->render->camera.w / 2 - 19*20/2)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "Lifes: ");
	//app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (19*20 / 2) / app->win->GetScale()) - (app->render->camera.x - (app->render->camera.w / 2 - (19*20 / 2) / app->win->GetScale())) * 2) / app->win->GetScale()) - 7*20 / app->win->GetScale(), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, playerLifes);

	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (17 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (17 * 20) / 2)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "Lifes:");
	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (17 * 20) / 2 + 6*20) - (app->render->camera.x - (app->render->camera.w / 2 - (17 * 20) / 2 + 6 * 20)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, playerLifes);

	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (17 * 20) / 2 + 7 * 20) - (app->render->camera.x - (app->render->camera.w / 2 - (17 * 20 ) / 2 + 7 * 20)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, "   Coins:");
	app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (17 * 20) / 2 + 16 * 20) - (app->render->camera.x - (app->render->camera.w / 2 - (17 * 20) / 2 + 16 * 20)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / app->win->GetScale(), textFont, playerCoins);

	if (level == 2) {
		app->fonts->BlitText((((app->render->camera.x - app->render->camera.w / 2 - (12 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (12 * 20) / 2)) * 2) / app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2 + 50) / app->win->GetScale(), textFont, "Coming soon!");

	}

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
