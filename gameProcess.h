#ifndef __GAME_PROCESS_H
#define __GAME_PROCESS_H

#include "process.h"

class GamingMouse;
class Board;
class Player;

class GameProcess : public Process{
private:
	GamingMouse* mouse;
	Board* _board;
	Player** playerList;
	Player* turn;

public:
	GameProcess();
	~GameProcess();

	virtual void Init(int);
	virtual void Loop() const;
};

#endif // __GAME_PROCESS_H