#include "bar.h"
#include "dxfunc.h"
#include "image.h"

Bar::Bar()
	: texture_(image->Bar_Texture){

}

Bar::Bar(Bstat s, Location _loc)
	: status(s), loc(_loc), texture_(image->Bar_Texture){

}

Bar::~Bar(){}

void Bar::DrawBar() const{
	DrawTexture(texture_, loc, 0.75f, 60.0f / 180 * PI);	// tmp
	return;
}

// 10.0f / 180 * 3.141592f;