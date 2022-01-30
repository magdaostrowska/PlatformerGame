#include "Render.h"
#include "App.h"
#include "Window.h"
#include "Intro.h"

#include "SDL/include/SDL_render.h"

Intro::Intro() : Module()
{
	name.Create("intro");
}

Intro::~Intro()
{

}

bool Intro::Start()
{
	
	return true;
}

bool Intro::Update(float dt)
{

	return true;
}

bool Intro::PostUpdate()
{

	return true;
}
