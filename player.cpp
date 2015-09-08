#include "player.h"
#include "image.h"

Player::Player(){}

Player::Player(int n, IDirect3DTexture9* chara_texture, IDirect3DTexture9* square_over_texture, int x, int y)
	: character(new Character(n, chara_texture, square_over_texture, x, y)), bar(10), next(NULL){

}

Player::~Player(){}

void Player::InitPlayer(Player** player1, Player** player2, Player** turn){
	*player1 = new Player(1, Character_Black_Texture, Square_Over_Black_Texture, 0, 4);
	(*player1)->next = *player2;

	*player2 = new Player(2, Character_Brown_Texture, Square_Over_Brown_Texture, 8, 4);
	(*player2)->next = *player1;

	// impl.
	// *turn = rand()..

	return;
}

void Player::DrawRemainBar(){
	//impl.

	return;
}