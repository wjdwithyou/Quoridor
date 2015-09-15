#ifndef __PLAYER_H
#define __PLAYER_H

#include "character.h"

class Player{
private:
	static int numPlayer;

	Character* character;
	int bar;
	Player* next;

public:
	Player();
	Player(int, Location, IDirect3DTexture9*);
	~Player();

	void InitPlayer(Player***, Player**);
	void DrawRemainBar();

	int get_numPlayer(){ return numPlayer; }
	Character* get_character(){ return character; }
};

#endif // __PLAYER_H