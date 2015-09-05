#include "board.h"
#include "dxfunc.h"
#include "image.h"

#include "api.h"	/////

Board::Board()
	: size(580){
}
Board::~Board(){}

void Board::DrawBoard(){
	DrawC(Board_Texture, WindowWidth/2, WindowHeight/2, 1.0f, 0.0f, (float)size/2);
}