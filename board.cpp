#include "board.h"
#include "api.h"
#include "dxfunc.h"
#include "image.h"	/////

Board::Board()
	: Width(580), Height(580){

}

Board::~Board(){}

Location Board::loc = {(WindowWidth - Board().Width) / 2, (WindowHeight - Board().Height) / 2};

void Board::DrawBoard(){
	DrawC(Board_Texture, WindowWidth/2, WindowHeight/2, 1.0f, 0.0f, (float)Width/2);	/////
	return;
}