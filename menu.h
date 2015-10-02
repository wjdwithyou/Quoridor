#ifndef __MENU_H
#define __MENU_H

#include "common.h"

class Button;

class Menu{
public:
	const static int TITLE_WIDTH = 600;		// even only
	const static int TITLE_HEIGHT = 250;	// even only
	const static int TITLE_LOC_X = (WindowWidth - TITLE_WIDTH) >> 1;
	const static int TITLE_LOC_Y = 50;

	static Location loc;
	static Button** btnList;

public:
	Menu();
	~Menu();

	void DrawTitle() const;
	void Draw() const;
};

#endif // __MENU_H