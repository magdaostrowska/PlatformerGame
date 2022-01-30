#ifndef __FADE_TO_BLACK_H__
#define __FADE_TO_BLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class Intro : public Module
{
public:

	Intro();

	~Intro();

	bool Start() override;

	bool Update(float dt);

	bool PostUpdate() override;






};

#endif //__FADE_TO_BLACK_H__


