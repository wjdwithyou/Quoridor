#include "bar.h"
#include "dxfunc.h"
#include "image.h"

Bar::Bar()
	: texture_pack(image->Bar_Texture_Pack){

}

Bar::Bar(Bstat s, Location _loc)
	: status(s), loc(_loc), mag(0.75), texture_pack(image->Bar_Texture_Pack){
		
}

Bar::~Bar(){}

Location Bar::size = {60, 125};

void Bar::DrawBar() const{
	DrawTexture(texture_pack[status], loc, mag, 60.0f / 180 * PI, static_cast<float>(size.x >> 1),  static_cast<float>(size.y >> 1));
	return;
}