#ifndef __PLAYER_H
#define __PLAYER_H

#include "character.h"

class Player{
private:
	Character* character;
	int bar;
	Player* next;

public:
	Player();
	Player(int, IDirect3DTexture9*, IDirect3DTexture9*, int, int);
	~Player();

	void InitPlayer(Player**, Player**);
	void DrawRemainBar();

	Character* get_character(){ return character; }
};

#endif // __PLAYER_H