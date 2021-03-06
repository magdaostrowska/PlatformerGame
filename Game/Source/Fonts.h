#ifndef __FONTS_H__
#define __FONTS_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_pixels.h"

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];

	SDL_Texture* texture = nullptr;

	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
};

class Fonts : public Module
{
public:

	Fonts();

	~Fonts();

	int Load(const char* texturePath, const char* characters, uint rows = 1);

	void UnLoad(int fontIndex);

	void BlitText(int x, int y, int fontIndex, const char* text, int zoom = 1, int r = 255, int g = 255, int b = 255, int max = 1920, int down = 1) const;

private:

	Font fonts[MAX_FONTS];

};


#endif // __Fonts_H__
