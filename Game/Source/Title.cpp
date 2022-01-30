#include "App.h"
#include "Title.h"
#include "Input.h"
#include "SDL/include/SDL.h"
#include "FadeToBlack.h"
#include "Player.h"
#include "Textures.h"
#include "Map.h"
#include "GuiManager.h"

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
	

	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (((app->render->camera.x - app->render->camera.w / 2 - 150 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 150 / 2)) * 2) / (int)app->win->GetScale()), 150, 150, 50 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (((app->render->camera.x - app->render->camera.w / 2 - 110 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 110 / 2)) * 2) / (int)app->win->GetScale()), 230, 110, 40 }, this);
	
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test3", { 5, 5,  20, 20 }, this);

	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (((app->render->camera.x - app->render->camera.w / 2 - 400 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 400 / 2)) * 2) / (int)app->win->GetScale()), -90, 160, 40 }, this);

	//btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", {30, 30, 160, 40 }, this);
	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { 300, 300, 160, 40 }, this);

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
	bool ret = true;
	if (toExit == true) {
		ret = false;
	}
	return ret;
}

bool Title::CleanUp()
{
	return true;
}

bool Title::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (inTitle == 0) {

			if (control->id == 3)
			{
				if (app->scene->inPause == true) {
					app->scene->inPause = false;
				}
				else {
					app->scene->inPause = true;
				}
				
			}
			
		}
		else if (inTitle == 1) {

			

			if (control->id == 1)
			{
				app->fade->Fade(240, 1);
				inTitle = 0;
			}

			if (control->id == 2)
			{
				toExit = true;
			}

		}
		

	}
	//Other cases here

	default: break;
	}

	return true;
}