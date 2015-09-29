#include "bar.h"
#include "dxfunc.h"
#include "image.h"

Bar::Bar()
	: texture_pack(image->Bar_Texture_Pack){

}

Bar::Bar(Bstat s, Location _loc)
	: status(s), loc(_loc), mag(0.75f), angle(60.0f), texture_pack(image->Bar_Texture_Pack){
		
}

Bar::~Bar(){}

Location Bar::size = {60, 125};

void Bar::Draw(Location mloc) const{
	Location temp = (status == b_clicked)? mloc: loc;

	DrawTexture(texture_pack[status], temp, mag, angle / 180 * PI, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));

	return;
}

void Bar::__set_pickedBar(){
	status = b_clicked;
	mag = 1.0f;
	angle = 0.0f;

	return;
}

void Bar::__set_releasedBar(){
	status = b_over;
	mag = 0.75f;
	angle = 60.0f;

	return;
}

void Bar::__set_angle(float delta){
	angle += delta;
	return;
}