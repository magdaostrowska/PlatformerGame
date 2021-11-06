#include "App.h"
#include "Title.h"
#include "Input.h"
#include "SDL/include/SDL.h"
#include "FadeToBlack.h"






Title::Title() : Module()
{

}

Title::~Title()
{

}

bool Title::Awake() {

	inTitle = true;
	return true;
}
bool Title::Start()
{

	return true;
}

bool Title::Update(float dt)
{
	if (inTitle == true) {
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			app->fade->Fade(240, 1);
			inTitle = false;
		}
	}

	return true;
}

bool Title::PostUpdate()
{

	return true;
}

bool Title::CleanUp()
{
	return true;
}