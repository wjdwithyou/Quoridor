#include "player.h"
#include "character.h"
#include "board.h"
#include "square.h"
#include "bar.h"

Player::Player(){}

Player::Player(int n, Location dloc, Location sloc, Location iemp, Location bdt, IDirect3DTexture9* texture_)
	: num(n), character(new Character(n, dloc, sloc, texture_)), barList(), numBar(20/numPlayer), next(NULL)
{
	Bstat stat;
	Location pltmp = CooToPxl(sloc);

	pltmp.x += iemp.x;
	pltmp.y += iemp.y;

	barList = new Bar*[numBar];

	for (int i = 0; i < numBar; ++i){
		stat = (i == numBar - 1)? b_up: b_down;

		barList[i] = new Bar(stat, pltmp);

		pltmp.x += bdt.x;
		pltmp.y += bdt.y;
	}
}

Player::~Player(){}

int Player::numPlayer = 4;	// only '2' and '4' players are allowed.

void Player::InitPlayer(Player*** playerList, Board* _board, Player** turn){
	// TODO: REARRANGE
	int b = _board->get_Size() - 1;

	Location* demp;	// dest
	Location p2dst[2] = {{b, -1}, {0, -1}};
	Location p4dst[4] = {{-1, 0}, {0, -1}, {-1, b}, {b, -1}};

	Location* semp;	// chara st
	Location p2sp[2] = {{0, b>>1}, {b, b>>1}};
	Location p4sp[4] = {{b>>1, b}, {b, b>>1}, {b>>1, 0}, {0, b>>1}};

	Location iemp;	// bar st, using __get_barInitLoc()

	Location* b2emp; // bar delta
	Location p2bdt[2] = {{0, Bar::_BAR}, {0, -Bar::_BAR}};
	Location p4bdt[4] = {{Bar::_BAR, 0}, {0, -Bar::_BAR}, {-Bar::_BAR, 0}, {0, Bar::_BAR}};

	demp = (numPlayer == 2)? p2dst: p4dst;
	semp = (numPlayer == 2)? p2sp: p4sp;
	b2emp = (numPlayer == 2)? p2bdt: p4bdt;

	*playerList = new Player*[numPlayer];
	
	for (int i = 0; i < numPlayer; ++i){
		iemp = __get_barInitLoc(_board, i);
		(*playerList)[i] = new Player(i, demp[i], semp[i], iemp, b2emp[i], image->Character_Texture_Pack[i]);
	}

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

Location Player::__get_barInitLoc(Board* _board, int pn) const{
	Location* iemp;
	Location p2bil[2] = {{-Bar::_BOARD, 0}, {Bar::_BOARD + Square::SQUARE_SIZE, 0}};
	Location p4bil[4] = {{0, Bar::_BOARD + Square::SQUARE_SIZE}, {Bar::_BOARD + Square::SQUARE_SIZE, 0}, {0, -Bar::_BOARD}, {-Bar::_BOARD, 0}};

	iemp = (numPlayer == 2)? p2bil: p4bil;

	return iemp[pn];
}