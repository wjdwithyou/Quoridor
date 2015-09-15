#include "player.h"

Player::Player(){}

Player::Player(int n, Location loc, IDirect3DTexture9* texture_)
	: character(new Character(n, loc, texture_)), bar(10), next(NULL){

}

/*
Player::Player(int n, Location loc, IDirect3DTexture9** texturePack)
	: character(new Character(n, loc, texturePack)), bar(10), next(NULL){

}
*/

Player::~Player(){}

int Player::numPlayer = 2;

void Player::InitPlayer(Player*** playerList, Player** turn){
	Location* tmp;
	Location p2[2] = { {0, 4}, {8, 4} };
	Location p4[4] = { {4, 8}, {8, 4}, {4, 0}, {0, 4} };

	tmp = (numPlayer==2)? p2: p4;

	*playerList = new Player*[numPlayer];

	for (int i = 0; i < numPlayer; ++i){
		(*playerList)[i] = new Player(i, tmp[i], image->Character_Texture[i]);
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];
	}

	*turn = (*playerList)[0];

	return;
}

void Player::DrawRemainBar(){
	//impl.

	return;
}