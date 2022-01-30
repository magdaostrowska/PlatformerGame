#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Fonts.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if (id == 3) {
			if ((mouseX > (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale())) && (mouseX < ((((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()) + bounds.w)) &&
				(mouseY - 20 > (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10) && (mouseY - 20 < ((app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10 + bounds.h)))
			{
				state = GuiControlState::FOCUSED;

				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::PRESSED;
				}

				// If mouse button pressed -> Generate event!
				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				{
					NotifyObserver();
				}
			}
			else state = GuiControlState::NORMAL;
		}
		else {
			if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
				(mouseY - 20 > bounds.y) && (mouseY - 20 < (bounds.y + bounds.h)))
			{
				state = GuiControlState::FOCUSED;

				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::PRESSED;
				}

				// If mouse button pressed -> Generate event!
				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				{
					NotifyObserver();
				}
			}
			else state = GuiControlState::NORMAL;
		}

		
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	if (this->id==3) {
		switch (state)
		{
			//(((app->render->camera.x - app->render->camera.w / 2 - 80 / 2) - (app->render->camera.x - (app->render->camera.w / 2 - 80 / 2)) * 2) / app->win->GetScale()), (((app->render->camera.y - app->render->camera.h / 2 - (20 / 2)) - (app->render->camera.y - (app->render->camera.h / 2 - (20 / 2) + 20)) * 2) / app->win->GetScale()), textFont, "PLAY");

		case GuiControlState::DISABLED:
		{
			app->render->DrawRectangle({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10,bounds.w, bounds.h }, 0, 0, 0, 0);
		} break;

		case GuiControlState::NORMAL:
		{
			app->render->DrawRectangle({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int) app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2)  / (int)app->win->GetScale() + 10,bounds.w, bounds.h }, 233, 188, 51, 255);
			//app->fonts->BlitText({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10, app->scene->textFont, "||"});
		} break;

		//Draw the button according the GuiControl State
		case GuiControlState::FOCUSED:
		{
			app->render->DrawRectangle({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10,bounds.w, bounds.h }, 215, 122, 53, 240);
		} break;
		case GuiControlState::PRESSED:
		{
			app->render->DrawRectangle({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10,bounds.w, bounds.h }, 255, 231, 213, 255);
		} break;


		case GuiControlState::SELECTED: 
			app->render->DrawRectangle({ (((app->render->camera.x - app->render->camera.w / 2 - (30 * 20) / 2) - (app->render->camera.x - (app->render->camera.w / 2 - (30 * 20) / 2)) * 2) / (int)app->win->GetScale()), (app->render->camera.y - app->render->camera.y * 2) / (int)app->win->GetScale() + 10,bounds.w, bounds.h }, 0, 255, 0, 255);
			break;

		default:
			break;
		}
	}
	else {
		switch (state)
		{

		case GuiControlState::DISABLED:
		{
			app->render->DrawRectangle(bounds, 0, 0, 0, 0);
		} break;

		case GuiControlState::NORMAL:
		{
			app->render->DrawRectangle(bounds, 233, 188, 51, 255);

		} break;

		//Draw the button according the GuiControl State
		case GuiControlState::FOCUSED:
		{
			app->render->DrawRectangle(bounds, 215, 122, 53, 240);
		} break;
		case GuiControlState::PRESSED:
		{
			app->render->DrawRectangle(bounds, 255, 231, 213, 255);
		} break;


		case GuiControlState::SELECTED: app->render->DrawRectangle(bounds, 0, 255, 0, 255);
			break;

		default:
			break;
		}
	}
	

	return false;
}