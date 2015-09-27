#ifndef __PLAYER_H
#define __PLAYER_H

#include <d3d9.h>
#include "common.h"

class Board;
class Character;
class Bar;

class Player{
private:
	static int numPlayer;

	int num;
	Character* character;
	Bar** barList;
	int numBar;
	Player* next;

public:
	Player();
	Player(int, Location, Location, Location, Location, IDirect3DTexture9*);
	~Player();

	void InitPlayer(Player***, Board*, Player**);

	Location __get_barInitLoc(Board*, int) const;
	Bar* __get_lastBar() const;

	int get_numPlayer() const{ return numPlayer; }
	Character* get_character() const{ return character; }
	Bar** get_barList() const{ return barList; }
	int get_numBar() const{ return numBar; }
	Player* get_next() const{ return next; }
};

#endif // __PLAYER_H