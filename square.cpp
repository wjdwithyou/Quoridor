#include "square.h"
#include "dxfunc.h"
#include "image.h"

Square::Square(){}

Square::Square(int x, int y)
	: status(q_base), onthis(NULL), texture_pack(image->Square_Texture_Pack)
{
	loc.x = x;
	loc.y = y;
}

Square::~Square(){}

void Square::Draw() const{
	DrawTexture(texture_pack[status], CooToPxl(loc), 1.0f, 0.0f);
	return;
}