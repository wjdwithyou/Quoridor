#include "bar.h"
#include "dxfunc.h"
#include "image.h"
#include "gamingMouse.h"
#include "board.h"

Bar::Bar()
	: texture_pack(image->Bar_Texture_Pack){

}

Bar::Bar(Location _loc)
	: status(b_over), loc(_loc), mag(0.75f), angle(60.0f), texture_pack(image->Bar_Texture_Pack){
		
}

Bar::~Bar(){}

Location Bar::size = {60, 125};

Location Bar::size_used = {5, 125};

void Bar::Draw(GamingMouse* mouse) const{		// simplify test
	switch (status){
	case b_over:
		DrawTexture(texture_pack[status], loc, mag, angle / 180 * PI, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
		break;
		
	case b_on:
		DrawTexture(texture_pack[status], loc, mag, angle / 180 * PI, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
		break;

	case b_clicked:
		DrawTexture(texture_pack[status], mouse->get_pxloc(), mag, angle / 180 * PI, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
		break;

	case b_can:
		DrawTexture(texture_pack[status], CooToPxl(mouse->get_locooits(), Board::SIZE - 1), mag, angle / 180 * PI, static_cast<float>(size_used.x >> 1) + EFFECT_THICK, static_cast<float>(size_used.y >> 1) + EFFECT_THICK);
		break;

	case b_cannot:
		DrawTexture(texture_pack[status], CooToPxl(mouse->get_locooits(), Board::SIZE - 1), mag, angle / 180 * PI, static_cast<float>(size_used.x >> 1) + EFFECT_THICK, static_cast<float>(size_used.y >> 1) + EFFECT_THICK);
		break;

	case b_used:
		DrawTexture(texture_pack[status], loc, mag, angle / 180 * PI, static_cast<float>(size_used.x >> 1), static_cast<float>(size_used.y >> 1));
		break;

	default:
		break;
	}


	/*

	Location temp = (status == b_clicked)? mloc: loc;

	if (status == b_clicked){
		Point* it;

		if ((it = mouse->CheckAroundPoint()) != NULL){
			if (it->get_onBarStatus() == d_none)
				DrawTexture(texture_pack[b_can], it->get_pxloc(), 1.0f, 0.0f, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
			else
				DrawTexture(texture_pack[b_cannot], it->get_pxloc(), 1.0f, 0.0f, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
		}
	}
	else
		DrawTexture(texture_pack[status], temp, mag, angle / 180 * PI, static_cast<float>(size.x >> 1), static_cast<float>(size.y >> 1));
		*/
	return;
}

Bdir Bar::CheckOrthogonal() const{
	if (angle == 0.0f || angle == 180.0f)
		return d_vtc;

	if (angle == 90.0f || angle == 270.0f)
		return d_hrz;

	return d_none;
}

void Bar::__set_pickedBar(){
	status = b_clicked;
	mag = 1.0f;
	angle = 0.0f;

	return;
}

void Bar::__set_usedBar(Location _loc){
	status = b_used;
	loc = _loc;
	mag = 1.0f;
	//angle = 0.0f;	/////

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

	if (angle >= 360.0f)
		angle -= 360.0f;

	if (angle < 0.0f)
		angle += 360.0f;

	return;
}