#include "menu.h"
#include "dxfunc.h"
#include "image.h"
#include "button.h"

Menu::Menu(){
	btnList = new Button*[Button::NUM];

	for (int i = 0; i < Button::NUM; ++i)
		btnList[i] = new Button(i);
}

Menu::~Menu(){}

Location Menu::loc = {(WindowWidth - Button::WIDTH) >> 1, WindowHeight - ((Button::NUM + 1) * Button::HEIGHT)};

Button** Menu::btnList = NULL;

void Menu::DrawTitle() const{
	DrawTexture(image->Title_Texture, static_cast<float>(TITLE_LOC_X), static_cast<float>(TITLE_LOC_Y), 1.0f, 0.0f);
	return;
}

void Menu::Draw() const{
	for (int i = 0; i < Button::NUM; ++i)
		btnList[i]->Draw();

	return;
}