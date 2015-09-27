#include "mouse.h"
#include <math.h>
#include "dxfunc.h"
#include "image.h"
#include "board.h"
#include "square.h"
#include "player.h"
#include "character.h"
#include "bar.h"

Mouse::Mouse()
	: status(m_ready), effect_square(image->Effect_Texture)
{
	pxloc.x = pxloc.y = 0;
	locoo.x = locoo.y = -1;
}

Mouse::Mouse(Location loc)
	: status(m_clk_chara), locoo(loc), effect_square(image->Effect_Texture)
{
	pxloc.x = pxloc.y = 0;	/////
}

Mouse::~Mouse(){}

void Mouse::Click(Player** turn){
	Character* cmp = (*turn)->get_character();
	Bar* bmp = (*turn)->__get_lastBar();

	switch (status){
	case m_ready:
		if (CheckOnCharacter() == cmp){
			status = m_clk_chara;

			Board::board[cmp->get_loc().y][cmp->get_loc().x]->set_status(q_clicked);

			cmp->SearchMoveable();
			cmp->RevealMoveable();

			//impl.
		}

		if (CheckOnBar(*turn)){
			status = m_clk_bar;
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
		// impl.
		break;

	case m_etc:
		// impl.

		break;

	default:
		break;
	}

	return;
}

void Mouse::DrawEffect() const{
	if (CheckOnSquare() != NULL)
		//DrawTexture(effect_square, CooToPxl(locoo), 1.0f, 0.0f);				// Why it doesn't work???
		DrawTexture(image->Effect_Texture, CooToPxl(locoo), 1.0f, 0.0f);

	return;
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

Bar* Mouse::CheckOnBar(Player* turn) const{
	Bar* temp = turn->__get_lastBar();

	if (!CheckRoundRange(temp)){
		temp->set_status(b_over);
		return NULL;
	}

	temp->set_status(b_on);

	return temp;
}

bool Mouse::CheckRoundRange(Bar* b) const{
	if (pow(static_cast<float>(pxloc.x - b->get_loc().x), 2) + pow(static_cast<float>(pxloc.y - b->get_loc().y), 2)\
		<= pow(static_cast<float>(0.75 * ((b->get_size().x <= b->get_size().y)? b->get_size().x: b->get_size().y)), 2))
		return true;

	return false;
}

void Mouse::__set_loc(int x, int y){
	pxloc.x = x;
	pxloc.y = y;

	locoo = PxlToCoo(pxloc);

	return;
}