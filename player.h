#ifndef __PLAYER_H
#define __PLAYER_H

#include <d3d9.h>
#include "common.h"

class Board;
class Character;
class Bar;

class Player{
private:
	int num;
	Character* character;
	Bar** barList;
	int numBar;
	int maxBar;
	Player* next;

public:
	static int numPlayer;

public:
	Player();
	Player(int, Location, Location, Location, Location, IDirect3DTexture9*);
	~Player();

	void InitPlayer(Player***, Player**);

	Location __get_barInitLoc(int) const;
	Bar* __get_lastBar() const;
	
	void __set_numBar(int);

	int get_numPlayer() const{ return numPlayer; }
	Character* get_character() const{ return character; }
	Bar** get_barList() const{ return barList; }
	int get_maxBar() const{ return maxBar; }
	Player* get_next() const{ return next; }
};

#endif // __PLAYER_H