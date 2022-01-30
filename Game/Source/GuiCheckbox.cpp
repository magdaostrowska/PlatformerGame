#include "GuiCheckbox.h"

GuiCheckbox::GuiCheckbox(uint32 id, SDL_Rect bounds, const char* text, bool initState, SDL_Texture* texture) : GuiControl(GuiControlType::CHECKBOX, id)
{
	rectAtlasPos = new iPoint(87, 99);
	falseAtlasPos = new iPoint(227, 201);
	trueAtlasPos = new iPoint(552, 1407);

	squareTexWidth = 90;
	squareTexHeight = 90;
	rectTexWidth = 180;
	rectTexHeight = 90;
	margin = 10;
	marginSquare = 10;

	textDisable = false;
	isMouseIn = false;

	this->bounds = bounds;
	this->texture = texture;
	this->text = text;
}

GuiCheckbox::~GuiCheckbox()
{
}

bool GuiCheckbox::Update(float dt)
{
	return false;
}

bool GuiCheckbox::Draw()
{
	return false;
}

bool GuiCheckbox::GetValue()
{
	return false;
}

void GuiCheckbox::ChangeImageChecked()
{
	if (!isChecked) 
	{
		checkBoxImage.x = falseAtlasPos->x;
		checkBoxImage.y = falseAtlasPos->y;
	}
	else
	{
		checkBoxImage.x = trueAtlasPos->x;
		checkBoxImage.y = trueAtlasPos->y;
	}

	button.x = rectAtlasPos->x;
}
