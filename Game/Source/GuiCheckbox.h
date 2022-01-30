#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"
#include "Point.h"
#include "SString.h"

class GuiCheckbox : public GuiControl
{
public:

	GuiCheckbox(uint32 id, SDL_Rect bounds, const char* text, bool initState = false, SDL_Texture* texture = NULL);
	virtual ~GuiCheckbox();

	bool Update(float dt);
	bool Draw();

	bool GetValue();
	void SetValue(bool state) { isChecked = state; };

private:

	void ChangeImageChecked();

	iPoint* rectAtlasPos = new iPoint(87, 99);
	iPoint* falseAtlasPos = new iPoint(227, 201);
	iPoint* trueAtlasPos = new iPoint(552, 1407);
	
	SDL_Rect button;
	SDL_Rect checkBoxInput;
	SDL_Rect checkBoxImage;

	int squareTexWidth, squareTexHeight, rectTexWidth, rectTexHeight, margin, marginSquare;
	bool textDisable, isMouseIn, isChecked;
};

#endif // __GUICHECKBOX_H__
