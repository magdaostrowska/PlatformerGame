#include "App.h"
#include "Title.h"
#include "Input.h"
#include "SDL/include/SDL.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Textures.h"
#include "Map.h"

Title::Title() : Module()
{
	name.Create("title");
}

Title::~Title()
{

}

bool Title::Awake() {

	
	return true;
}
bool Title::Start()
{
	intro_image = app->tex->Load("Assets/textures/intro_image.png");
	inTitle = 1;
	return true;
}

bool Title::Update(float dt)
{
	//TITULO
	if (inTitle == 1) {

		//app->render->DrawTexture(intro_image, 0,0);

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			app->fade->Fade(240, 1);
			inTitle = 0;
		}
	}
	//REINICIO
	if (inTitle == 2) {
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			//app->fade->Fade(240, 1);
			//inTitle = 0;
			//app->player->Spawn(app->player->playerInfo); //ELIMINAR LO DE ABAJO
			//app->player->position.x = app->player->position.y = 0;
			//app->player->lifes = 3;
			app->map->RemoveCol();
			app->map->CleanUp();

			app->map->Load("map_level1.tmx");
			app->tex->UnLoad(app->scene->back1);
			app->scene->back1 = app->tex->Load("Assets/textures/back_image.png");
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->ReSpawn();
			//app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
			//app->player->lifes = 3;//borrar al poner spawn
			app->map->LoadCol();
			app->fade->Fade(240, 1);
			inTitle = 0;
			
		}
	}
	//FELICIDADES
	if (inTitle == 3) {
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			app->scene->level = 1;
			app->map->RemoveCol();
			app->map->CleanUp();

			app->map->Load("map_level1.tmx");
			app->tex->UnLoad(app->scene->back1);
			app->scene->back1 = app->tex->Load("Assets/textures/back_image.png");
			app->entity->FindEntity(EntityType::PLAYER)->FindSubClassPlayer()->ReSpawn();
			app->map->LoadCol();
			app->fade->Fade(240, 1);
			inTitle = 0;

		}
	}
	return true;
}

bool Title::PostUpdate()
{
	return true;
}

bool Title::CleanUp()
{
	return true;
}