#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "FadeToBlack.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load state game
	bool LoadState(pugi::xml_node& data);

	// Save state game
	bool SaveState(pugi::xml_node& data)const;


public:

	int level = 2;

private:

	int textFont = -1;

	iPoint back_pos;
	SDL_Rect rectMap = {0,0,2304,324};

	SDL_Texture* img;
	SDL_Texture* back1;

	char playerLifes[2] = { "\0" };
	SDL_Rect blackRect = {0,0,0,0};
	SDL_Rect blackRect2 = { 0,0,0,0 };
};

#endif // __SCENE_H__