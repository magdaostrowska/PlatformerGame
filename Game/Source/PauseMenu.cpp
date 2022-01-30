#include "PauseMenu.h"

PauseMenu::PauseMenu(iPoint position)
{
	name.Create("PauseMenu");
	screenRect = { 0, 0, WIDTH, HEIGHT };
	padding = 100;

	resumeButton = new GuiButton(1, { position.x , position.y, 183, 91 }, "RESUME");
	settingsButton = new GuiButton(2, { position.x , position.y + padding, 183, 91 }, "SETTINGS");
	backToTitleButton = new GuiButton(3, { position.x , position.y + padding * 2, 183, 91 }, "TITLE");
	exitButton = new GuiButton(4, { position.x , position.y + padding * 3, 90, 90 }, "EXIT");

	isActive = false;
	isPauseMenuActive = false;
}

PauseMenu::~PauseMenu()
{

}

bool PauseMenu::Update(float dt)
{
	bool ret = true;

	if (isActive)
	{
		resumeButton->Update(dt);
		settingsButton->Update(dt);
		backToTitleButton->Update(dt);
		ret = exitButton->Update(dt);
		if (isPauseMenuActive)
		{
			// TODO: settingsMenu->Update(dt);
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
				CloseSettingsMenu();
		}
		else
		{
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			{
				// TODO: app->sceneManager->SetPause(false);
				isActive = false;
				isPauseMenuActive = false;
			}
		}
	}
	return true;
}

bool PauseMenu::CleanUp()
{
	return true;
}

bool PauseMenu::Draw()
{
	return false;
}

bool PauseMenu::Event(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (control->id == 1)
		{
			//app->sceneManager->SetPause(false);
			active = false;
			isPauseMenuActive = false;
		}
		else if (control->id == 2)
		{
			isPauseMenuActive = true;
			resumeButton->state = GuiControlState::DISABLED;
			settingsButton->state = GuiControlState::DISABLED;
			backToTitleButton->state = GuiControlState::DISABLED;
			exitButton->state = GuiControlState::DISABLED;
			/*settingsMenu->MovePosition();
			settingsMenu->sldMusic->SetValue(app->audio->GetVolumeMusic());
			settingsMenu->sldFx->SetValue(app->audio->GetVolumeFx());
			settingsMenu->AbleDisableSetting();*/
		}
		else if (control->id == 3)
		{
			
		}
		else if (control->id == 4)
		{
			return false;
		}
		else if (control->id == 10)
		{
			CloseSettingsMenu();
		}

	}
	case GuiControlType::SLIDER:
	{
		
	}
	case GuiControlType::CHECKBOX:
	{
		
	}
	default: break;
	}
	return true;

}

void PauseMenu::AbleDisableSetting()
{
	isActive = !isActive;
}

void PauseMenu::AbleDisableMenu()
{
	isPauseMenuActive = !isPauseMenuActive;
}

void PauseMenu::CloseSettingsMenu()
{
	isPauseMenuActive = false;
	resumeButton->state = GuiControlState::NORMAL;
	settingsButton->state = GuiControlState::NORMAL;
	backToTitleButton->state = GuiControlState::NORMAL;
	exitButton->state = GuiControlState::NORMAL;
	//settingsMenu->AbleDisableSetting();
	app->SaveGameRequest();
}
