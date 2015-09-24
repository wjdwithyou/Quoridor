#ifndef __SQUARE_H
#define __SQUARE_H

#include <d3d9.h>
#include "common.h"

class Character;

enum Qstat{ q_base, q_clicked, q_moveable, q_win };

class Square{
private:
	Qstat status;
	Location loc;
	Character* onthis;
	IDirect3DTexture9** texture_pack;

public:
	const static int SQUARE_SIZE = 60;
	const static int MAX_QSTAT = 4;

public:
	Square();
	Square(int, int);
	~Square();

	void Draw() const;

	Qstat get_status() const{ return status; }
	Location get_loc() const{ return loc; }
	Character* get_onthis() const{ return onthis; }

	void set_status(Qstat s){ status = s; return; }
	void set_onthis(Character* c){ onthis = c; return; }
};

#endif // __SQUARE_H