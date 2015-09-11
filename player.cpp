#include "player.h"

Player::Player(){}

Player::Player(int n, IDirect3DTexture9** texturePack, Location loc)
	: character(new Character(n, texturePack, loc)), bar(10), next(NULL){

}
/*
Player::Player(int n, IDirect3DTexture9* chara_texture, IDirect3DTexture9* square_over_texture, int x, int y)
	: character(new Character(n, chara_texture, square_over_texture, x, y)), bar(10), next(NULL){

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
		(*playerList)[i] = new Player(i, image->Character_Texture_Pack[i], tmp[i]);
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];
	}

	*turn = (*playerList)[0];

	return;
}

void Player::DrawRemainBar(){
	//impl.

	return;
}