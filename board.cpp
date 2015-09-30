#include "board.h"
#include "dxfunc.h"
#include "square.h"
#include "rectj.h"
#include "point.h"

Board::Board(){}

Board::Board(IDirect3DTexture9* texture_)
	: pBoardTexture(texture_)
{
	Init();
}

Board::~Board(){}

Location Board::loc = {(WindowWidth - WIDTH) >> 1, (WindowHeight - HEIGHT) >> 1};
Location Board::itsloc = {loc.x + Square::SIZE + 2, loc.y + Square::SIZE + 2};

Square*** Board::board = NULL;
//Rectj*** Board::vtc = NULL;
//Rectj*** Board::hrz = NULL;
Point*** Board::its = NULL;

void Board::Init(){
	board = new Square**[SIZE];

	for (int i = 0; i < SIZE; ++i){
		board[i] = new Square*[SIZE];

		for (int j = 0; j < SIZE; ++j)
			board[i][j] = new Square(j, i);
	}

	/*
	vtc = new Rectj**[SIZE];

	for (int i = 0; i < SIZE; ++i){
		vtc[i] = new Rectj*[SIZE - 1];

		for (int j = 0; j < SIZE - 1; ++j)
			vtc[i][j] = new Rectj();
	}

	hrz = new Rectj**[SIZE - 1];

	for (int i = 0; i < SIZE - 1; ++i){
		hrz[i] = new Rectj*[SIZE];

		for (int j = 0; j < SIZE; ++j)
			hrz[i][j] = new Rectj();
	}
	*/

	its = new Point**[SIZE - 1];

	for (int i = 0; i < SIZE - 1; ++i){
		its[i] = new Point*[SIZE - 1];

		for (int j = 0; j < SIZE - 1; ++j)
			its[i][j] = new Point(j, i);
	}

	return;
}

void Board::Draw() const{
	for (int i = 0; i < SIZE; ++i){
		for (int j = 0; j < SIZE; ++j)
			board[i][j]->Draw();
	}

	return;
}

/*
void Board::Draw(){
	DrawC(pBoardTexture, WindowWidth/2, WindowHeight/2, 1.0f, 0.0f, (float)Width/2);	/////
	return;
}
*/

Location Board::__get_centerLoc() const{
	Location temp;

	temp.x = loc.x + (WIDTH >> 1);
	temp.y = loc.y + (HEIGHT >> 1);

	return temp;
}