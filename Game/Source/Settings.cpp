#include "Settings.h"
#include "App.h"

Settings::Settings(iPoint Position)
{
	initialPosition = Position;
	padding = 100;
	isActive = false;
}

Settings::~Settings()
{
}

bool Settings::Update(float dt)
{
	if (isActive)
	{
		/*musicSlider->Update(dt);
		fxSlider->Update(dt);
		fullscreenCheckbox->Update(dt);
		VSyncCheckbox->Update(dt);*/
		backButton->Update(dt);
	}

	return true;
}

bool Settings::Draw()
{
	if (isActive)
	{
		/*musicSlider->Update(dt);
		fxSlider->Update(dt);
		fullscreenCheckbox->Update(dt);
		VSyncCheckbox->Update(dt);*/
		//backButton->Draw();
	}

	return true;
}

bool Settings::CleanUp()
{
	isActive = false;

	/*delete musicSlider;
	delete fxSlider;
	delete fullscreenCheckbox;
	delete VSyncCheckbox;*/
	delete backButton;

	/*musicSlider = NULL;
	fxSlider = NULL;
	fullscreenCheckbox = NULL;
	VSyncCheckbox = NULL;*/
	backButton = NULL;

	return true;
}

void Settings::ChangePosition()
{
	int x = initialPosition.x - app->render->camera.x;
	int y = initialPosition.y - app->render->camera.y;

	/*musicSlider->bounds.x = x;
	musicSlider->bounds.y = y;

	fxSlider->bounds.x = x;
	fxSlider->bounds.y = y + padding * 1;

	fullscreenCheckbox->bounds.x = x;
	fullscreenCheckbox->bounds.y = y + padding * 2;

	VSyncCheckbox->bounds.x = x;
	VSyncCheckbox->bounds.y = y + padding * 3;*/

	backButton->bounds.x = x + (183 / 4);
	backButton->bounds.y = y + padding * 4;
}

void Settings::ChangeSettings()
{
	isActive = !isActive;
}

bool Settings::GetActiveSettings()
{
	return isActive;
}