#include "button.h"
#include "dxfunc.h"
#include "image.h"
#include "common.h"

#include "menu.h"

Button::Button(){}

Button::Button(int n)
	: num(n), status(btn_down), texture_pack(image->Button_Texture_Pack[n])
{
	loc.x = Menu::loc.x;
	loc.y = (HEIGHT * num) + Menu::loc.y;
}

Button::~Button(){}

void Button::Draw() const{
	DrawTexture(texture_pack[status], loc, 1.0f, 0.0f);
	return;
}