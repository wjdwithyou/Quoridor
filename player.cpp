#include "player.h"

Player::Player(){}

Player::Player(IDirect3DTexture9* texture_, int x, int y)
	: character(texture_, x, y), bar(9){	/////

}

Player::~Player(){}