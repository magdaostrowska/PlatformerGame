#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Collisions.h"
#include "Fonts.h"
#include "Title.h"
#include "FadeToBlack.h"
#include "Enemy.h"
#include "PathFinding.h"

#include "Defs.h"
#include "Log.h"
#include "PugiXml/src/pugixml.hpp"

#include <iostream>
#include <sstream>

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Fonts;
class Scene;
class Map;
class Collisions;
class Player;
class Title;
class FadeToBlack;
class ModuleEnemy;
class PathFinding;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	pugi::xml_node GetConfig();

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	//virtual void OnCollision(Collider* c1, Collider* c2);

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Map* map;
	Collisions* collisions;
	Player* player;
	Fonts* fonts;
	Title* titleScreen;
	FadeToBlack* fade;
	ModuleEnemy* enemies;
	PathFinding* pathfinding;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// Creating new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;
	float dt;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	SString filenameGame;
	SString filenameConfig;
};

extern App* app;

#endif	// __APP_H__