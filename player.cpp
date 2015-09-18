#include "player.h"

Player::Player(){}

Player::Player(int n, Location dloc, Location sloc, IDirect3DTexture9* texture_)
	: character(new Character(n, dloc, sloc, texture_)), bar(10), next(NULL){

}

Player::~Player(){}

int Player::numPlayer = 2;

void Player::InitPlayer(Player*** playerList, Player** turn){
	Location* demp;
	Location p2dst[2] = { {8, -1}, {0, -1} };
	Location p4dst[4] = { {-1, 0}, {0, -1}, {-1, 8}, {8, -1} };

	Location* semp;
	Location p2sp[2] = { {0, 4}, {8, 4} };
	Location p4sp[4] = { {4, 8}, {8, 4}, {4, 0}, {0, 4} };

	demp = (numPlayer==2)? p2dst: p4dst;
	semp = (numPlayer==2)? p2sp: p4sp;

	*playerList = new Player*[numPlayer];

	for (int i = 0; i < numPlayer; ++i)
		(*playerList)[i] = new Player(i, demp[i], semp[i], image->Character_Texture[i]);

	for (int i = 0; i < numPlayer; ++i)
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];

	/*
	// Why it doesn'y works??
	for (int i = 0; i < numPlayer; ++i){
		(*playerList)[i] = new Player(i, tmp[i], image->Character_Texture[i]);
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];
	}
	*/

	*turn = (*playerList)[0];

	return;
}

void Player::DrawRemainBar() const{
	//impl.

	return;
}