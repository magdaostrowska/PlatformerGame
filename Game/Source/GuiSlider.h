#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"
#include "App.h"
#include "Fonts.h"
#include "Globals.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, const char* text, int min = 0, int max = 100, SDL_Texture* texture = NULL);
	~GuiSlider();

	bool Update(float dt);
	bool Draw();

	void SetValue(int newValue);
	int GetValue();

	void SliderControl(int mouseX, int mouseY);

private:

	iPoint* rectAtlasPos = new iPoint(87, 99);
	int margin = 10;
	SDL_Rect button;
	int rectTexW = 183;
	int rectTexH = 91;

	SDL_Rect slider;
	SDL_Rect sliderImage;
	int marginSliders = 4;

	SDL_Rect sliderBarInput;
	SDL_Rect sliderBarImage;

	int value;
	int lastValue;

	int minValue;
	int maxValue;
};

#endif // __GUISLIDER_H__
