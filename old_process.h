#ifndef __PROCESS_H
#define __PROCESS_H

#include <Windows.h>

//class Menu;
class Board;
class Player;

//enum Pstat{ p_menu, p_game };

class Process{
private:
	//Menu* menu;

	//Board* _board;
	//Player** playerList;

public:
	//const static int NUM_STAT = 2;
	//static Pstat status;

public:
	Process();
	Process(WNDCLASS);
	~Process();

	//void MenuLoop() const;
	//void GameLoop() const;

	//stat get_status() const{ return status; }
};

#endif // __PROCESS_H