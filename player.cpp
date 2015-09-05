#include "player.h"

Player::Player(){}

Player::Player(IDirect3DTexture9* texture_, int x, int y)
	: character(new Character(texture_, x, y)), bar(10){

}

Player::~Player(){}

void Player::DrawRemainBar(){

}