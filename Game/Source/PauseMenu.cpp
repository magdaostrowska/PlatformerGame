#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	name.Create("PauseMmenu");
	settings_created = false;
	isPauseMenuCreated = false;
	isInGameGuiCreated = false;
	background = nullptr;
	inGameGui = false;
}

bool PauseMenu::Awake(pugi::xml_node& conf)
{

	return true;
}

bool PauseMenu::Start()
{
	return true;
}

bool PauseMenu::Update(float dt)
{
	switch (attribute)
	{
	case PAUSE_MENU:
		if (isPauseMenuCreated == false)CreatePauseMenu();
		break;
	case PAUSE_GUI:
		inGameGui = true;
		if (isInGameGuiCreated == false)CreateInGameGui();
		break;
	case NONE:
		DestroyAllGui();
		break;
	default:
		break;
	}

	return true;
}

bool PauseMenu::CleanUp()
{
	DestroyAllGui();

	return true;
}

void PauseMenu::CreatePauseMenu()
{
	int pos_x = app->player->position.x;
	int pos_y = app->player->position.y;

	// TODO add buttons etc

	isPauseMenuCreated = true;
}

void PauseMenu::DestroyPauseMenu()
{
	// TODO destroy buttons etc
	isPauseMenuCreated = false;
}

void PauseMenu::CreateInGameGui()
{
	//Lifes
	iPoint heartPos[3] = {
		{10, 0}, //heart 1
		{50, 0}, //heart 2
		{90, 0} //heart 3
	};

	for (size_t i = 0; i < app->player->lifes; i++)
	{
		
	}

	//Coins
	iPoint coinPos = { 200, 20 };

	for (size_t i = 0; i < app->player->coins; i++)
	{
		
	}

	isInGameGuiCreated = true;
}

void PauseMenu::DestroyInGameGui()
{
	isInGameGuiCreated = false;
}

void PauseMenu::UpdateInGameGui()
{
	CreateInGameGui();
}

void PauseMenu::DestroyAllGui()
{
	DestroyPauseMenu();
	DestroyInGameGui();
}