#ifndef __GAMING_MOUSE_H
#define __GAMING_MOUSE_H

#include "mouse.h"
#include <d3d9.h>
#include "common.h"

class Button;
class Square;
class Point;
class Player;
class Character;
class Bar;

enum Mstat{ m_ready, m_clk_chara, m_clk_bar, m_etc };

class GamingMouse : public Mouse{
private:
	Mstat status;
	Location locoo;	// 0 to 8, and -1
	Location locooits; // 0 to 7, and -1
	IDirect3DTexture9* effect_square;
	Bar* pick;

public:
	GamingMouse();
	GamingMouse(Location);	/////
	~GamingMouse();

	void Click(Player**);	// global variable을 굳이 parameter로 받을 필요가 있는지?
							// global variable을 통한 접근은 WndProc으로 한정?
	void R_Click();
	void Wheel(bool) const;
	void DrawEffect() const;

	Button* CheckOnButton() const;
	Square* CheckOnSquare() const;
	Character* CheckOnCharacter() const;
	Bar* CheckOnBar(Player*) const;
	bool CheckRoundRange(Bar*) const;
	Point* CheckAroundPoint(Player*) const;
	bool CheckAroundUsedBar() const;
	bool CheckBlocking(Player*) const;

	void __set_loc(int, int);

	Mstat get_status() const{ return status; }
	Location get_locoo() const{ return locoo; }
	Location get_locooits() const{ return locooits; }
	Bar* get_pick() const{ return pick; }

	void set_status(Mstat stat){ status = stat; return; }
};

#endif // __GAMING_MOUSE_H