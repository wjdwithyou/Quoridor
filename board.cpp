#include "board.h"
#include "api.h"
#include "dxfunc.h"
#include "image.h"	/////

Board::Board()
	: Width(580), Height(580)
{
	loc.x = (WindowWidth - Width) / 2;
	loc.y = (WindowHeight - Height) / 2;
}

Board::~Board(){}

void Board::DrawBoard(){
	DrawC(Board_Texture, WindowWidth/2, WindowHeight/2, 1.0f, 0.0f, (float)Width/2);
}