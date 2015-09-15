#include "square.h"
#include "dxfunc.h"
#include "image.h"

Square::Square(){}

Square::Square(int x, int y)
	: status(q_base), onthis(NULL), texture_(image->Square_Texture[q_base])
{
	loc.x = x;
	loc.y = y;
}

Square::~Square(){}

void Square::Draw(){
	DrawTexture(texture_, CooToPxl(loc), 1.0f, 0.0f);
	return;
}