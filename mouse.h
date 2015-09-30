#ifndef __MOUSE_H
#define __MOUSE_H

#include <d3d9.h>
#include "common.h"

class Square;
class Point;
class Player;
class Character;
class Bar;

enum Mstat{ m_ready, m_clk_chara, m_clk_bar, m_etc };

class Mouse{
private:
	Mstat status;
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback
	Location locoo;	// (-1, a), (b, -1), ...
	Location locooits;
	IDirect3DTexture9* effect_square;
	Bar* pick;

public:
	Mouse();
	Mouse(Location);	/////
	~Mouse();

	void Click();
	void R_Click();
	void Wheel(bool) const;
	void DrawEffect() const;

	Square* CheckOnSquare() const;
	Character* CheckOnCharacter() const;
	Bar* CheckOnBar() const;
	bool CheckRoundRange(Bar*) const;
	Point* CheckAroundPoint() const;

	void __set_loc(int, int);

	Mstat get_status() const{ return status; }
	Location get_pxloc() const{ return pxloc; }
	Location get_locoo() const{ return locoo; }
	Location get_locooits() const{ return locooits; }
	Bar* get_pick() const{ return pick; }

	void set_status(Mstat stat){ status = stat; return; }
};

#endif // __MOUSE_H