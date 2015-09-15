#include "board.h"
#include "api.h"
#include "dxfunc.h"
#include "square.h"

Board::Board()
	: Size(9), Width(580), Height(580){

}

Board::Board(IDirect3DTexture9* texture_)
	: Size(9), Width(580), Height(580), pBoardTexture(texture_)
{
	Init();
}

Board::~Board(){}

Location Board::loc = {(WindowWidth - Board().Width) / 2, (WindowHeight - Board().Height) / 2};

Square*** Board::board = NULL;

void Board::Init(){
	board = new Square**[Size];

	for (int i = 0; i < Size; ++i){
		board[i] = new Square*[Size];

		for (int j = 0; j <Size; ++j){
			board[i][j] = new Square(j, i);
		}
	}

	return;
}

void Board::Draw(){
	for (int i = 0; i < Size; ++i){
		for (int j = 0; j < Size; ++j)
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