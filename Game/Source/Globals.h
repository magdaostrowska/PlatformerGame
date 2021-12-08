#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "windows.h"
#include <stdio.h>

/*

// Log macro for debug messages
#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

	OutputDebugString(tmp_string2);
}
*/

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
#define VSYNC 1

// Files
#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Enemies
#define MAX_ENEMIES 100
#define SPAWN_MARGIN 50

// Pathfinding
#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255

#endif // __GLOBALS_H__