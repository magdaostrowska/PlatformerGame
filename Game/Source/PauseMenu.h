#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "Module.h"
#include "Textures.h"
#include "App.h"
#include "Player.h"
#include "PugiXml/src/pugixml.hpp"

enum MenuAttributes
{
	PAUSE_MENU,
	PAUSE_GUI,
	NONE,
};

class PauseMenu : public Module {

public:
	PauseMenu();
	~PauseMenu();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void CreatePauseMenu();
	void DestroyPauseMenu();

	void CreateInGameGui();
	void DestroyInGameGui();
	void UpdateInGameGui();

	void DestroyAllGui();

public:

	MenuAttributes attribute;
	bool inGameGui;


private:

	SDL_Texture* background;
	bool settings_created;
	bool isPauseMenuCreated;
	bool isInGameGuiCreated;

	//ListItem<*> screen_ui;
};


#endif // !__PAUSEMENU_H__