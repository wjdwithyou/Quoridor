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

Location Bar::size = {60, 125};

void Bar::DrawBar() const{
	DrawTexture(texture_, loc, 0.75f, 60.0f / 180 * PI, static_cast<float>(size.x >> 1),  static_cast<float>(size.y >> 1));
	return;
}