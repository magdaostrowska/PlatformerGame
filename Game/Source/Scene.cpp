#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
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
	app->map->Load("map_no_back.tmx");
	back1 = app->tex->Load("Assets/Textures/back_image.png");
	back_pos = { 0,0 };
	//app->map->Load("map_1.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
    // Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

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

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;
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