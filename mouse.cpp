#include "mouse.h"
#include "process.h"
#include "menu.h"
#include "button.h"
#include "player.h"

Mouse::Mouse(){
	pxloc.x = pxloc.y = 0;
	//g_mouse = this;
}

Mouse::~Mouse(){}

void Mouse::Click(Player** dummy){
	Button* btnp;

	if ((btnp = CheckOnButton()) != NULL){
		int pn = btnp->get_num();
		
		switch(pn){
		case 1: // 2player
		case 2:	// 4player
			Player::numPlayer = pn << 1;
			//Process::status = p_game;
			//status = m_ready;
			
			g_process = p_game;
			*g_process_cur = *(g_process_list0 + g_process);
			//++(*g_process_test);

			//(*g_process_cur)->Init(pn<<1);
			(*g_process_cur)->Init();

			//(*(g_process_list0 + g_process))->Init(pn<<1);

			//(*g_process_test)->Init(pn<<1);
			g_mouse = (*g_process_cur)->get_mouse();

			break;

		case 4:	// exit
			exit(0);
			break;

		case 0:	// 1player
			// impl.
		case 3: // opt.
			// impl.
		default:
			break;
		}
	}
			
	return;
}

void Mouse::R_Click(){
	// impl?
	return;
}

void Mouse::Wheel(bool b) const{
	// impl?
	return;
}

Button* Mouse::CheckOnButton() const{
	// TODO: REARRANGE
	if (pxloc.y < Menu::loc.y || pxloc.y >= Menu::loc.y + (Button::HEIGHT * Button::NUM))
		return NULL;

	if (pxloc.x < Menu::loc.x || pxloc.x >= Menu::loc.x + Button::WIDTH)
		return NULL;

	for (int i = 0; i < Button::NUM; ++i)
		Menu::btnList[i]->set_status(btn_down);

	Menu::btnList[(pxloc.y - Menu::loc.y) / Button::HEIGHT]->set_status(btn_up);

	return Menu::btnList[(pxloc.y - Menu::loc.y) / Button::HEIGHT];
}

Bar* Mouse::CheckOnBar() const{
	// impl?
	return NULL;
}

Point* Mouse::CheckAroundPoint() const{
	// impl?
	return NULL;
}

void Mouse::__set_loc(int x, int y){
	pxloc.x = x;
	pxloc.y = y;

	return;
}