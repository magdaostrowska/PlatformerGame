#include "FadeToBlack.h"
#include "Render.h"
#include "App.h"
#include "Window.h"

#include "SDL/include/SDL_render.h"

FadeToBlack::FadeToBlack() : Module()
{
	name.Create("fade");
	screenRect = { 0, 0, 1920 *3, 1080 * 3 };
}

FadeToBlack::~FadeToBlack()
{

}

bool FadeToBlack::Start()
{
	//LOG("Preparing Fade Screen");

	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	screenRect = { 0,0, app->win->screenSurface->w ,app->win->screenSurface->h };
	return true;
}

bool FadeToBlack::Update(float dt)
{

	if (currentStep == Fade_Step::NONE) return true;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			//moduleToDisable->Disable();
			//moduleToEnable->Enable();

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	return true;
}

bool FadeToBlack::PostUpdate()
{

	if (currentStep == Fade_Step::NONE) return true;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;


	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);

	return true;
}

bool FadeToBlack::Fade(float frames, int mode)
{

	bool ret = false;

	if (currentStep == Fade_Step::NONE)
	{
		if (mode == 0) {
			currentStep = Fade_Step::TO_BLACK;
			frameCount = 0;
		}
		else if (mode == 1) {
			currentStep = Fade_Step::FROM_BLACK;
			frameCount = frames;
		}
		
		
		maxFadeFrames = frames;

		//this->moduleToDisable = moduleToDisable;
		//this->moduleToEnable = moduleToEnable;

		ret = true;
	}

	return ret;
}