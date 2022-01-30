#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "Module.h"
#include "Textures.h"
#include "App.h"
#include "Player.h"
#include "GuiButton.h"
#include "Globals.h"
#include "Audio.h"
#include "Log.h"
#include "PugiXml/src/pugixml.hpp"

class PauseMenu : public Module {

public:

	PauseMenu(iPoint position);
	~PauseMenu();
	
	bool Update(float dt) override;
	bool CleanUp() override;

	bool Draw();
	bool Event(GuiControl* control);

	void AbleDisableSetting();
	void AbleDisableMenu();

	void CloseSettingsMenu();

private:

	SDL_Rect screenRect = { NULL };
	GuiButton* resumeButton;
	GuiButton* settingsButton;
	GuiButton* backToTitleButton;
	GuiButton* exitButton;

	//TODO: GuiSettings* settingsMenu;

	int padding;
	bool isActive, isPauseMenuActive;
};


#endif // !__PAUSEMENU_H__