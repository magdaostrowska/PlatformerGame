#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "windows.h"
#include <stdio.h>

// Exit status values
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Update function result return values
enum class UpdateResult
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs
typedef unsigned int uint;

#define SCREEN_SIZE 1
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 1
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0

#define VSYNC true

// Files
#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// DynArray
#define DYN_ARRAY_BLOCK_SIZE 16

// SString
#define TMP_STRING_SIZE	4096

// Fonts
#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

//Input
#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYS 300
//#define NUM_KEYS 352
//#define LAST_KEYS_PRESSED_BUFFER 50

// Collider
#define MAX_LISTENERS 10

// Enemies
#define MAX_ENEMIES 100
#define SPAWN_MARGIN 50

// Items
#define MAX_ITEMS 100

// Shots
#define MAX_ACTIVE_SHOTS 100

// Pathfinding
#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255
#define COST_MAP_SIZE 100
#define MAX_FRAMES 100

#define SPACEBOUNDBAR 10

#endif // __GLOBALS_H__