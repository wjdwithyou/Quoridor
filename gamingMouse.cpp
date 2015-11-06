#include "gamingMouse.h"
#include <math.h>
#include "dxfunc.h"
#include "image.h"
#include "process.h"
#include "board.h"
#include "square.h"
#include "point.h"
#include "player.h"
#include "character.h"
#include "bar.h"

GamingMouse::GamingMouse()
	: Mouse(), status(m_ready), effect_square(image->Effect_Texture), pick(NULL)
{
	locoo.x = locoo.y = -1;
	locooits.x = locooits.y = -1;
}

GamingMouse::GamingMouse(Location loc)
	: Mouse(), status(m_clk_chara), locoo(loc), effect_square(image->Effect_Texture), pick(NULL)
{
	locooits.x = locooits.y = -1;	/////
}

GamingMouse::~GamingMouse(){}

void GamingMouse::Click(Player** turn){
	Character* cmp = (*turn)->get_character();
	Bar* bmp = (*turn)->__get_lastBar();
	Point* pmp;

	switch (status){
	case m_ready:
		if (CheckOnCharacter() == cmp){
			status = m_clk_chara;

			Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_clicked);

			cmp->SearchMoveable();
			cmp->RevealMoveable();

			// impl.
		}

		if (CheckOnBar(*turn) != NULL){
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
					*turn = (*turn)->get_next();
					status = m_ready;
				}

				break;
			default:
				break;
			}
		}

		break;

	case m_clk_bar:
		if (pick->get_status() != b_can)
			break;
		/*
		if (CheckAroundUsedBar())
			// beep sound?
			break;
		*/
		
		
		pmp = CheckAroundPoint(*turn);

		pmp->set_onBarStatus(pick->CheckOrthogonal());

		pick->__set_usedBar(pmp->get_pxloc());
		pick = NULL;
		
		(*turn)->__set_numBar(-1);
		
		*turn = (*turn)->get_next();
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

void GamingMouse::R_Click(){
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

void GamingMouse::Wheel(bool b) const{
	if (pick == NULL)
		return;

	float delta = (b)? -45.0f: 45.0f;

	pick->__set_angle(delta);

	if (pick->CheckOrthogonal() == d_none)
		pick->set_status(b_clicked);

	return;
}

void GamingMouse::DrawEffect() const{
	if (CheckOnSquare() != NULL){
		if (status == m_clk_bar)
			return;

		//DrawTexture(effect_square, CooToPxl(locoo), 1.0f, 0.0f);				// Why it doesn't work???
		DrawTexture(image->Effect_Texture, CooToPxl(locoo, Board::SIZE), 1.0f, 0.0f);
	}

	return;
}

/*
Button* GamingMouse::CheckOnButton() const{		// override

	return NULL;
}
*/

Square* GamingMouse::CheckOnSquare() const{
	if (locoo.x == -1 || locoo.y == -1)
		return NULL;

	return Board::board[locoo.y][locoo.x];
}

Character* GamingMouse::CheckOnCharacter() const{
	if (CheckOnSquare() == NULL)
		return NULL;

	return CheckOnSquare()->get_onthis();
}

Bar* GamingMouse::CheckOnBar(Player* turn) const{
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

bool GamingMouse::CheckRoundRange(Bar* b) const{
	if (pow(static_cast<float>(pxloc.x - b->get_loc().x), 2) + pow(static_cast<float>(pxloc.y - b->get_loc().y), 2)\
		<= pow(static_cast<float>(0.75 * ((b->get_size().x <= b->get_size().y)? b->get_size().x: b->get_size().y))/* >> 1*/, 2))
		return true;

	return false;
}

Point* GamingMouse::CheckAroundPoint(Player* turn) const{
	if (status != m_clk_bar)
		return NULL;

	if (locooits.x == -1 || locooits.y == -1){
		pick->set_status(b_clicked);
		return NULL;
	}

	if (pick->CheckOrthogonal() == d_none)
		return NULL;

	if (CheckAroundUsedBar())
		pick->set_status(b_cannot);
	else{
		Player* iter = turn;
		Bstat bsmp = b_can;

		do{
			if (iter->get_character()->CheckReachable(locooits, pick->CheckOrthogonal()) == false){
				bsmp = b_cannot;
				break;
			}

			iter = iter->get_next();
		} while(iter != turn);

		pick->set_status(bsmp);
	}

	return Board::its[locooits.y][locooits.x];
}

bool GamingMouse::CheckAroundUsedBar() const{
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

void GamingMouse::__set_loc(int x, int y){
	Mouse::__set_loc(x, y);
	
	locoo = PxlToCoo(pxloc, Board::SIZE);
	locooits = PxlToCoo(pxloc, Board::SIZE - 1);

	return;
}