#include "player.h"
#include "character.h"
#include "bar.h"

Player::Player(){}

Player::Player(int n, Location dloc, Location sloc, Location bloc, Location bdt, IDirect3DTexture9* texture_)
	: character(new Character(n, dloc, sloc, texture_)), barList(), numBar(20/numPlayer), next(NULL)
{
	/*
	barList = new Bar*[numBar];

	for (int i = 0; i < numBar; ++i)
		barList[i] = new Bar(CooToPxl(sloc));
	*/

	Bstat stat;
	Location pltmp = CooToPxl(sloc);

	pltmp.x += bloc.x;
	pltmp.y += bloc.y;

	barList = new Bar*[numBar];

	for (int i = 0; i < numBar; ++i){
		stat = (i == numBar - 1)? b_up: b_down;

		barList[i] = new Bar(stat, pltmp);

		pltmp.x += bdt.x;
		pltmp.y += bdt.y;
	}
}

Player::~Player(){}

int Player::numPlayer = 4;

void Player::InitPlayer(Player*** playerList, Player** turn){
	// TODO: REARRANGE
	Location* demp;
	Location p2dst[2] = {{8, -1}, {0, -1}};
	Location p4dst[4] = {{-1, 0}, {0, -1}, {-1, 8}, {8, -1}};

	Location* semp;
	Location p2sp[2] = {{0, 4}, {8, 4}};
	Location p4sp[4] = {{4, 8}, {8, 4}, {4, 0}, {0, 4}};

	Location* bemp;
	Location p2bst[2] = {{-50, 0}, {50, 0}};
	Location p4bst[4] = {{0, 50}, {50, 0}, {0, -50}, {-50, 0}};

	Location* b2emp;
	Location p2bdt[2] = {{0, 10}, {0, -10}};
	Location p4bdt[4] = {{10, 0}, {0, -10}, {-10, 0}, {0, 10}};

	demp = (numPlayer == 2)? p2dst: p4dst;
	semp = (numPlayer == 2)? p2sp: p4sp;
	bemp = (numPlayer == 2)? p2bst: p4bst;
	b2emp = (numPlayer == 2)? p2bdt: p4bdt;

	*playerList = new Player*[numPlayer];

	for (int i = 0; i < numPlayer; ++i)
		(*playerList)[i] = new Player(i, demp[i], semp[i], bemp[i], b2emp[i], image->Character_Texture_Pack[i]);

	for (int i = 0; i < numPlayer; ++i)
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];

	/*
	// Why it doesn't works??
	for (int i = 0; i < numPlayer; ++i){
		(*playerList)[i] = new Player(i, tmp[i], image->Character_Texture[i]);
		(*playerList)[i]->next = (*playerList)[(i+1)%numPlayer];
	}
	*/

	*turn = (*playerList)[0];

	return;
}