#include "mouse.h"
#include <math.h>
#include "dxfunc.h"
#include "image.h"
#include "process.h"
#include "menu.h"
#include "button.h"	/////
#include "board.h"
#include "square.h"
#include "point.h"
#include "player.h"
#include "character.h"
#include "bar.h"

Mouse::Mouse()
	: status(m_menu), effect_square(image->Effect_Texture), pick(NULL)
{
	pxloc.x = pxloc.y = 0;
	locoo.x = locoo.y = -1;
	locooits.x = locooits.y = -1;
}

Mouse::Mouse(Location loc)
	: status(m_clk_chara), locoo(loc), effect_square(image->Effect_Texture), pick(NULL)
{
	pxloc.x = pxloc.y = 0;	/////
	locooits.x = locooits.y = -1;	/////
}

Mouse::~Mouse(){}

void Mouse::Click(){
	Button* btnp;
	
	Character* cmp = turn->get_character();
	Bar* bmp = turn->__get_lastBar();
	Point* pmp;

	switch (status){
	case m_menu:
		if ((btnp = CheckOnButton()) != NULL){
			switch(btnp->get_num()){
			case 2:	// 4player
				//Player::numPlayer = n;
				Process::status = p_game;
				status = m_ready;
				break;
			case 4:	// exit
				exit(0);
				break;

			case 0:
			case 1:
			case 3:
			default:
				break;
			}
		}

		break;

	case m_ready:
		if (CheckOnCharacter() == cmp){
			status = m_clk_chara;

			Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_clicked);

			cmp->SearchMoveable();
			cmp->RevealMoveable();

			// impl.
		}

		if (CheckOnBar() != NULL){
			status = m_clk_bar;
			pick = bmp;

			pick->__set_pickedBar();
			// impl.
		}

		// impl.

		break;

	case m_clk_chara:
		if (CheckOnSquare() != NULL){
			switch (CheckOnSquare()->get_status()){
			case q_base:
				break;
			case q_clicked:
				Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_base);

				cmp->HideMoveable();
				cmp->ResetMoveable();

				status = m_ready;

				break;
			case q_moveable:
				Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_base);

				cmp->Move(CheckOnSquare());

				cmp->HideMoveable();
				cmp->ResetMoveable();

				if (cmp->Check()){
					Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_win);
					// impl.
					status = m_etc;
				}
				else{
					turn = turn->get_next();
					status = m_ready;
				}

				break;
			default:
				break;
			}
		}

		break;

	case m_clk_bar:
		if (CheckAroundUsedBar())
			// beep sound?
			break;
		
		pmp = CheckAroundPoint();

		pmp->set_onBarStatus(pick->CheckOrthogonal());

		pick->__set_usedBar(pmp->get_pxloc());
		pick = NULL;
		
		turn->__set_numBar(-1);
		
		turn = turn->get_next();
		status = m_ready;

		break;

	case m_etc:
		// impl.

		break;

	default:
		break;
	}

	return;
}

void Mouse::R_Click(){
	switch (status){
	case m_ready:
		break;

	case m_clk_chara:
		// impl.
		break;

	case m_clk_bar:
		pick->__set_releasedBar();
		pick = NULL;

		status = m_ready;

		break;

	case m_etc:
		break;

	default:
		break;
	}

	return;
}

void Mouse::Wheel(bool b) const{
	if (pick == NULL)
		return;

	float delta = (b)? -45.0f: 45.0f;

	pick->__set_angle(delta);

	if (pick->CheckOrthogonal() == d_none)
		pick->set_status(b_clicked);

	return;
}

void Mouse::DrawEffect() const{
	if (CheckOnSquare() != NULL){
		if (status == m_clk_bar)
			return;

		//DrawTexture(effect_square, CooToPxl(locoo), 1.0f, 0.0f);				// Why it doesn't work???
		DrawTexture(image->Effect_Texture, CooToPxl(locoo, Board::SIZE), 1.0f, 0.0f);
	}

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

Square* Mouse::CheckOnSquare() const{
	if (locoo.x == -1 || locoo.y == -1)
		return NULL;

	return Board::board[locoo.y][locoo.x];
}

Character* Mouse::CheckOnCharacter() const{
	if (CheckOnSquare() == NULL)
		return NULL;

	return CheckOnSquare()->get_onthis();
}

Bar* Mouse::CheckOnBar() const{
	if (Process::status != p_game)
		return NULL;

	Bar* b = turn->__get_lastBar();

	if (b == NULL)
		return NULL;

	if (status != m_ready)	// test
		return NULL;

	if (!CheckRoundRange(b)){
		b->set_status(b_over);
		return NULL;
	}

	b->set_status(b_on);

	return b;
}

bool Mouse::CheckRoundRange(Bar* b) const{
	if (pow(static_cast<float>(pxloc.x - b->get_loc().x), 2) + pow(static_cast<float>(pxloc.y - b->get_loc().y), 2)\
		<= pow(static_cast<float>(0.75 * ((b->get_size().x <= b->get_size().y)? b->get_size().x: b->get_size().y))/* >> 1*/, 2))
		return true;

	return false;
}

Point* Mouse::CheckAroundPoint() const{
	if (status != m_clk_bar)
		return NULL;

	if (locooits.x == -1 || locooits.y == -1){
		pick->set_status(b_clicked);
		return NULL;
	}

	if (pick->CheckOrthogonal() == d_none)
		return NULL;

	pick->set_status(CheckAroundUsedBar()? b_cannot: b_can);

	return Board::its[locooits.y][locooits.x];
}

bool Mouse::CheckAroundUsedBar() const{
	// TODO: REARRANGE
	// Location demp[2][2] = {{{0, -1}, {0, 1}}, {{-1, 0}, {1, 0}}};
	Bdir pdir = pick->CheckOrthogonal();

	switch (pdir){
	case d_none:
		break;

	case d_vtc:
		if (locooits.y != 0){
			if (pdir == Board::its[locooits.y - 1][locooits.x]->get_onBarStatus())
				return true;
		}

		if (Board::its[locooits.y][locooits.x]->get_onBarStatus() != d_none)
			return true;

		if (locooits.y != Board::SIZE - 2){
			if (pdir == Board::its[locooits.y + 1][locooits.x]->get_onBarStatus())
				return true;
		}

		break;

	case d_hrz:
		if (locooits.x != 0){
			if (pdir == Board::its[locooits.y][locooits.x - 1]->get_onBarStatus())
				return true;
		}

		if (Board::its[locooits.y][locooits.x]->get_onBarStatus() != d_none)
			return true;

		if (locooits.x != Board::SIZE - 2){
			if (pdir == Board::its[locooits.y][locooits.x + 1]->get_onBarStatus())
				return true;
		}

		break;

	default:
		break;
	}

	return false;
}

void Mouse::__set_loc(int x, int y){
	pxloc.x = x;
	pxloc.y = y;
	
	locoo = PxlToCoo(pxloc, Board::SIZE);
	locooits = PxlToCoo(pxloc, Board::SIZE - 1);

	return;
}