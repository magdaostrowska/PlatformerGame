#include "GuiManager.h"
#include "App.h"
#include "Textures.h"

#include "GuiButton.h"
#include "Audio.h"
#include "Title.h"

GuiManager::GuiManager() :Module()
{
	name.Create("GuiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds)
{
	// Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text);
		break;

		// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer

	control->SetObserver(observer);
	//control->SetTexture(texture);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);

	return control;
}

bool GuiManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}
	}
	return true;

}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		if (app->titleScreen->inTitle == 0) {

			if (control->data->id == 3)
			{
				control->data->Draw(app->render);
				int u = 7;
			}

		}
		else if (app->titleScreen->inTitle == 1) {



			if (control->data->id == 1)
			{
				control->data->Draw(app->render);
			}

			if (control->data->id == 2)
			{
				control->data->Draw(app->render);
			}

		}

		//control->data->Draw(app->render);
		control = control->next;
	}

	return true;
}

bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;
}