#include "square.h"

Square::Square(){}

Square::Square(int x, int y)
	: onthis(NULL)
{
	loc.x = x;
	loc.y = y;
}

Square::~Square(){}