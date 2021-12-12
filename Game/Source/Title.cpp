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
	inTitle = 1;
	return true;
}

bool Title::Update(float dt)
{
	if (inTitle == 1) {
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			app->fade->Fade(240, 1);
			inTitle = 0;
		}
	}
	if (inTitle == 2) {
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			app->fade->Fade(240, 1);
			inTitle = 0;
			//app->player->Spawn(); //ELIMINAR LO DE ABAJO
			app->player->position.x = app->player->position.y = 0;
			app->player->lifes = 3;
			
		}
	}
	if (inTitle == 3) {
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			app->scene->level = 1;
			app->map->RemoveCol();
			app->map->CleanUp();

			app->map->Load("map_level1.tmx");
			app->tex->UnLoad(app->scene->back1);
			app->scene->back1 = app->tex->Load("Assets/textures/back_image.png");
			//app->player->Spawn();
			app->player->position.x = app->player->position.y = 0; //borrar al poner spawn
			app->player->lifes = 3;//borrar al poner spawn
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