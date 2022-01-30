#ifndef __TITLE_H__
#define __TITLE_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Texture;

class Title : public Module
{
public:

	Title();

	virtual ~Title();

	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	int inTitle=0;

	SDL_Texture* intro_image = nullptr;

	bool toExit = false;

	GuiButton* btn1;
	GuiButton* btn2;
	GuiButton* btn3;

private:
	//int textFont = -1;

};

#endif // __TITLE_H__