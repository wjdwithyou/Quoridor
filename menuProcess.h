#ifndef __MENU_PROCESS_H
#define __MENU_PROCESS_H

#include "process.h"

class Mouse;
class Menu;

class MenuProcess : public Process{
private:
	Mouse* mouse;
	Menu* menu;

public:
	MenuProcess();
	~MenuProcess();

	virtual void Init(int);
	virtual void Loop() const;
};

#endif // __MENU_PROCESS_H