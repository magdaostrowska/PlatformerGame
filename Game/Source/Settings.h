#ifndef __GUISETTINGS_H__
#define __GUISETTINGS_H__

#include "Point.h"
#include "SString.h"
#include "GuiButton.h"
//#include "GuiCheckBox.h"
#include "GuiSlider.h"

class Settings
{
public:

	Settings(iPoint Position /*, SceneControl* moduleObserver*/);
	~Settings();

	bool Update(float dt);
	bool Draw();
	bool CleanUp();

	void ChangePosition();

	void ChangeSettings();
	bool GetActiveSettings();

	GuiSlider* sldMusic;
	GuiSlider* sldFx;
	//GuiCheckBox* chBxFullScreen;
	//GuiCheckBox* chBxVSync;

	GuiButton* backButton;

private:

	iPoint initialPosition;
	int padding;// = 100;
	bool isActive;

};
#endif // __GUISETTINGS_H__