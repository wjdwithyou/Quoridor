#include "board.h"
#include "api.h"
#include "dxfunc.h"
#include "image.h"	/////

Board::Board()
	: Size(9), Width(580), Height(580)
{
	Init();
}

Board::~Board(){}

Location Board::loc = {(WindowWidth - Board().Width) / 2, (WindowHeight - Board().Height) / 2};

Square** Board::board = NULL;

void Board::Init(){
	board = new Square*[Size];

	for (int i = 0; i < Size; ++i){
		board[i] = new Square[Size];
	}

	return;
}

void Board::Draw(){
	DrawC(Board_Texture, WindowWidth/2, WindowHeight/2, 1.0f, 0.0f, (float)Width/2);	/////
	return;
}