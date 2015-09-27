#ifndef __BAR_H
#define __BAR_H

#include <d3d9.h>
#include "common.h"

enum Bstat{ b_over, b_on, b_clicked };

class Bar{
private:
	static Location size;

	Bstat status;
	Location loc;
	float mag;
	IDirect3DTexture9** texture_pack;

public:
	const static int _BOARD = 50;	// board-bar
	const static int _BAR = 15;		// bar-bar

public:
	Bar();
	Bar(Bstat, Location);
	~Bar();

	void DrawBar() const;

	Location get_size() const{ return size; }
	Location get_loc() const{ return loc; }		// for debug!
	float get_mag() const{ return mag; }

	void set_status(Bstat s){ status = s; return; }
};

#endif // __BAR_H