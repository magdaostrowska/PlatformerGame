#ifndef __FADE_TO_BLACK_H__
#define __FADE_TO_BLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeToBlack : public Module
{
public:

	FadeToBlack();

	~FadeToBlack();

	bool Start() override;

	bool Update(float dt);

	bool PostUpdate() override;

	bool Fade(float frames = 60, int mode =0);

	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	} currentStep = Fade_Step::NONE;

	SDL_Rect screenRect;

	//Module* moduleToEnable = nullptr;
	//Module* moduleToDisable = nullptr;
};

#endif //__FADE_TO_BLACK_H__

