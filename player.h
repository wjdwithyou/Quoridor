#ifndef __PLAYER_H
#define __PLAYER_H

#include "character.h"

class Player{
private:
	Character* character;
	int bar;

public:
	Player();
	Player(IDirect3DTexture9*, int, int);
	~Player();

	void DrawRemainBar();

	Character* get_character(){ return character; }
};

#endif // __PLAYER_H